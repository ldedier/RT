/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:44:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/03/02 20:31:58 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	normal_sphere(t_object sphere, t_point3d hitpoint)
{
	return (normalize(newvector(sphere.o, hitpoint)));
}

t_point3d	normal_cone(t_object cone, t_point3d hitpoint)
{
	t_point3d	aux;
	t_point3d	hitplane;
	t_point3d	normal;

	aux = newvector(cone.o, hitpoint);
	hitplane = crossprod(aux, cone.r);
	normal = crossprod(aux, hitplane);
	if (dotprod(cone.r, aux) < 0.0)
		normal = scale(normal, -1.0);
	return (normalize(normal));
}

t_point3d	normal_plane(t_object plane, t_point3d hitpoint)
{
	(void)hitpoint;
	return (plane.r);
}

t_point3d	normal_cylinder(t_object cyl, t_point3d hitp)
{
	return (normalize(newvector(
					translate_vec(cyl.o, cyl.r,
						dotprod(cyl.r, newvector(cyl.o, hitp))), hitp)));
}
