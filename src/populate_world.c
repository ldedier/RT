/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:36:39 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/27 03:34:24 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** todo: read from file
*/

t_object	create_sphere(t_point3d pos, double rad, t_color color)
{
	t_object	sphere;

	sphere.intersect_func = intersect_sphere;
	sphere.normal_func = normal_sphere;
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
	plane.normal_func = normal_plane;
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
	cone.normal_func = normal_cone;
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
	cylinder.normal_func = normal_cylinder;
	cylinder.o = pos;
	cylinder.s.x = rad;
	cylinder.r = normalize(v);
	cylinder.c = color;
	return (cylinder);
}

void		populate_world(t_world *world, unsigned char scene)
{
	t_objlist	**lst;
(void)scene;	
	lst = &(world->objlist);
	world->lights[0].o = LIGHT1_POS;
	world->lights[0].intensity = LIGHT1_INT;
	add_obj(lst, create_sphere(SPHERE1_POS, SPHERE1_RAD, SPHERE1_COL));
	if (scene > 1)
	{
		add_obj(lst, create_sphere(SPHERE2_POS, SPHERE2_RAD, SPHERE2_COL));
		add_obj(lst, create_sphere(SPHERE3_POS, SPHERE3_RAD, SPHERE3_COL));
	}
	if (scene > 2)
	{
		add_obj(lst, create_plane(PLANE1_POS, PLANE1_VEC, PLANE1_COL));
		add_obj(lst, create_plane(PLANE2_POS, PLANE2_VEC, PLANE2_COL));
	}
	if (scene > 3)
		add_obj(lst, create_cone(CONE1_POS, CONE1_VEC, CONE1_ANG, CONE1_COL));
	if (scene > 4)
		add_obj(lst, create_cylind(CYLINDER1_POS, CYLINDER1_VEC,
					CYLINDER1_RAD, CYLINDER1_COL));
}
