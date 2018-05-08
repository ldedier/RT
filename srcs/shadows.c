/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 23:03:33 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/08 00:15:47 by ldedier          ###   ########.fr       */
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
		srays[i]->v = normalize(newvector(hit->point, world->lights[i].o));
		srays[i]->o = translate_vec(hit->point, hit->normal,
				EPSILON * proj(hit->normal, hit->bounce));
		if ((shit = trace(*(srays[i]), world->objlist, 0)) &&
				magnitude(newvector(srays[i]->o, shit->point)) <
				magnitude(newvector(hit->point, world->lights[i].o)))
		{
			free(srays[i]);
			srays[i] = NULL;
		}
		free(shit);
		i++;
	}
}
