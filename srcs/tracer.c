/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 06:13:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_point3d	reflection(t_point3d n, t_point3d v)
{
	t_point3d	r;
	double		aux;

	aux = 2 * dotprod(v, n);
	r.x = v.x - n.x * aux;
	r.y = v.y - n.y * aux;
	r.z = v.z - n.z * aux;
	return (r);
}

t_hit				*retfree(int r, t_hit **hit)
{
	if (!r)
	{
		free(*hit);
		*hit = NULL;
	}
	return (*hit);
}

void				ft_transform_line(t_line *line, t_object object)
{
//	ft_print_mat4(object.transform_pos_inv);
	line->o = ft_point3d_mat4_mult(line->o, object.transform_pos_inv);
	line->v = normalize(ft_point3d_mat4_mult(line->v,
				object.transform_dir_inv));
}

void				ft_transform_hit_back(t_hit *hit)
{
	hit->point = ft_point3d_mat4_mult(hit->point, hit->obj.transform_pos);
	hit->normal = ft_point3d_mat4_mult(hit->normal, hit->obj.transform_dir);
}

t_hit				*trace(t_line line, t_objlist *objlist)
{
	t_point3d	newhit;
	t_object	obj;
	t_hit		*hit;
	
	hit = malloc(sizeof(t_hit));
	hit->point = translate_vec(line.o, line.v, -EPSILON);
	while (objlist)
	{
		obj = *(objlist->object);
//		ft_transform_line(&line, obj);
		if (obj.intersect_func(line, obj, &newhit) &&
				((dotprod(newvector(line.o, newhit), line.v) > 0 &&
				magnitude(newvector(line.o, newhit)) <
				magnitude(newvector(line.o, hit->point))) ||
				dotprod(newvector(line.o, hit->point), line.v) < 0))
		{
			hit->point = newhit;
			hit->obj = *(objlist->object);
			hit->normal = hit->obj.normal_func(hit->obj, hit->point);
		//	ft_transform_hit_back(hit);
			hit->bounce = reflection(hit->normal, line.v);
		}
		objlist = objlist->next;
	}
	if (dotprod(newvector(line.o, hit->point), line.v) > 0)
		return (retfree(1, &hit));
	return (retfree(0, &hit));
}
