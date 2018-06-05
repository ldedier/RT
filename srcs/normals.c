/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:44:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/26 06:59:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	normal_sphere(t_object sphere, t_point3d hitpoint, t_line line)
{
	(void)sphere;
	(void)line;
	return (normalize(hitpoint));
}

t_point3d	normal_cone(t_object cone, t_point3d hitpoint, t_line line)
{
	/*	t_point3d	aux;
		t_point3d	hitplane;
		t_point3d	normal;

		aux = newvector(cone.o, hitpoint);
		hitplane = crossprod(aux, cone.r);
		normal = crossprod(aux, hitplane);
		if (dotprod(cone.r, aux) < 0.0)
		normal = scale(normal, -1.0);
		return (normalize(normal));*/
	t_point3d	normal;

	(void)line;
	normal.x = (hitpoint.x > 0 ? -1 : 1) *
		sqrt(hitpoint.z * hitpoint.z + hitpoint.y * hitpoint.y) *
		tan(cone.object_union.cone.angle);
	normal.y = hitpoint.y;
	normal.z = hitpoint.z;
	return (normal);
}

t_point3d	normal_plane(t_object plane, t_point3d hitpoint, t_line line)
{
	t_point3d	normal;

	(void)plane;
	(void)hitpoint;
	normal = ft_new_vec3(0, (line.v.y < 0) ? 1 : -1, 0);
	return (normal);
}

t_point3d	normal_cylinder(t_object cyl, t_point3d hitpoint, t_line line)
{
	t_point3d	normal;

	(void)cyl;
	(void)line;
	normal = normalize(ft_new_vec3(0, hitpoint.y, hitpoint.z));
	return (normal);
}

t_point3d		normal_ellipsoid(t_object obj, t_point3d point, t_line line)
{
	t_point3d normal;
	t_point3d	abc;

	(void)line;
	abc = obj.object_union.ellipsoid.abc;
	normal = ft_new_vec3(point.x / (abc.x * abc.x), point.y / (abc.y * abc.y),
			point.z / (abc.z * abc.z));
	return (normal);
}
