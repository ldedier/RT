/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:37:59 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/03 05:59:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	getwhiteratio(t_color c, double bot, double top)
{
	double	min;
	double	res;

	min = c.r;
	min = c.g < min ? c.g : min;
	min = c.b < min ? c.b : min;
	res = min / 0xFF;
	if (res > bot)
	{
		if (res < top)
			return (res);
		else
			return (top);
	}
	else
		return (bot);
}

static t_illum	getillum(t_world *world, t_hit *hit, t_shadow **shadows)
{
	int		i;
	t_illum	illu;
	double	newillu;
	t_light	light;

	i = -1;
	illu.in = world->ambient.in;
	illu.color = interpole_color(illu.in, BLACK_COLOR, world->ambient.color);
	while (++i < world->nlights)
		if (shadows[i])
		{
			light = world->lights[i];
			if (light.type != 'd')
				light.intensity = 1.0 * (1.0 - world->fog.in) /
					sqrt(magnitude(newvector(hit->point, light.o)));
			newillu = dotprod(hit->pert, shadows[i]->sray.v) *
				light.intensity / world->nlights;
			newillu *= 1 - shadows[i]->il.in;
			newillu = newillu > 0 ? newillu : 0;
			newillu = newillu > 1.0 ? 1.0 : newillu;
			illu.in += newillu;
			if (shadows[i]->il.in > EPSILON)
			illu.color = interpole_color(shadows[i]->il.in,
					shadows[i]->il.color, illu.color);
			illu.color = add_colors(illu.color, scale_color(light.c, newillu));
		}
	illu.in = illu.in < world->ambient.in ? world->ambient.in : illu.in;
	illu.in = illu.in > 1.0 ? 1.0 : illu.in;
	return (illu);
}

static t_illum	getshine(t_world *world, t_hit *hit, t_shadow **shadows, t_color lc)
{
	int		i;
	t_illum	shine;
	double	newsh;
	t_light	lig;

	shine.color = lc;
	shine.in = 0;
	i = -1;
	while (++i < world->nlights)
		if (shadows[i] && world->lights[i].type != 'd')
		{
			lig = world->lights[i];
			lig.intensity = magnitude(newvector(hit->point, lig.o)) *
				(1.0 - world->fog.in);
			newsh = dotprod(hit->pertbounce, shadows[i]->sray.v);
			newsh = newsh > 0 ? pow(newsh, hit->obj.shine * lig.intensity) : 0;
			shine.color = add_colors(
					shine.color, scale_color(lig.c, newsh));
			shine.in = shine.in + newsh > 1.0 ? 1.0 : shine.in + newsh;
		}
	return (shine);
}

t_color			get_object_color(t_hit *hit)
{
	if (hit->obj.parser.width == -1)
		return (hit->obj.c);
	else
		return get_color(hit->obj.texture_func(hit->obj, *hit));
}

t_color			illuminate(t_world *world, t_hit *hit, t_shadow **shadows, int fast)
{
	t_illum	illu;
	t_illum	shine;
	t_color	lightcol;
	t_color	plaincol;
	t_color	transp_scaled;

	plaincol = pert_color(hit);
	illu = getillum(world, hit, shadows);

//	transp_scaled = interpole_color(sqrt(hit->obj.transp), BLACK_COLOR, get_object_color(hit));
	transp_scaled = interpole_color(sqrt(hit->obj.transp), BLACK_COLOR, hit->obj.c);
	lightcol = interpole_color(illu.in, transp_scaled, interpole_color(
				getwhiteratio(illu.color, 0.3, 1), illu.color, plaincol));
	if (fast)
		return (lightcol);
	shine = getshine(world, hit, shadows, lightcol);
	return (interpole_color(shine.in, lightcol, shine.color));
}
