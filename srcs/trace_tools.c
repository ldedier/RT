/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 06:16:52 by lcavalle          #+#    #+#             */
/*   Updated: 2020/02/06 20:42:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hit				*retfree(int r, t_hit **hit)
{
	if (r != 1)
	{
		free(*hit);
		*hit = NULL;
	}
	return (*hit);
}

t_line				ft_transform_line(t_object object, t_line t)
{
	t_line line;

	line.oldo = t.o;
	line.oldv = t.v;
	line.o = ft_point3d_mat4_mult(t.o, object.transform_pos_inv);
	line.v = normalize(ft_point3d_mat4_mult(t.v, object.transform_dir_inv));
	line.x = t.x;
	line.y = t.y;
	return (line);
}

void				ft_transform_hit_back(t_hit *hit, t_line original)
{
	t_hit tmp;

	tmp = *hit;
	hit->old_point = hit->point;
	hit->old_normal = hit->normal;
	hit->point = ft_point3d_mat4_mult(tmp.point, tmp.obj.transform_pos);
	hit->t = magnitude(newvector(original.o, hit->point));
	hit->normal = normalize(
			ft_point3d_mat4_mult(tmp.normal, tmp.obj.transform_dir));
	hit->pert = normalize(
			ft_point3d_mat4_mult(tmp.pert, tmp.obj.transform_dir));
}

static t_point3d	bump_normal(t_point3d normal, t_point3d point, int color)
{
	t_color		col;
	t_point3d	bumped;
	t_point3d	tangeant;
	t_point3d	bitangeant;
	t_point3d	newp;

	newp = normalize(ft_new_vec3(point.x, 0, point.z));
	tangeant = ft_point3d_cross_product(newp, ft_new_vec3(0, 1, 0));
	bitangeant = ft_point3d_cross_product(tangeant, newp);
	col = get_color(color);
	bumped.x = 2 * (col.r / 255.0) - 1;
	bumped.y = 2 * (col.g / 255.0) - 1;
	bumped.z = 2 * (col.b / 255.0) - 1;
	return (normalize(ft_point3d_add(
				ft_point3d_add(
					ft_point3d_scalar(tangeant, bumped.x),
						ft_point3d_scalar(bitangeant, bumped.y)),
							ft_point3d_scalar(normal, bumped.z))));
}

t_point3d			get_normal(t_object obj, t_hit *hit, t_line line)
{
	hit->unbumped_old_normal = obj.normal_func(obj, hit->point, line);
	if (obj.parser_normal.width == -1)
		return (hit->unbumped_old_normal);
	else
		return (bump_normal(hit->unbumped_old_normal, hit->point,
			get_object_color_normal(hit)));
}
