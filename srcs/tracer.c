/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/26 07:32:17 by ldedier          ###   ########.fr       */
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

double				get_smallest_pos_val(int ret, double sols[MAX_DEGREE], double min)
{
	double res;
	int i;

	res = min;
	i = 0;
	while (i < ret)
	{
		if(sols[i] > 0 && (sols[i] < res || res == -1))
			res = sols[i];
		i++;
	}
	return res;
}

void			get_others_values(t_hit *hit);

t_hit				*trace(t_line line, t_cobjlist *cobjlist)
{
	t_hit		newhit;
	t_hit		*hit;
	t_cobject	cobj;
	t_object	obj;
	double		sols[MAX_DEGREE];
	int ret;
	t_line transformed;

	hit = ft_memalloc(sizeof(t_hit));
	hit->t = -1;
	while (cobjlist)
	{
		cobj = *(cobjlist->cobject);
		while (cobj.objlist)
		{
			obj = *(cobj.objlist->object);
			transformed = ft_transform_line(obj, line);
			if ((ret = obj.intersect_func(transformed,
					obj, sols)))
			{
				if ((newhit.t = get_smallest_pos_val(ret, sols, hit->t)) && (
						newhit.t < hit->t || hit->t == -1))
				{
					newhit.obj = obj;
					newhit.point = ft_point3d_add(transformed.o,ft_point3d_scalar(transformed.v, newhit.t));
					newhit.normal = obj.normal_func(obj, newhit.point, transformed);
					
					ft_transform_hit_back(&newhit);
				//	if (newhit.point.y > 0)
				//	{
						*hit = newhit;
						if (ft_dot_product(hit->normal, line.v) > 0)
						{
							hit->enter = 0;
							hit->normal = scale(hit->normal, -1);
						}
						else
							hit->enter = 1;
			//		}
				}
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
