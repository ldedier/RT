/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 23:03:33 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 09:02:41 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	castshadows(t_world *world, t_hit *hit, t_line **srays)
{
	t_hit	*shit;
	int		i;

	i = 0;
	while (i < world->nlights)
	{
		srays[i] = ft_memalloc(sizeof(t_line));
		if (world->lights[i].type != 'd')
			srays[i]->v = normalize(newvector(hit->point, world->lights[i].o));
		else
			srays[i]->v = normalize(scale(world->lights[i].o, -1.0));
		srays[i]->o = translate_vec(hit->point, hit->normal,
				EPSILON * proj(hit->normal, hit->bounce));
		if (((shit = trace(*(srays[i]), world->objlist)) &&
				((world->lights[i].type != 'd' &&
				magnitude(newvector(srays[i]->o, shit->point)) <
				magnitude(newvector(hit->point, world->lights[i].o))) ||
				world->lights[i].type == 'd')) ||
				(world->lights[i].type == 's' &&
				acos(dotprod(normalize(scale(srays[i]->v, -1)),
						world->lights[i].v)) > world->lights[i].angle))
		{
			free(srays[i]);
			srays[i] = NULL;
		}
		free(shit);
		i++;
	}
}
