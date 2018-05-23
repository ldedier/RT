/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:44:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/23 09:33:35 by lcavalle         ###   ########.fr       */
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
	pert = normalize(rotate_axis(hit->normal, normalize(hit->point), angle));
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
