/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 06:58:15 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 06:58:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_key_event6(t_world *e, SDL_Event event, int press)
{
	if (event.key.keysym.sym == SDLK_y)
	{
		if (press == 1)
		{
			if (e->can_export)
			{
				ft_export_scene(e);
				e->can_export = 0;
			}
		}
		else
			e->can_export = 1;
	}
}
