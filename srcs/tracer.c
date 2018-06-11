/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/10 09:33:33 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			trace_triangle(t_object obj, t_line line, t_hit *hit)
{
	t_sols		sols;
	t_hit		newhit;

	if ((sols.nbsols = obj.intersect_func(line, obj, sols.roots)))
	{
		newhit.obj = obj;
		if (((newhit.t = get_smallest_legal_pos_val_t(newhit,
							sols, hit->t, line)) > 0) &&
				(newhit.t < hit->t || hit->t == -1))
		{
			newhit.point = ft_point3d_add(line.o,
					ft_point3d_scalar(line.v, newhit.t));
			newhit.normal = normal_triangle(obj, hit->point, line);
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

static void			trace_object(t_objlist *objlist, t_object obj, t_line line,
		t_hit *hit)
{
	if (obj.intersect_func != intersect_triangle)
	{
		if (!obj.negative)
			intersect_positive(objlist, obj, line, hit);
		else
			intersect_negative(objlist, obj, line, hit);
	}
	else
	{
		trace_triangle(obj, line, hit);
	}
}

static t_hit		*trace_end(t_line line, t_hit *hit)
{
	if (hit->t > 0)
	{
		hit->bounce = reflection(hit->normal, line.v);
		hit->pert = pert_normal(hit);
		hit->pertbounce = reflection(hit->pert, line.v);
		return (retfree(1, &hit));
	}
	return (retfree(0, &hit));
}

t_hit				*trace(t_line line, t_cobjlist *cobjlist)
{
	t_hit		*hit;
	t_cobjlist	*cobjiter;
	t_objlist	*objiter;
	t_objlist	*objlist;

	hit = ft_memalloc(sizeof(t_hit));
	hit->t = -1;
	cobjiter = cobjlist;
	while (cobjiter)
	{
		objiter = cobjiter->cobject->objlist;
		objlist = objiter;
		while (objiter)
		{
			trace_object(objlist, *(objiter->object), line, hit);
			objiter = objiter->next;
		}
		cobjiter = cobjiter->next;
	}
	return (trace_end(line, hit));
}
