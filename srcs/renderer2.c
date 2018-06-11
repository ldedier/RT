/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:41:16 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 04:48:54 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ray_color_init(t_aux_ray_color *arc, t_world *world, t_hit *hit,
		int fast)
{
	t_color	illuminated_c;

	ft_init_aux_render(&(arc->x), hit);
	arc->fog.in = magnitude(newvector(hit->point, world->cam->o)) *
		world->fog.in;
	arc->fog.in = arc->fog.in > 1.0 ? 1.0 : arc->fog.in;
	castshadows(world, hit, arc->shadows);
	arc->aux = (t_shadowsfree){.shadows = arc->shadows,
		.nlights = world->nlights};
	illuminated_c = illuminate(world, hit, arc->shadows, fast);
	arc->fog.color = interpole_color(arc->fog.in, illuminated_c,
			world->fog.color);
	arc->hit = hit;
}

static t_color	get_reflect(t_world *world, const t_aux_ray_color *arc,
		int bounce, int fast)
{
	if (bounce < world->max_bounce && arc->x.f_reflect > EPSILON && !fast)
		return (ray_color(newray(translate_vec(arc->hit->point,
						arc->hit->pertbounce, EPSILON2), arc->hit->pertbounce),
				world, bounce + 1, 0));
	else
		return (pert_color(arc->hit));
}

static t_color	get_refract(t_world *world, const t_aux_ray_color *arc,
		int bounce, int fast)
{
	if (bounce < world->max_bounce && arc->x.f_transp > EPSILON && !fast)
	{
		if (fabs(arc->x.f_refract - 1) > EPSILON)
			return (ray_color(newray(translate_vec(arc->hit->point,
							arc->ray->v, EPSILON), refraction(arc->hit,
								arc->ray, arc->x.f_refract)),
					world, bounce + 1, 0));
		else
			return (ray_color(newray(translate_vec(arc->hit->point,
							arc->ray->v, EPSILON), arc->ray->v),
					world, bounce, 0));
	}
	else
		return (pert_color(arc->hit));
}

t_color		ray_color(t_line ray, t_world *world, int bounce, int fast)
{
	t_hit			*hit;
	t_aux_ray_color	aux_rc;
	t_color			reflect_c;
	t_color			refract_c;
	t_illum			ebloui;

	if ((hit = trace(ray, world->cobjlist)))
	{
		ray_color_init(&aux_rc, world, hit, fast);
		aux_rc.ray = &ray;
		reflect_c = get_reflect(world, &aux_rc, bounce, fast);
		refract_c = get_refract(world, &aux_rc, bounce, fast);
		ebloui.color = get_ebloui(world, ray, hit->t, &(ebloui.in));
		return (freeret_rend(interpole_color(aux_rc.x.f_transp,
						interpole_color(aux_rc.x.f_reflect,
							interpole_color(ebloui.in,
								aux_rc.fog.color, WHITE_COLOR),
							reflect_c), refract_c), &hit, &(aux_rc.aux)));

	}
	ebloui.color = get_ebloui(world, ray, -1, &(ebloui.in));
	return (freeret_rend(ebloui.color, &hit, NULL));
}
