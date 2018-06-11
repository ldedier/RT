/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_others.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 01:13:42 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 04:04:20 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_motion_others_5(t_world *world, SDL_Event event)
{
	int		i;
	int		x;
	int		y;

	if (world->menu.active_cp >= 0)
	{
		i = world->menu.active_cp;
		x = event.motion.x - world->menu.others_cp[i].pix.x;
		y = event.motion.y - world->menu.others_cp[i].pix.y;
		if (x < 0)
			x = 0;
		else if (x > 99)
			x = 99;
		if (y < 0)
			y = 0;
		else if (y > 99)
			y = 99;
		*(world->menu.others_cp[i].color) = world->menu.color_map[y * 100 + x];
		world->menu.others_cp[i].pos.x = x;
		world->menu.others_cp[i].pos.y = y;
		paint_threaded_fast(world);
	}
}

void	ft_mouse_motion_others_4(t_world *world, float value, int i)
{
	if (value >= world->menu.others_grb[i].min &&
			value <= world->menu.others_grb[i].max)
		*(world->menu.others_grb[i].value) = (int)value;
	else
	{
		if (value < world->menu.others_grb[i].min)
			*(world->menu.others_grb[i].value) =
				world->menu.others_grb[i].min;
		if (value > world->menu.others_grb[i].max)
			*(world->menu.others_grb[i].value) =
				world->menu.others_grb[i].max;
	}
	world->cancel_render = 1;
	join_threads(world);
	paint_threaded_fast(world);
	update_progress_bar(world);
}

void	ft_mouse_motion_others_3(t_world *world, SDL_Event event)
{
	int		i;
	int		nb_val;
	float	step;
	int		value;
	int		j;

	if (world->menu.active_grb >= 0)
	{
		i = world->menu.active_grb;
		nb_val = world->menu.others_grb[i].max - world->menu.others_grb[i].min
			+ 1;
		step = 108 / (float)(nb_val - 1);
		value = ft_clamp(0, event.motion.x - (world->menu.others_grb[i].pix.x
					+ 4), 100);
		j = 0;
		while (((j * step) - (step / 2)) <= value)
			j++;
		if (world->menu.others_grb[i].min == 0 && value < 100)
			j--;
		value = j;
		ft_mouse_motion_others_4(world, value, i);
		return ;
	}
	ft_mouse_motion_others_5(world, event);
}

void	ft_mouse_motion_others_2(t_world *world, float value, int i)
{
	if (value >= world->menu.others_rb[i].min &&
			value <= world->menu.others_rb[i].max)
		*(world->menu.others_rb[i].value) = value;
	else
	{
		if (value < world->menu.others_rb[i].min)
			*(world->menu.others_rb[i].value) =
				world->menu.others_rb[i].min;
		if (value > world->menu.others_rb[i].max)
			*(world->menu.others_rb[i].value) =
				world->menu.others_rb[i].max;
	}
}

void	ft_mouse_motion_others(t_world *world, SDL_Event event)
{
	int		i;
	float	value;

	if (world->menu.active_rb >= 0)
	{
		i = world->menu.active_rb;
		value = ((float)(event.motion.x - (world->menu.others_rb[i].pix.x + 4))
				/ 100) * world->menu.others_rb[i].max;
		ft_mouse_motion_others_2(world, value, i);
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_motion_others_3(world, event);
}
