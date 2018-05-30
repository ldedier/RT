/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insides.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 12:06:33 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/29 20:38:49 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	inside_sphere(t_hit h, t_object obj)
{
	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	if (h.point.x * h.point.x + h.point.y * h.point.y + h.point.z * h.point.z <
			obj.object_union.sphere.radius * obj.object_union.sphere.radius)
		return (1);
	return (0);
}

int	inside_cone(t_hit h, t_object obj)
{
	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	if (acos(dotprod(normalize(h.point), AXIS_X)) < obj.object_union.cone.angle)
		return (1);
	return (0);
}

int	inside_cylinder(t_hit h, t_object obj)
{
	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	if (h.point.y * h.point.y + h.point.z * h.point.z <
			obj.object_union.cylinder.radius * obj.object_union.cylinder.radius)
		return (1);
	return (0);
}

int	inside_plane(t_hit h, t_object obj)
{
	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	if (dotprod(normalize(h.point), AXIS_Y) > 0)
		return (1);
	return (0);
}

int	inside_ellipsoid(t_hit h, t_object obj)
{
	t_point3d	abc;

	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	abc = obj.object_union.ellipsoid.abc;
	if (h.point.x * h.point.x / abc.x / abc.x +
			h.point.y * h.point.y / abc.y / abc.y +
			h.point.z * h.point.z / abc.z / abc.z < 1)
		return (1);
	return (0);
}
