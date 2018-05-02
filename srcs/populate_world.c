/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:36:39 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 07:15:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	create_sphere(t_point3d pos, double rad, t_color color)
{
	t_object	sphere;

	sphere.intersect_func = intersect_sphere;
//	sphere.normal_func = normal_sphere;
	sphere.o = pos;
	sphere.s.x = rad;
	sphere.r = POINT_ZERO;
	sphere.c = color;
	return (sphere);
}

t_object	create_plane(t_point3d pos, t_point3d v, t_color color)
{
	t_object	plane;

	plane.intersect_func = intersect_plane;
//	plane.normal_func = normal_plane;
	plane.o = pos;
	plane.s = POINT_ZERO;
	plane.r = normalize(v);
	plane.c = color;
	return (plane);
}

t_object	create_cone(t_point3d pos, t_point3d v, double the, t_color color)
{
	t_object	cone;

	cone.intersect_func = intersect_cone;
//	cone.normal_func = normal_cone;
	cone.o = pos;
	cone.s.x = the;
	cone.r = normalize(v);
	cone.c = color;
	return (cone);
}

t_object	create_cylind(t_point3d pos, t_point3d v, double rad, t_color color)
{
	t_object	cylinder;

	cylinder.intersect_func = intersect_cylinder;
//	cylinder.normal_func = normal_cylinder;
	cylinder.o = pos;
	cylinder.s.x = rad;
	cylinder.r = normalize(v);
	cylinder.c = color;
	return (cylinder);
}
