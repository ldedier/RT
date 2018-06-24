/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 01:14:36 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 03:34:10 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_objects_5(t_world *world, int i)
{
	world->menu.active_object = world->menu.objects[i].x;
	ft_set_selected_object(world, world->menu.active_object);
	if (world->selected_cobject->id == world->menu.active_object)
		ft_mouse_button_objects_6(world);
	else
		ft_mouse_button_objects_7(world);
	update_progress_bar(world);
}

void	ft_mouse_button_objects_4(t_world *world, int *x0, int *x1, int i)
{
	if (world->menu.objects[i].y == 0)
	{
		*x0 = world->canvas->win.w + 55;
		*x1 = *x0 + 360;
	}
	else
	{
		*x0 = world->canvas->win.w + 55 + 40;
		*x1 = *x0 + 360 - 40;
	}
}

void	ft_mouse_button_objects_3(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		x1;
	int		y0;
	int		y1;

	i = 0;
	y0 = world->menu.first_object;
	while (i < world->menu.nb_objects)
	{
		ft_mouse_button_objects_4(world, &x0, &x1, i);
		y1 = y0 + i * (50 + 15);
		if (x >= (x0) && x <= (x1) && y >= (y1) && y <= (y1 + 50))
		{
			ft_mouse_button_objects_5(world, i);
			return ;
		}
		i++;
	}
	ft_mouse_button_objects_8(world, event, x, y);
}

void	ft_mouse_button_objects_2(t_world *world, SDL_Event event, int x, int y)
{
	int		x0;
	int		y0;

	x0 = world->canvas->win.w + 443;
	y0 = 140 + world->menu.scroll_objects.pos;
	if (x >= (x0) && x <= (x0 + 10) && y >= (y0) &&
			y <= (y0 + world->menu.scroll_objects.height))
	{
		world->menu.scroll_objects.active = 1;
		world->menu.scroll_objects.step = y - 5 - 135 -
			world->menu.scroll_objects.pos;
		return ;
	}
	if (x >= (x0) && x <= (x0 + 10) && y >= (140) &&
			y <= (140 + world->menu.scroll_objects.len - 10))
	{
		world->menu.scroll_objects.active = 1;
		world->menu.scroll_objects.step =
			world->menu.scroll_objects.height / 2;
		ft_mouse_motion(world, event);
		return ;
	}
	ft_mouse_button_objects_3(world, event, x, y);
}

void	ft_mouse_button_objects(t_world *world, SDL_Event event)
{
	int		x;
	int		y;

	x = event.button.x;
	y = event.button.y;
	if (x >= (world->canvas->win.w + 180) && x <= (world->canvas->win.w + 320)
			&& y >= 30 && y <= 70)
	{
		world->menu.type = MENU_LIGHTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (x >= (world->canvas->win.w + 330) && x <= (world->canvas->win.w +
				470) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OTHERS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else
		ft_mouse_button_objects_2(world, event, x, y);
}
