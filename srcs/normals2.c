/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 06:44:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 05:08:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d		normal_torus(t_object obj, t_point3d point, t_line line)
{
	t_point3d	normal;
	double		a;

	(void)line;
	a = 1.0 - (obj.object_union.torus.big_rad /
		sqrt(point.x * point.x + point.y * point.y));
	normal = normalize(ft_new_vec3(a * point.x, a * point.y, point.z));
	return (normal);
}

t_point3d		normal_goursat(t_object obj, t_point3d point, t_line line)
{
	t_point3d	normal;
	double		a;

	(void)line;
	a = obj.object_union.goursat.a;
	normal = normalize(ft_new_vec3(4 * (point.x * point.x * point.x) -
				(2 * a * point.x),
				4 * (point.y * point.y * point.y) - (2 * a * point.y),
				4 * (point.z * point.z * point.z) - (2 * a * point.z)));
	return (normal);
}

t_point3d		normal_lemniscate(t_object obj, t_point3d point, t_line line)
{
	t_point3d normal;

	(void)obj;
	(void)line;
	normal = normalize(ft_new_vec3(
				4 * point.x * point.x * point.x - 2 * point.x,
				2 * point.y,
				2 * point.z));
	return (normal);
}

t_point3d		normal_roman(t_object obj, t_point3d point, t_line line)
{
	t_point3d normal;

	(void)obj;
	(void)line;
	normal = normalize(ft_new_vec3(
				2 * point.x * point.y * point.y +
				2 * point.x * point.z * point.z +
				point.y * point.z,
				2 * point.y * point.x * point.x +
				2 * point.y * point.z * point.z +
				point.x * point.z,
				2 * point.z * point.y * point.y +
				2 * point.z * point.x * point.x +
				point.x * point.y));
	return (normal);
}

t_point3d		normal_piriform(t_object obj, t_point3d point, t_line line)
{
	t_point3d normal;

	(void)obj;
	(void)line;
	normal = normalize(ft_new_vec3(2 * point.x,
				4 * (point.y * point.y * point.y) - (3 * point.y * point.y),
				(2 * point.z)));
	return (normal);
}
