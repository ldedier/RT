/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/24 01:18:20 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hit		*trace(t_line line, t_objlist *objlist)
{
	t_point3d	newhit;
	t_object	obj;
	t_hit		*hit;

	hit = malloc(sizeof(t_hit));
	hit->point = move(line.o, line.v, -EPSILON);
	while (objlist)
	{
		obj = objlist->object;
		//obj.intersect_func(line, obj, &newhit);
		if (obj.intersect_func(line, obj, &newhit) && 
				((dotprod(newvector(line.o, newhit), line.v) > 0 &&
				 magnitude(newvector(line.o, newhit)) <
				 magnitude(newvector(line.o, hit->point))) ||
				dotprod(newvector(line.o, hit->point), line.v) < 0))
		{
			//printf("dotprod: %f, mag1: %f, mag2: %f\n",dotprod(newvector(line.o, hit.point), line.v), magnitude(newvector(line.o, newhit)) , magnitude(newvector(line.o, hit.point)));fflush(stdout);
			hit->point = newhit;
			hit->obj = objlist->object;
		}
		objlist = objlist->next;
	}
	if (dotprod(newvector(line.o, hit->point), line.v) > 0)
		return (hit);
	return (NULL);
}
