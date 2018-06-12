/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 04:12:12 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 05:10:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d		normal_paraboloid(t_object obj, t_point3d point, t_line line)
{
	t_point3d normal;

	(void)line;
	(void)obj;
	normal = normalize(ft_new_vec3(-1, 2 * point.y, 2 * point.z));
	return (normal);
}

t_point3d		normal_hyperboloid(t_object obj, t_point3d point, t_line line)
{
	t_point3d	normal;
	double		a;

	(void)line;
	a = obj.object_union.hyperboloid.radius;
	normal = normalize(ft_new_vec3(-2 * point.x, 2 * point.y, 2 * point.z));
	return (normal);
}

t_point3d		normal_mobius(t_object obj, t_point3d point, t_line line)
{
	t_point3d normal;

	(void)line;
	(void)obj;
	normal = normalize(ft_new_vec3(
		2 * point.x * point.y - 2 * point.z - 4 * point.x * point.z,
		point.x * point.x + point.z * point.z + 3 * point.y * point.y - 1,
		2 * (point.y * point.z - point.x - point.x *
			point.x - point.y * point.y)));
	return (normal);
}
