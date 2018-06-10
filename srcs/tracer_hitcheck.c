/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_hitcheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 06:19:49 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/10 09:38:13 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_point3d	izokay_relative_pos(t_hit *newhit, double sol,
		t_line transformed)
{
	t_point3d	relative_pos;

	relative_pos = ft_point3d_add(transformed.o,
			ft_point3d_scalar(transformed.v, sol));
	newhit->point = ft_point3d_add(transformed.o,
			ft_point3d_scalar(transformed.v, sol));
	newhit->normal = newhit->obj.normal_func(newhit->obj,
			newhit->point, transformed);
	return (relative_pos);
}

int					izokay(t_hit newhit, double sol, t_line transformed)
{
	t_list		*ptr;
	t_point3d	relative_pos;
	t_point3d	absolute_pos;
	t_point3d	point;
	t_cut		cut;

	if (ft_lstlength(newhit.obj.cuts) == 0)
		return (1);
	ptr = newhit.obj.cuts;
	relative_pos = izokay_relative_pos(&newhit, sol, transformed);
	absolute_pos = ft_point3d_mat4_mult(relative_pos, newhit.obj.transform_pos);
	while (ptr != NULL)
	{
		cut = *((t_cut *)(ptr->content));
		if (cut.relative)
			point = relative_pos;
		else
			point = absolute_pos;
		if (ft_evaluate_cut(cut, point, newhit) == 1)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

int					izokay_t(t_hit newhit, double sol, t_line line)
{
	t_list		*ptr;
	t_point3d	absolute_pos;
	t_cut		cut;

	if (ft_lstlength(newhit.obj.cuts) == 0)
		return (1);
	ptr = newhit.obj.cuts;
	absolute_pos = ft_point3d_add(line.o, ft_point3d_scalar(line.v, sol));
	while (ptr != NULL)
	{
		cut = *((t_cut *)(ptr->content));
		if (ft_evaluate_cut(cut, absolute_pos, newhit) == 1)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

double				get_smallest_legal_pos_val(t_hit newhit, t_sols sols,
		double min, t_auxtracer aux)
{
	double	res;
	int		i;

	res = min + EPSILON2;
	i = 0;
	while (i < sols.nbsols)
	{
		if (sols.roots[i] > 0 && (sols.roots[i] < res || equal_double(res, -1)))
		{
			newhit.point = ft_point3d_add(aux.transformed.o, ft_point3d_scalar(
						aux.transformed.v, sols.roots[i]));
			if (izokay(newhit, sols.roots[i], aux.transformed) && ((aux.neg ?
							!is_inside_other(newhit, aux.objlist,
								aux.neg, aux.other) :
							is_inside_other(newhit, aux.objlist,
								aux.neg, aux.other))))
				res = sols.roots[i];
		}
		i++;
	}
	return (res);
}

double				get_smallest_legal_pos_val_t(t_hit newhit, t_sols sols,
		double min, t_line line)
{
	double	res;
	int		i;

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
