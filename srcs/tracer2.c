/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:48:49 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/29 17:30:10 by lcavalle         ###   ########.fr       */
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
							transformed, objlist, 1, &other)) > 0) && (newhit.t < hit->t || hit->t == -1))
		{
			newhit.point = ft_point3d_add(transformed.o,
					ft_point3d_scalar(transformed.v, newhit.t));
				newhit.normal = obj.normal_func(obj, newhit.point, transformed);
				ft_transform_hit_back(&newhit);
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
							transformed, objlist, 0, &other)) > 0) && (newhit.t < hit->t || hit->t == -1))
		{
			newhit.point = ft_point3d_add(transformed.o,ft_point3d_scalar(transformed.v, newhit.t));
				newhit.normal = obj.normal_func(obj, newhit.point, transformed);
				newhit.obj.c = other.c;
				newhit.obj.pert = other.pert;
				newhit.obj.shine = other.shine;
				newhit.obj.reflect = other.reflect;
				newhit.obj.refract = other.refract;
				newhit.obj.transp = other.transp;
				ft_transform_hit_back(&newhit);
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
