/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_others_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 02:18:08 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 02:35:04 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_others_10(t_world *world, int x, int y)
{
	int		x0;

	if (world->exporting_video == 1)
	{
		x0 = world->canvas->win.w + 225;
		if (x >= (x0) && x <= (x0 + world->menu.stop.width) && y >= 751 &&
				y <= (751 + world->menu.stop.height))
		{
			world->exporting_video = 0;
			ft_export_y4m(world->video);
			update_progress_bar(world);
		}
	}
	else
	{
		x0 = world->canvas->win.w + 220;
		if (x >= (x0) && x <= (x0 + world->menu.video.width) && y >= 760 &&
				y <= (760 + world->menu.video.height))
		{
			world->exporting_video = 1;
			update_progress_bar(world);
		}
	}
}

void	ft_mouse_button_others_9(t_world *world, int x, int y)
{
	int		x0;
	int		y0;

	x0 = world->canvas->win.w + 95;
	y0 = 750;
	if (x >= (x0) && x <= (x0 + world->menu.photo.width) && y >= (y0) &&
			y <= (y0 + world->menu.photo.height))
	{
		ft_export_rt(world, ".ppm");
		return ;
	}
	x0 = world->canvas->win.w + 345;
	y0 = 752;
	if (x >= (x0) && x <= (x0 + world->menu.save.width) && y >= (y0) &&
			y <= (y0 + world->menu.save.height))
	{
		ft_export_scene(world);
		return ;
	}
	ft_mouse_button_others_10(world, x, y);
}

void	ft_mouse_button_others_8(t_world *world, int x, int y)
{
	int		x0;
	int		y0;

	x0 = world->canvas->win.w + 75;
	y0 = 565;
	if (x >= (x0) && x <= (x0 + world->menu.cartoon.width) && y >= (y0) &&
			y <= (y0 + world->menu.cartoon.height))
	{
		if (world->shader == 2)
			world->shader = 1;
		else
			world->shader = 2;
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_others_9(world, x, y);
}

void	ft_mouse_button_others_7(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		y0;

	i = 0;
	while (i < world->menu.nb_others_cp)
	{
		x0 = world->menu.others_cp[i].pix.x;
		y0 = world->menu.others_cp[i].pix.y;
		if (x >= (x0) && x <= (x0 + 100) && y >= (y0) && y <= (y0 + 100))
		{
			world->menu.active_cp = i;
			ft_mouse_motion(world, event);
			return ;
		}
		i++;
	}
	ft_mouse_button_others_8(world, x, y);
}

void	ft_mouse_button_others_6(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		x1;
	int		y0;

	i = 0;
	while (i < world->menu.nb_others_grb)
	{
		x0 = world->menu.others_grb[i].pix.x;
		x1 = x0 + 108;
		y0 = world->menu.others_grb[i].pix.y;
		if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) && y <= (y0 - 3 + 12))
		{
			world->menu.active_grb = i;
			ft_mouse_motion(world, event);
			return ;
		}
		i++;
	}
	ft_mouse_button_others_7(world, event, x, y);
}
