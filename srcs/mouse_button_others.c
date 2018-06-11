/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_others.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 01:19:23 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 02:34:35 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_others_5(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		x1;
	int		y0;

	i = 0;
	while (i < world->menu.nb_others_rb)
	{
		x0 = world->menu.others_rb[i].pix.x + ((world->menu.others_rb[i].min *
					100) / world->menu.others_rb[i].max);
		x1 = world->menu.others_rb[i].pix.x + ((world->menu.others_rb[i].max *
					100) / world->menu.others_rb[i].max);
		y0 = world->menu.others_rb[i].pix.y;
		if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) && y <= (y0 - 3 + 12))
		{
			world->menu.active_rb = i;
			ft_mouse_motion(world, event);
			return ;
		}
		i++;
	}
	ft_mouse_button_others_6(world, event, x, y);
}

int		ft_mouse_button_others_4(t_world *world, int i, int tmp)
{
	if (i == (e_nfilters + 1))
	{
		world->menu.filter_active = 0;
		update_progress_bar(world);
		return (1);
	}
	world->menu.filters_list[0] = world->menu.filters_list[i];
	world->menu.filters_list[i] = tmp;
	ft_sort_menu_filters(world);
	world->menu.filter_active = 0;
	world->filters[tmp] = 0;
	world->filters[world->menu.filters_list[0]] = 1;
	if (i > 0)
	{
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
	}
	update_progress_bar(world);
	return (0);
}

int		ft_mouse_button_others_3(t_world *world, int x, int y)
{
	int		i;
	int		x0;
	int		x1;
	int		y0;
	int		tmp;

	x0 = world->menu.filters.pos.x;
	x1 = world->menu.filters.pos.x + world->menu.filters.size.x;
	tmp = world->menu.filters_list[0];
	i = 0;
	while (i < (e_nfilters + 1))
	{
		y0 = world->menu.filters.pos.y + i * (world->menu.filters.size.y + 2);
		if (x >= x0 && x <= x1 && y >= y0 &&
				y <= (y0 + world->menu.filters.size.y))
			break ;
		i++;
	}
	return (ft_mouse_button_others_4(world, i, tmp));
}

void	ft_mouse_button_others_2(t_world *world, SDL_Event event, int x, int y)
{
	if (world->menu.filter_active == 0)
	{
		if (x >= (world->menu.filters.pos.x) && x <= (world->menu.filters.pos.x
			+ world->menu.filters.size.x) && y >= (world->menu.filters.pos.y) &&
			y <= (world->menu.filters.pos.y + world->menu.filters.size.y))
		{
			world->menu.filter_active = 1;
			update_progress_bar(world);
			return ;
		}
	}
	else if (world->menu.filter_active == 1)
	{
		if (ft_mouse_button_others_3(world, x, y) == 0)
			return ;
	}
	if (world->menu.filter_active == 1)
		world->menu.filter_active = 0;
	ft_mouse_button_others_5(world, event, x, y);
}

void	ft_mouse_button_others(t_world *world, SDL_Event event)
{
	int		x;
	int		y;

	x = event.button.x;
	y = event.button.y;
	if (x >= (world->canvas->win.w + 30) && x <= (world->canvas->win.w + 170) &&
			y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OBJECTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (x >= (world->canvas->win.w + 180) && x <= (world->canvas->win.w +
				320) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_LIGHTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else
		ft_mouse_button_others_2(world, event, x, y);
}
