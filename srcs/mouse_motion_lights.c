/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_lights.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 01:12:41 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 04:23:15 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_motion_lights_5(t_world *world, SDL_Event event)
{
	int		new_pos;

	if (world->menu.scroll_lights.active == 1)
	{
		new_pos = event.motion.y - 140 - world->menu.scroll_lights.step;
		if (new_pos < 0)
			new_pos = 0;
		else if ((new_pos + world->menu.scroll_lights.height)
				> (world->menu.scroll_lights.len - 10))
			new_pos = world->menu.scroll_lights.len - 10
				- world->menu.scroll_lights.height;
		world->menu.scroll_lights.pos = new_pos;
		update_progress_bar(world);
	}
}

void	ft_mouse_motion_lights_4(t_world *world, SDL_Event event)
{
	int		i;
	int		x;
	int		y;

	if (world->menu.active_cp >= 0)
	{
		i = world->menu.active_cp;
		x = event.motion.x - world->menu.lights_cp[i].pix.x;
		y = event.motion.y - world->menu.lights_cp[i].pix.y;
		if (x < 0)
			x = 0;
		else if (x > 99)
			x = 99;
		if (y < 0)
			y = 0;
		else if (y > 99)
			y = 99;
		*(world->menu.lights_cp[i].color) = world->menu.color_map[y * 100 + x];
		world->menu.lights_cp[i].pos.x = x;
		world->menu.lights_cp[i].pos.y = y;
		paint_threaded_fast(world);
		return ;
	}
	ft_mouse_motion_lights_5(world, event);
}

void	ft_mouse_motion_lights_3(t_world *world, float value, int i)
{
	if (value >= world->menu.lights_rb[i].min &&
			value <= world->menu.lights_rb[i].max)
		*(world->menu.lights_rb[i].value) = value - 1;
	else
	{
		if (value < world->menu.lights_rb[i].min)
			*(world->menu.lights_rb[i].value) =
				world->menu.lights_rb[i].min - 1;
		if (value > world->menu.lights_rb[i].max)
			*(world->menu.lights_rb[i].value) =
				world->menu.lights_rb[i].max - 1;
	}
}

void	ft_mouse_motion_lights_2(t_world *world, float value, int i)
{
	if (value >= world->menu.lights_rb[i].min &&
			value <= world->menu.lights_rb[i].max)
		*(world->menu.lights_rb[i].value) = value;
	else
	{
		if (value < world->menu.lights_rb[i].min)
			*(world->menu.lights_rb[i].value) =
				world->menu.lights_rb[i].min;
		if (value > world->menu.lights_rb[i].max)
			*(world->menu.lights_rb[i].value) =
				world->menu.lights_rb[i].max;
	}
}

void	ft_mouse_motion_lights(t_world *world, SDL_Event event)
{
	int		i;
	float	value;

	if (world->menu.active_rb >= 0)
	{
		i = world->menu.active_rb;
		value = ((float)(event.motion.x - (world->menu.lights_rb[i].pix.x + 4))
				/ 100) * world->menu.lights_rb[i].max;
		if (i <= 1)
			ft_mouse_motion_lights_2(world, value, i);
		else
			ft_mouse_motion_lights_3(world, value, i);
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_motion_lights_4(world, event);
}
