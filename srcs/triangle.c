/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 04:34:03 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 04:09:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			intersect_triangle(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	t_aux_triangle x;

	x.edge1 = ft_point3d_cmp(obj.object_union.triangle.v2,
			obj.object_union.triangle.v1);
	x.edge2 = ft_point3d_cmp(obj.object_union.triangle.v3,
			obj.object_union.triangle.v1);
	x.normal = ft_point3d_cross_product(line.v, x.edge2);
	x.a = ft_dot_product(x.edge1, x.normal);
	if (x.a > -EPSILON && x.a < EPSILON)
		return (0);
	x.f = 1 / x.a;
	x.s = ft_point3d_cmp(line.o, obj.object_union.triangle.v1);
	x.u = x.f * ft_dot_product(x.s, x.normal);
	if (x.u < 0 || x.u > 1)
		return (0);
	x.q = ft_point3d_cross_product(x.s, x.edge1);
	x.v = x.f * ft_dot_product(line.v, x.q);
	if (x.v < 0 || x.u + x.v > 1)
		return (0);
	sols[0] = x.f * ft_dot_product(x.edge2, x.q);
	return (1);
}

t_point3d	normal_triangle(t_object obj, t_point3d p, t_line l)
{
	t_point3d edge1;
	t_point3d edge2;

	(void)p;
	(void)l;
	edge1 = ft_point3d_cmp(obj.object_union.triangle.v2,
			obj.object_union.triangle.v1);
	edge2 = ft_point3d_cmp(obj.object_union.triangle.v3,
			obj.object_union.triangle.v1);
	return (normalize(ft_point3d_cross_product(edge1, edge2)));
}
