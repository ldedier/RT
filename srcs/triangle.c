/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 04:34:03 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/28 01:36:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
int			intersect_triangle(t_line line, t_object obj, double sols[MAX_DEGREE])
{
	t_point3d edge1 = ft_point3d_cmp(obj.object_union.triangle.v2,
			obj.object_union.triangle.v1);
	t_point3d edge2 = ft_point3d_cmp(obj.object_union.triangle.v3,
			obj.object_union.triangle.v1);
	t_point3d h = ft_point3d_cross_product(line.v, edge2);

	double a = ft_dot_product(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	double f = 1 / a;
	t_point3d s = ft_point3d_cmp(line.o, obj.object_union.triangle.v1);
	double u = f * ft_dot_product(s, h);
	if (u < 0 || u > 1)
		return (0);
	t_point3d q = ft_point3d_cross_product(s, edge1);
	double v = f * ft_dot_product(line.v, q);
	if (v < 0 || u + v > 1)
		return (0);
	sols[0] = f * ft_dot_product(edge2, q);
	return (1);
}
/*
int			intersect_triangle(t_line line, t_object obj, double sols[MAX_DEGREE])
{
	t_point3d edge1 = ft_point3d_cmp(obj.object_union.triangle.v2,
			obj.object_union.triangle.v1);
	t_point3d edge2 = ft_point3d_cmp(obj.object_union.triangle.v3,
			obj.object_union.triangle.v1);

	t_point3d normal = ft_point3d_cross_product(edge1, edge2);
	if (ft_dot_product(line.v, normal) > 0)
	{
		normal = ft_point3d_scalar(normal, -1);
	}

	float dotprodnormal_ray = ft_dot_product(normal, line.v);
	if (fabs(dotprodnormal_ray) < EPSILON)
		return 0;

	double d =  ft_dot_product(normal, obj.object_union.triangle.v1);
	double t = (ft_dot_product(normal, line.o) + d) / (-dotprodnormal_ray);
	if (t < 0)
		return (0);
	t_point3d point = ft_point3d_add(line.o, ft_point3d_scalar(line.v, t));

	t_point3d c;
	t_point3d vp0;
	t_point3d edge_0 = ft_point3d_cmp(obj.object_union.triangle.v2,
			obj.object_union.triangle.v1);

	vp0 = ft_point3d_cmp(point, obj.object_union.triangle.v1);
	c = ft_point3d_cross_product(edge_0, vp0);
	if (ft_dot_product(c, normal) < 0)
		return (0);

	t_point3d vp1;
	t_point3d edge_1 = ft_point3d_cmp(obj.object_union.triangle.v3,
			obj.object_union.triangle.v2);

	vp1 = ft_point3d_cmp(point, obj.object_union.triangle.v2);
	c = ft_point3d_cross_product(edge_1, vp1);
	if (ft_dot_product(c, normal) < 0)
		return (0);
	t_point3d vp2;
	t_point3d edge_2 = ft_point3d_cmp(obj.object_union.triangle.v1,
			obj.object_union.triangle.v3);

	vp2 = ft_point3d_cmp(point, obj.object_union.triangle.v3);
	c = ft_point3d_cross_product(edge_2, vp2);
	if (ft_dot_product(c, normal) < 0)
		return (0);
	sols[0] = t;
	return (1);
}
*/
t_point3d	normal_triangle(t_object obj, t_point3d p, t_line l)
{
	(void)p;
	(void)l;
	t_point3d edge1 = ft_point3d_cmp(obj.object_union.triangle.v2,
			obj.object_union.triangle.v1);
	t_point3d edge2 = ft_point3d_cmp(obj.object_union.triangle.v3,
			obj.object_union.triangle.v1);
	return normalize(ft_point3d_cross_product(edge1, edge2));
}
