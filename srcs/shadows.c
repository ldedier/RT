/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 23:03:33 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 08:29:15 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	clampwhite(t_color c)
{
	unsigned char min;

	min = c.r;
	min = c.g < min ? c.g : min;
	min = c.b < min ? c.b : min;
	c.r -= min;
	c.g -= min;
	c.b -= min;
	return (c);
}

static t_illum	clamp_illum(t_illum il, t_intcolor icol)
{
	il.in = il.in > 1 ? 1 : il.in;
	il.in = il.in < 0 ? 0 : il.in;
	il.color = clampwhite(scale_convert_color(icol, 1));
	return (il);
}

static void		get_shadow_illum(t_shadow *shadow, t_world *world,
		t_light light, int bounce)
{
	t_hit	*hit;
	t_line	sray;

	if ((hit = trace(shadow->sray, world->cobjlist)))
	{
		if (bounce < world->max_bounce && hit->obj.transp > EPSILON &&
				(light.type == 'd' ||
				magnitude(newvector(shadow->sray.o, hit->point)) <
				magnitude(newvector(shadow->sray.o, light.o))))
		{
			shadow->il.in += (1 - hit->obj.transp) * (1 - shadow->il.in);
			sray = shadow->sray;
			shadow->sray = newray(translate_vec(hit->point, shadow->sray.v,
						EPSILON), shadow->sray.v);
			get_shadow_illum(shadow, world, light, bounce + 1);
			shadow->sray = sray;
			shadow->icol = add_scale_intcolors(shadow->icol,
					get_intcolor(pert_color(hit)), 1 - hit->obj.transp);
		}
		if (bounce == 0)
			shadow->il = clamp_illum(shadow->il, shadow->icol);
	}
	free(hit);
}

static void		castshadows2(t_world *world, t_hit *hit, t_shadow **shadows,
		int i)
{
	int		shadow;
	t_hit	*shit;

	shadow = 0;
	if (((shit = trace(shadows[i]->sray, world->cobjlist)) &&
				((world->lights[i].type != 'd' &&
				magnitude(newvector(shadows[i]->sray.o, shit->point)) <
				magnitude(newvector(hit->point, world->lights[i].o))) ||
				world->lights[i].type == 'd')))
	{
		if (shit->obj.transp < EPSILON)
			shadow = 1;
		else
			get_shadow_illum(shadows[i], world, world->lights[i], 0);
	}
	if ((world->lights[i].type == 's' &&
				acos(dotprod(normalize(scale(shadows[i]->sray.v, -1)),
						world->lights[i].v)) > world->lights[i].angle) ||
			shadow)
	{
		free(shadows[i]);
		shadows[i] = NULL;
	}
	free(shit);
}

void			castshadows(t_world *world, t_hit *hit, t_shadow **shadows)
{
	int		i;

	i = 0;
	while (i < world->nlights)
	{
		shadows[i] = ft_memalloc(sizeof(t_shadow));
		if (world->lights[i].type != 'd')
			shadows[i]->sray.v = normalize(newvector(hit->point,
						world->lights[i].o));
		else
			shadows[i]->sray.v = normalize(scale(world->lights[i].v, -1));
		shadows[i]->sray.o = translate_vec(hit->point, hit->normal,
				EPSILON * proj(hit->normal, hit->bounce));
		castshadows2(world, hit, shadows, i);
		i++;
	}
}
