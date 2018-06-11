/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insides2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:34:25 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 08:32:49 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	inside_torus(t_hit h, t_object obj)
{
	double	radic;
	double	square;

	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	radic = h.point.x * h.point.x + h.point.y * h.point.y;
	square = obj.object_union.torus.big_rad - sqrt(radic);
	if (square * square + h.point.z * h.point.z <
			obj.object_union.torus.small_rad * obj.object_union.torus.small_rad)
		return (1);
	return (0);
}

int	inside_paraboloid(t_hit h, t_object obj)
{
	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	if (h.point.y * h.point.y + h.point.z * h.point.z < h.point.x)
		return (1);
	return (0);
}

int	inside_hyperboloid(t_hit h, t_object obj)
{
	h.point = ft_point3d_mat4_mult(h.point, h.obj.transform_pos);
	h.point = ft_point3d_mat4_mult(h.point, obj.transform_pos_inv);
	if (h.point.y * h.point.y + h.point.z * h.point.z - h.point.x * h.point.x <
			0)
		return (1);
	return (0);
}

int	inside_goursat(t_hit h, t_object obj)
{
	(void)h;
	(void)obj;
	return (0);
}
