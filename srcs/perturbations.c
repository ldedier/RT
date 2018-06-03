/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:44:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/03 07:25:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	pert_normal(t_hit *hit)
{
	t_point3d	pert;
	t_point3d	rand_ang;
	double		angle;

	if (hit->obj.pert == e_ripple)
		angle = sin(magnitude(hit->point));
	else if (hit->obj.pert == e_waves)
		angle = sin(hit->point.x);
	else
		angle = 0;
	pert = normalize(rotate_axis(hit->normal, normalize(crossprod(hit->normal, hit->point)), angle * 0.2));
	if (hit->obj.pert == e_noise)
	{
		angle = 0.12;
		rand_ang.x = (double)(rand() % 100) / 100 * angle - angle / 2;
		rand_ang.y = (double)(rand() % 100) / 100 * angle - angle / 2;
		rand_ang.z = (double)(rand() % 100) / 100 * angle - angle / 2;
		pert = rotate_vec(pert, rand_ang);
	}
	return (pert);
}

t_color	pert_color(t_hit *hit)
{
	t_color	ret;
	t_color	inv;

	ret = get_object_color(hit);
	inv = scale_convert_color(add_scale_intcolors(get_intcolor(WHITE_COLOR),
				get_intcolor(get_object_color(hit)), -1), 1);
	if (hit->obj.pert == e_chess && 
			(((sin(hit->point.x) > 0 ? 1 : -1) *
			  (sin(hit->point.z) > 0 ? 1 : -1)) > 0))
		return (inv);
	if (hit->obj.pert == e_spiral)
	{
		return (inv);
	}
	return (ret);
}
