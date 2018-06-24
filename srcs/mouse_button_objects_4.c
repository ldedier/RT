/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_objects_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 03:27:22 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 03:28:43 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_objects_18(t_world *world, int x, int y, int y0)
{
	int		x0;

	x0 = world->canvas->win.w + 40 + 25 + 15 + 6 * 50;
	if (x >= (x0) && x <= (x0 + 40) && y >= (y0) && y <= (y0 + 40))
	{
		if (world->selected_cobject->id == world->menu.active_object)
			world->selected_cobject->pert = e_marble;
		else
			world->selected_object->pert = e_marble;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
}

void	ft_mouse_button_objects_17(t_world *world, int x, int y, int y0)
{
	int		x0;

	x0 = world->canvas->win.w + 40 + 25 + 15 + 5 * 50;
	if (x >= (x0) && x <= (x0 + 40) && y >= (y0) && y <= (y0 + 40))
	{
		if (world->selected_cobject->id == world->menu.active_object)
			world->selected_cobject->pert = e_perlin;
		else
			world->selected_object->pert = e_perlin;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_objects_18(world, x, y, y0);
}

void	ft_mouse_button_objects_16(t_world *world, int x, int y, int y0)
{
	int		x0;

	x0 = world->canvas->win.w + 40 + 25 + 15 + 4 * 50;
	if (x >= (x0) && x <= (x0 + 40) && y >= (y0) && y <= (y0 + 40))
	{
		if (world->selected_cobject->id == world->menu.active_object)
			world->selected_cobject->pert = e_chess;
		else
			world->selected_object->pert = e_chess;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_objects_17(world, x, y, y0);
}
