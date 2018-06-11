/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_objects_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 04:30:46 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 04:30:57 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_motion_objects_6(t_world *world, SDL_Event event)
{
	int		new_pos;

	if (world->menu.scroll_objects.active == 1)
	{
		new_pos = event.motion.y - 140 - world->menu.scroll_objects.step;
		if (new_pos < 0)
			new_pos = 0;
		else if ((new_pos + world->menu.scroll_objects.height) >
				(world->menu.scroll_objects.len - 10))
			new_pos = world->menu.scroll_objects.len - 10
				- world->menu.scroll_objects.height;
		world->menu.scroll_objects.pos = new_pos;
		update_progress_bar(world);
	}
}
