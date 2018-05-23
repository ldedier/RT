/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:44:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/23 01:49:08 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	pert_sphere(t_hit *hit)
{
	(void)hit;
	return (hit->normal);
}

t_point3d	pert_cone(t_hit *hit)
{
	return (hit->normal);
}

t_point3d	pert_plane(t_hit *hit)
{
	t_point3d	pert;
	t_point3d	yaxis;

	yaxis = (t_point3d){.x = 0, .y = 0, .z = 1};
	//plane.ptbn.v = (t_point3d){.x=rand() % 100 / 50.0 - 1.0,.y=0,.z=rand() % 100 / 50.0 - 1.0};
//	hit->obj.pert.v = yaxis;//crossprod(hit->point, yaxis);
	double angle = sin(magnitude(hit->point));
	pert = rotate_axis(hit->normal, hit->obj.pert.v, angle);
	//printf("%f %f %f\n",pert.x,pert.y,pert.z);fflush(stdout);
	return (pert);
}

t_point3d	pert_cylinder(t_hit *hit)
{
	(void)hit;
	return (hit->normal);
}
