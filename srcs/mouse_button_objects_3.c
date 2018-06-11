/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_objects_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 03:26:57 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 03:29:43 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_objects_15(t_world *world, int x, int y, int y0)
{
	int		x0;

	x0 = world->canvas->win.w + 40 + 25 + 15 + 3 * 50;
	if (x >= (x0) && x <= (x0 + 40) && y >= (y0) && y <= (y0 + 40))
	{
		if (world->selected_cobject->id == world->menu.active_object)
			world->selected_cobject->pert = e_noise;
		else
			world->selected_object->pert = e_noise;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_objects_16(world, x, y, y0);
}

void	ft_mouse_button_objects_14(t_world *world, int x, int y, int y0)
{
	int		x0;

	x0 = world->canvas->win.w + 40 + 25 + 15 + 2 * 50;
	if (x >= (x0) && x <= (x0 + 40) && y >= (y0) && y <= (y0 + 40))
	{
		if (world->selected_cobject->id == world->menu.active_object)
			world->selected_cobject->pert = e_waves;
		else
			world->selected_object->pert = e_waves;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_objects_15(world, x, y, y0);
}

void	ft_mouse_button_objects_13(t_world *world, int x, int y, int y0)
{
	int		x0;

	x0 = world->canvas->win.w + 40 + 25 + 15 + 1 * 50;
	if (x >= (x0) && x <= (x0 + 40) && y >= (y0) && y <= (y0 + 40))
	{
		if (world->selected_cobject->id == world->menu.active_object)
			world->selected_cobject->pert = e_ripple;
		else
			world->selected_object->pert = e_ripple;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_objects_14(world, x, y, y0);
}

void	ft_mouse_button_objects_12(t_world *world, int x, int y)
{
	int		x0;
	int		y0;

	y0 = 135 + 265 + 20 + 20 + 60 + 60 + 170 + 20 + 25 + 15;
	x0 = world->canvas->win.w + 40 + 25 + 15 + 0 * 50;
	if (x >= (x0) && x <= (x0 + 40) && y >= (y0) && y <= (y0 + 40))
	{
		if (world->selected_cobject->id == world->menu.active_object)
			world->selected_cobject->pert = e_none;
		else
			world->selected_object->pert = e_none;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_objects_13(world, x, y, y0);
}

void	ft_mouse_button_objects_11(t_world *world)
{
	if (world->selected_cobject->id == world->menu.active_object)
	{
		if (world->selected_cobject->negative)
			world->selected_cobject->negative = 0;
		else
			world->selected_cobject->negative = 1;
	}
	else
	{
		if (world->selected_object->negative)
			world->selected_object->negative = 0;
		else
			world->selected_object->negative = 1;
	}
}
