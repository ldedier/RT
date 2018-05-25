/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/24 03:14:37 by lcavalle         ###   ########.fr       */
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
	return line;
}

void				ft_transform_hit_back(t_hit *hit)
{
	t_hit tmp;

	tmp = *hit;
	hit->point = ft_point3d_mat4_mult(tmp.point, tmp.obj.transform_pos);
	hit->normal = normalize(
			ft_point3d_mat4_mult(tmp.normal, tmp.obj.transform_dir));
	hit->pert = normalize(
			ft_point3d_mat4_mult(tmp.pert, tmp.obj.transform_dir));
}

t_hit				*trace(t_line line, t_cobjlist *cobjlist)
{
	t_hit		newhit;
	t_hit		*hit;
	t_cobject	cobj;
	t_object	obj;

	hit = ft_memalloc(sizeof(t_hit));
	hit->t = -1;
	while (cobjlist)
	{
		cobj = *(cobjlist->cobject);
		while (cobj.objlist)
		{
			obj = *(cobj.objlist->object);
			if ((obj.intersect_func(ft_transform_line(obj, line), obj, &newhit))
					&& (newhit.t > 0 && (newhit.t < hit->t || hit->t == -1)))
			{
					newhit.obj = obj;
					ft_transform_hit_back(&newhit);
					*hit = newhit;
			}
			cobj.objlist = cobj.objlist->next;
		}
		cobjlist = cobjlist->next;
	}
	if (hit->t > 0)
	{
		hit->bounce = reflection(hit->normal, line.v);
		hit->pert = pert_normal(hit);
		hit->pertbounce = reflection(hit->pert, line.v);
		return (retfree(1, &hit));
	}
	return (retfree(0, &hit));
}
