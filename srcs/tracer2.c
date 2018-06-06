/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:48:49 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/06 06:41:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_inside_other(t_hit h, t_objlist *objlist, int neg,
		t_object *other)
{
	t_objlist	*objiter;
	t_object	obj;
	int			negated;

	negated = 0;
		objiter = objlist;
		while (objiter && !negated)
		{
			obj = *(objiter->object);
			if (obj.negative == neg && obj.inside_func(h, obj))
			{
				negated = 1;
				*other = obj;
			}
			objiter = objiter->next;
		}
	return (negated);
}

t_point3d	bump_normal(t_point3d normal, t_point3d point, int color)
{
	t_color col;
	t_point3d bumped;
	t_point3d tangeant;
	t_point3d bitangeant;
	t_point3d newp;

	newp= normalize(ft_new_vec3(point.x, 0, point.z));
	tangeant = ft_point3d_cross_product(newp, ft_new_vec3(0, 1, 0));
	bitangeant = ft_point3d_cross_product(tangeant, newp);
	
	col = get_color(color);
	bumped.x = 2 * (col.r / 255.0) - 1;
	bumped.y = 2 * (col.g / 255.0) - 1;
	bumped.z = 2 * (col.b / 255.0) - 1;
	//printf("%f\n", bumped.z);
		
	return (normalize(ft_point3d_add(
				ft_point3d_add(
					ft_point3d_scalar(tangeant, bumped.x),
						ft_point3d_scalar(bitangeant, bumped.y)),
							ft_point3d_scalar(normal, bumped.z)
				)));
}

t_point3d	get_normal(t_object obj, t_hit *hit, t_line line)
{
	hit->unbumped_old_normal = obj.normal_func(obj, hit->point, line);
	if (obj.parser_normal.width == -1)
		return (hit->unbumped_old_normal);
	else
		return (bump_normal(hit->unbumped_old_normal, hit->point,
			get_object_color_normal(hit)));
}

void	intersect_positive(t_objlist *objlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit		newhit;
	t_object	other;
	t_sols		sols;
	t_line		transformed;

	transformed = ft_transform_line(obj, line);
	if ((sols.nbsols = obj.intersect_func(transformed,
					obj, sols.roots)))
	{
		newhit.obj = obj;
		if (((newhit.t = get_smallest_legal_pos_val(newhit, sols, hit->t,
							transformed, objlist, 1, &other)) > 0))
		{
			newhit.point = ft_point3d_add(transformed.o,
					ft_point3d_scalar(transformed.v, newhit.t));
			newhit.normal = get_normal(obj, &newhit, transformed);
			ft_transform_hit_back(&newhit, line);
			if (newhit.t < hit->t || hit->t == -1)
			{
				*hit = newhit;
				if (ft_dot_product(hit->normal, line.v) > 0)
				{
					hit->enter = 0;
					hit->normal = scale(hit->normal, -1);
				}
				else
					hit->enter = 1;
			}
		}
	}
}

void	intersect_negative(t_objlist *objlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit		newhit;
	t_object	other;
	t_sols		sols;
	t_line		transformed;

	transformed = ft_transform_line(obj, line);
	if ((sols.nbsols = obj.intersect_func(transformed,
					obj, sols.roots)))
	{
		newhit.obj = obj;
		if (((newhit.t = get_smallest_legal_pos_val(newhit, sols, hit->t,
							transformed, objlist, 0, &other)) > 0))
		{
			newhit.point = ft_point3d_add(transformed.o,ft_point3d_scalar(transformed.v, newhit.t));
				newhit.normal = get_normal(obj, &newhit, transformed);
				newhit.obj.c = other.c;
				newhit.obj.pert = other.pert;
				newhit.obj.shine = other.shine;
				newhit.obj.reflect = other.reflect;
				newhit.obj.refract = other.refract;
				newhit.obj.transp = other.transp;
				ft_transform_hit_back(&newhit, line);
				if (newhit.t < hit->t || hit->t == -1)
				{
				*hit = newhit;
				if (ft_dot_product(hit->normal, line.v) > 0)
				{
					hit->enter = 0;
					hit->normal = scale(hit->normal, -1);
				}
				else
					hit->enter = 1;
		}
		}
	}
}
