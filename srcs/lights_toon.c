/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:37:59 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/17 00:02:39 by lcavalle         ###   ########.fr       */
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

static t_illum	getillum(t_world *world, t_hit *hit, t_line **srays)
{
	int		i;
	t_illum	illu;
	double	newillu;
	t_light	light;

	i = -1;
	illu.in = world->ambient.in;
	illu.color = interpole_color(illu.in, BLACK_COLOR, world->ambient.color);
	while (++i < world->nlights)
		if (srays[i])
		{
			light = world->lights[i];
			if (light.type != 'd')
				light.intensity = 1.0 * (1.0 - world->fog.in) /
					sqrt(magnitude(newvector(hit->point, light.o))) * 3;
			newillu = dotprod(hit->normal, srays[i]->v) *
				light.intensity / world->nlights;
			newillu = newillu < 0.6 ? 0.45 : 0.85;
			illu.in += newillu;
			illu.color = add_colors(
					illu.color, scale_color(light.c, newillu));
		}
	illu.in = illu.in < world->ambient.in ? world->ambient.in : illu.in;
	illu.in = illu.in > 1.0 ? 1.0 : illu.in;
	return (illu);
}

static t_illum	getshine(t_world *world, t_hit *hit, t_line **srays, t_color lc)
{
	int		i;
	t_illum	shine;
	double	newsh;
	t_light	light;

	shine.color = lc;
	shine.in = 0;
	i = -1;
	while (++i < world->nlights)
		if (srays[i] && world->lights[i].type != 'd')
		{
			light = world->lights[i];
			light.intensity = magnitude(newvector(hit->point, light.o)) *
				(1.0 - world->fog.in);
			newsh = dotprod(hit->bounce, srays[i]->v);
			newsh = newsh > 0 ? pow(newsh, PHONG * light.intensity) : 0;
			newsh = newsh < 0.6 ? 0.2 : 0.85;
			shine.color = add_colors(
					shine.color, scale_color(light.c, newsh));
			shine.in = shine.in + newsh > 1.0 ? 1.0 : shine.in + newsh;
		}
	return (shine);
}

t_color			illuminate_toon(t_world *world, t_hit *hit, t_line **srays,
		int fast)
{
	t_illum	illu;
	t_illum	shine;
	t_color	lightcol;

	illu = getillum(world, hit, srays);
	lightcol = interpole_color(illu.in, BLACK_COLOR, interpole_color(
				getwhiteratio(illu.color, 0.3, 1), illu.color, hit->obj.c));
	if (fast)
		return (lightcol);
	shine = getshine(world, hit, srays, lightcol);
	return (interpole_color(shine.in, lightcol, shine.color));
}