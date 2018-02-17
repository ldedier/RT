/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:36:39 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/17 03:13:46 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** todo: read from file
*/

t_object	create_sphere(t_point3d pos, double rad, t_color color)
{
	t_object	sphere;

	sphere.intersect_func = intersect_shpere;
	sphere.o = pos;
	sphere.s.x = rad;
	sphere.r = (t_point3d) {.x = 0.0, .y = 0.0, .z = 0.0};
	sphere.c = color;
	return (sphere);
}

void		populate_world(t_world *world, unsigned char scene)
{
	t_point3d	p;
	t_color		c;

	if (scene == 1)
		add_obj(&(world->objlist), create_sphere(SPHERE1_POS, SPHERE1_COL));
}
