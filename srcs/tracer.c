/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/27 06:17:29 by ldedier          ###   ########.fr       */
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

int					izokay(t_hit newhit, double sol, t_line transformed)
{
	t_list *ptr;
	t_point3d relative_pos;
	t_point3d absolute_pos;
	t_point3d point;
	t_cut cut;

	if (ft_lstlength(newhit.obj.cuts) == 0)
		return (1);
	ptr = newhit.obj.cuts;
	relative_pos = ft_point3d_add(transformed.o,ft_point3d_scalar(transformed.v, sol));
	absolute_pos = ft_point3d_mat4_mult(relative_pos, newhit.obj.transform_pos);
	while (ptr != NULL)
	{
		cut = *((t_cut *)(ptr->content));
		if (cut.relative)
			point = relative_pos;
		else
			point = absolute_pos;
		if (ft_evaluate_cut(cut, point) == 1)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

int					izokay_t(t_hit newhit, double sol, t_line line)
{
	t_list *ptr;
	t_point3d absolute_pos;
	t_cut cut;

	if (ft_lstlength(newhit.obj.cuts) == 0)
		return (1);
	ptr = newhit.obj.cuts;
	absolute_pos = ft_point3d_add(line.o,ft_point3d_scalar(line.v, sol));
	while (ptr != NULL)
	{
		cut = *((t_cut *)(ptr->content));
		if (ft_evaluate_cut(cut, absolute_pos) == 1)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

double				get_smallest_legal_pos_val(t_hit newhit, t_sols sols,
		double min, t_line transformed)
{
	double res;
	int i;
	
	res = min;
	i = 0;
	while (i < sols.nbsols)
	{
		if (sols.roots[i] > 0 && (sols.roots[i] < res || res == -1) &&
				izokay(newhit, sols.roots[i], transformed))
			res = sols.roots[i];
		i++;
	}
	return (res);
}

double				get_smallest_legal_pos_val_t(t_hit newhit, t_sols sols,
		double min, t_line line)
{
	double res;
	int i;

	res = min;
	i = 0;
	while (i < sols.nbsols)
	{
		if (sols.roots[i] > 0 && (sols.roots[i] < res || res == -1) &&
				izokay_t(newhit, sols.roots[i], line))
			res = sols.roots[i];
		i++;
	}
	return (res);
}

t_hit				*trace(t_line line, t_cobjlist *cobjlist)
{
	t_hit		newhit;
	t_hit		*hit;
	t_cobject	cobj;
	t_object	obj;
	t_sols		sols;
	t_line transformed;

	hit = ft_memalloc(sizeof(t_hit));
	hit->t = -1;
	while (cobjlist)
	{
		cobj = *(cobjlist->cobject);
		while (cobj.objlist)
		{
			obj = *(cobj.objlist->object);
			if (obj.intersect_func != intersect_triangle)
			{
				transformed = ft_transform_line(obj, line);
				if ((sols.nbsols = obj.intersect_func(transformed,
								obj, sols.roots)))
				{
					newhit.obj = obj;
					if (((newhit.t =
									get_smallest_legal_pos_val(newhit, sols, hit->t, transformed)) > 0) &&
							(newhit.t < hit->t || hit->t == -1))
					{
						newhit.point = ft_point3d_add(transformed.o,ft_point3d_scalar(transformed.v, newhit.t));
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
			else
			{
				if ((sols.nbsols = obj.intersect_func(line,
								obj, sols.roots)))
				{
					newhit.obj = obj;
					if (((newhit.t =
						get_smallest_legal_pos_val_t(newhit, sols, hit->t, line)) > 0) &&
							(newhit.t < hit->t || hit->t == -1))
					{
						newhit.point = ft_point3d_add(line.o,ft_point3d_scalar(line.v, newhit.t));
						newhit.normal = normal_triangle(obj);
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
