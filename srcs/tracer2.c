/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 09:48:49 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/27 21:01:23 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_inside_other(t_hit h, t_cobjlist *cobjlist, int neg,
		t_color *c)
{
	t_cobjlist	*cobjiter;
	t_objlist	*objiter;
	t_object	obj;
	int			negated;

	negated = 0;
	cobjiter = cobjlist;
	while (cobjiter && !negated)
	{
		objiter = cobjiter->cobject->objlist;
		while (objiter && !negated)
		{
			obj = *(objiter->object);
			if (obj.negative == neg && obj.inside_func(h, obj))
				negated = 1;
			*c = obj.c;
			objiter = objiter->next;
		}
		cobjiter = cobjiter->next;
	}
	return (negated);
}

void	intersect_positive(t_cobjlist *cobjlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit		newhit;
	t_color		othercol;

	if ((obj.intersect_func(ft_transform_line(obj, line), obj, &newhit)) &&
			(newhit.t > 0 && (newhit.t < hit->t || hit->t == -1)))
	{
		newhit.obj = obj;
		if (!is_inside_other(newhit, cobjlist, 1, &othercol))
		{
			newhit.col = obj.c;
			ft_transform_hit_back(&newhit);
			*hit = newhit;
		}
	}
}

void	intersect_negative(t_cobjlist *cobjlist, t_object obj, t_line line,
		t_hit *hit)
{
	t_hit		newhit;
	t_color		othercol;

	if ((obj.intersect_func(ft_transform_line(obj, line), obj, &newhit)) &&
			(newhit.t > 0 && (newhit.t < hit->t || hit->t == -1)))
	{
		newhit.obj = obj;
		if (is_inside_other(newhit, cobjlist, 0, &othercol))
		{
			newhit.col = othercol;
			ft_transform_hit_back(&newhit);
			*hit = newhit;
		}
	}
}
