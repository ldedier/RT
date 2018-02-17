/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/17 04:20:41 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_hit		trace(t_line line, t_objlist *objlist)
{
	t_point3d	hitpoint;
	t_point3d	newhit;

	hit.hitpoint = (t_point3d){.x = -1, .y = -1, .z = -1};
	while (objlist)
	{
		newhit = objlist->object.intersect_func(line, objlist->object);
		if (dotprod(newvector(line.o, newhit), line.v) > 0 &&
				magnitude(newhit) < magnitude(hit))
		{
			hit.point = newhit;
			hit.obj = objlist->object;
		}
		objlist = objlist->next;
	}
	return (hit);
}
