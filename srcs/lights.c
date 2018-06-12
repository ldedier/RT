/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:37:59 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 10:21:39 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_newillu(t_world *world, t_hit *hit, t_light light,
		t_shadow shadow)
{
	double	newillu;

	if (light.type != 'd')
		light.intensity = light.intensity * (1.0 - world->fog.in) /
			sqrt(magnitude(newvector(hit->point, light.o)));
	newillu = dotprod(hit->pert, normalize(shadow.sray.v)) *
		light.intensity;
	newillu = clamp_newillu(newillu, world, shadow.il.in);
	return (newillu);
}

static t_illum	getillum(t_world *world, t_hit *hit, t_shadow **shadows)
{
	int		i;
	t_illum	illu;
	double	newillu;
	t_light	light;

	i = -1;
	illu.in = world->ambient.in;
	illu.color = interpole_color(illu.in, get_color(0x0), world->ambient.color);
	while (++i < world->nlights)
	{
		if (shadows[i])
		{
			light = world->lights[i];
			newillu = get_newillu(world, hit, light, *(shadows[i]));
			illu.in += newillu;
			if (shadows[i]->il.in > EPSILON)
				illu.color = interpole_color(shadows[i]->il.in,
					shadows[i]->il.color, illu.color);
			illu.color = add_colors(illu.color, scale_color(light.c, newillu));
		}
	}
	illu.in = illu.in < world->ambient.in ? world->ambient.in : illu.in;
	illu.in = illu.in > 1.0 ? 1.0 : illu.in;
	return (illu);
}

static t_light	getshine2(t_light light, t_hit *hit, double fogin)
{
	light.intensity = 0.6;
	if (light.type != 'd')
		light.intensity = magnitude(newvector(hit->point, light.o)) *
			(1.0 - fogin);
	return (light);
}

static t_illum	getshine(t_world *world, t_hit *hit, t_shadow **shadows,
		t_color lc)
{
	int		i;
	t_illum	shine;
	double	newsh;
	t_light	lig;

	shine.color = lc;
	shine.in = 0;
	i = -1;
	while (++i < world->nlights)
		if (shadows[i])
		{
			lig = getshine2(world->lights[i], hit, world->fog.in);
			newsh = dotprod(hit->pertbounce, shadows[i]->sray.v);
			newsh = newsh > 0 ? pow(newsh, hit->obj.shine * lig.intensity) : 0;
			if (world->shader == 2)
				newsh = newsh < 0.6 ? 0.2 : 0.85;
			shine.color = add_colors(
					shine.color, scale_color(lig.c, newsh));
			shine.in = shine.in + newsh > 1.0 ? 1.0 : shine.in + newsh;
		}
	return (shine);
}

t_color			illuminate(t_world *world, t_hit *hit, t_shadow **shadows,
		int fast)
{
	t_illum	illu;
	t_illum	shine;
	t_color	lightcol;
	t_color	plaincol;
	t_color	transp_scaled;

	plaincol = pert_color(hit);
	illu = getillum(world, hit, shadows);
	transp_scaled = interpole_color(sqrt(hit->obj.transp), get_color(0x0),
			pert_color(hit));
	lightcol = interpole_color(illu.in, transp_scaled, interpole_color(
				getwhiteratio(illu.color, 0.3, 1), illu.color, plaincol));
	if (fast)
		return (lightcol);
	shine = getshine(world, hit, shadows, lightcol);
	return (interpole_color(shine.in, lightcol, shine.color));
}
