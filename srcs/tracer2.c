/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:48:49 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/10 09:39:58 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			is_inside_other(t_hit h, t_objlist *objlist, int neg,
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

static void	intersect_positive2(t_hit *newhit, t_line line, t_auxtracer2 aux,
		t_hit *hit)
{
	newhit->point = ft_point3d_add(aux.auxtracer.transformed.o,
			ft_point3d_scalar(aux.auxtracer.transformed.v, newhit->t));
	newhit->normal = get_normal(aux.obj, newhit, aux.auxtracer.transformed);
	ft_transform_hit_back(newhit, line);
	if (newhit->t < hit->t || hit->t == -1)
	{
		*hit = *newhit;
		if (ft_dot_product(hit->normal, line.v) > 0)
		{
			hit->enter = 0;
			hit->normal = scale(hit->normal, -1);
		}
		else
			hit->enter = 1;
	}
}

void		intersect_positive(t_objlist *objlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit			newhit;
	t_object		other;
	t_sols			sols;
	t_auxtracer2	aux;

	aux.auxtracer.transformed = ft_transform_line(obj, line);
	aux.auxtracer.neg = 1;
	aux.auxtracer.other = &other;
	aux.auxtracer.objlist = objlist;
	aux.obj = obj;
	if ((sols.nbsols = obj.intersect_func(aux.auxtracer.transformed,
					obj, sols.roots)))
	{
		newhit.obj = obj;
		if (((newhit.t = get_smallest_legal_pos_val(newhit, sols, hit->t,
							aux.auxtracer)) > 0))
			intersect_positive2(&newhit, line, aux, hit);
	}
}

static void	intersect_negative2(t_hit *newhit, t_line line, t_auxtracer2 aux,
		t_hit *hit)
{
	newhit->point = ft_point3d_add(aux.auxtracer.transformed.o,
			ft_point3d_scalar(aux.auxtracer.transformed.v, newhit->t));
	newhit->normal = get_normal(aux.obj, newhit, aux.auxtracer.transformed);
	newhit->obj.c = aux.auxtracer.other->c;
	newhit->obj.pert = aux.auxtracer.other->pert;
	newhit->obj.shine = aux.auxtracer.other->shine;
	newhit->obj.reflect = aux.auxtracer.other->reflect;
	newhit->obj.refract = aux.auxtracer.other->refract;
	newhit->obj.transp = aux.auxtracer.other->transp;
	ft_transform_hit_back(newhit, line);
	if (newhit->t < hit->t || hit->t == -1)
	{
		*hit = *newhit;
		if (ft_dot_product(hit->normal, line.v) > 0)
		{
			hit->enter = 0;
			hit->normal = scale(hit->normal, -1);
		}
		else
			hit->enter = 1;
	}
}

void		intersect_negative(t_objlist *objlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit			newhit;
	t_object		other;
	t_sols			sols;
	t_auxtracer2	aux;

	aux.auxtracer.transformed = ft_transform_line(obj, line);
	aux.auxtracer.neg = 0;
	aux.auxtracer.other = &other;
	aux.auxtracer.objlist = objlist;
	aux.obj = obj;
	if ((sols.nbsols = obj.intersect_func(aux.auxtracer.transformed,
					obj, sols.roots)))
	{
		newhit.obj = obj;
		if (((newhit.t = get_smallest_legal_pos_val(newhit, sols, hit->t,
							aux.auxtracer)) > 0))
			intersect_negative2(&newhit, line, aux, hit);
	}
}
