/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:36:39 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/22 18:50:15 by lcavalle         ###   ########.fr       */
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
	plane.o = pos;
	plane.s = POINT_ZERO;
	plane.r = v;
	plane.c = color;
	return (plane);
}

void		populate_world(t_world *world, unsigned char scene)
{
	world->lights[0].o = (t_point3d){.x = 2, .y = -1, .z = 0};
	world->lights[0].intensity = 0.5;
	//if (scene == 1)
		add_obj(&(world->objlist), create_sphere(SPHERE1_POS, SPHERE1_COL));
	if (scene == 2)
	{
		world->lights[0].o = (t_point3d){.x = -0.4, .y = 0.0, .z = 2};
		add_obj(&(world->objlist), create_sphere(SPHERE2_POS, SPHERE2_COL));
		add_obj(&(world->objlist), create_sphere(SPHERE3_POS, SPHERE3_COL));
	}
	//if (scene == 3)
	//	add_obj(&(world->objlist), create_plane(PLANE1_POS, PLANE1_VEC,
	//				PLANE1_COL));
}
