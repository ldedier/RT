/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_lights_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 02:49:47 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 02:51:41 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_lights_8(t_world *world, int x, int y, int y0)
{
	int		x0;

	x0 = world->canvas->win.w + 105 + 230;
	if (x >= (x0) && x <= (x0 + 60) && y >= (y0) && y <= (y0 + 60))
	{
		world->lights[world->menu.active_light].type = 'd';
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
}

void	ft_mouse_button_lights_7(t_world *world, int x, int y)
{
	int		x0;
	int		y0;

	y0 = 765;
	x0 = world->canvas->win.w + 105;
	if (x >= (x0) && x <= (x0 + 60) && y >= (y0) && y <= (y0 + 60))
	{
		world->lights[world->menu.active_light].type = 'p';
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	x0 = world->canvas->win.w + 105 + 115;
	if (x >= (x0) && x <= (x0 + 60) && y >= (y0) && y <= (y0 + 60))
	{
		world->lights[world->menu.active_light].type = 's';
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_lights_8(world, x, y, y0);
}

void	ft_mouse_button_lights_6(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		y0;

	i = 0;
	while (i < world->menu.nb_lights_cp)
	{
		x0 = world->menu.lights_cp[i].pix.x;
		y0 = world->menu.lights_cp[i].pix.y;
		if (x >= (x0) && x <= (x0 + 100) && y >= (y0) && y <= (y0 + 100))
		{
			world->menu.active_cp = i;
			ft_mouse_motion(world, event);
			return ;
		}
		i++;
	}
	ft_mouse_button_lights_7(world, x, y);
}
