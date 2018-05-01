/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/04/30 23:58:07 by lcavalle         ###   ########.fr       */
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
		if (obj.intersect_func(line, obj, &newhit) &&
				((dotprod(newvector(line.o, newhit), line.v) > 0 &&
				magnitude(newvector(line.o, newhit)) <
				magnitude(newvector(line.o, hit->point))) ||
				dotprod(newvector(line.o, hit->point), line.v) < 0))
		{
			hit->point = newhit;
			hit->obj = *(objlist->object);
			hit->normal = hit->obj.normal_func(hit->obj, hit->point);
			hit->bounce = reflection(hit->normal, line.v);
		}
		objlist = objlist->next;
	}
	if (dotprod(newvector(line.o, hit->point), line.v) > 0)
		return (retfree(1, &hit));
	return (retfree(0, &hit));
}
