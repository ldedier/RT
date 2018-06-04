/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:28:01 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/04 08:39:57 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_motion(t_world *world, SDL_Event event)
{
	if (world->mouse_press == 1)
	{
		world->cam->rotation.x = world->cam->rotation.x -
			(event.motion.xrel) * M_PI / 1024.0;
		world->cam->rotation.y = ft_fclamp(-M_PI / 2,
				world->cam->rotation.y - (event.motion.yrel) * M_PI / 1024.0,
				M_PI / 2);
		apply_rotation(world->cam);
		world->keys[mouse_move] = 1;
	}
	if (world->menu.active_rb >= 0)
	{
		int i = world->menu.active_rb;
		float value = ((float)(event.motion.x - (world->menu.others_rb[i].pix.x + 4)) / 100) * world->menu.others_rb[i].max;
		if (value >= world->menu.others_rb[i].min && value <= world->menu.others_rb[i].max)
			*(world->menu.others_rb[i].value) = value;
		else
		{
			if (value < world->menu.others_rb[i].min)
				*(world->menu.others_rb[i].value) = world->menu.others_rb[i].min;
			if (value > world->menu.others_rb[i].max)
				*(world->menu.others_rb[i].value) = world->menu.others_rb[i].max;
		}
		paint_threaded_fast(world);;
	}
	if (world->menu.active_cp >= 0)
	{
		int i = world->menu.active_cp;
		int x = event.motion.x - world->menu.others_cp[i].pix.x;
		int y = event.motion.y - world->menu.others_cp[i].pix.y;
		if (x < 0)
			x = 0;
		else if (x > 100)
			x = 100;
		if (y < 0)
			y = 0;
		else if (y > 100)
			y = 100;
		*(world->menu.others_cp[i].color) = world->menu.color_map[y * 100 + x];
		world->menu.others_cp[i].pos.x = x;
		world->menu.others_cp[i].pos.y = y;
		paint_threaded_fast(world);;
	}
}

void	ft_sort_menu_filters(t_world *world)
{
	int		changed;
	int		i;
	int		tmp;

	changed = 1;
	while (changed == 1)
	{
		changed = 0;
		i = 1;
		while ((i + 1) < (e_nfilters + 1))
		{
			if (world->menu.filters_list[i] > world->menu.filters_list[i + 1])
			{
				tmp = world->menu.filters_list[i];
				world->menu.filters_list[i] = world->menu.filters_list[i + 1];
				world->menu.filters_list[i + 1] = tmp;
				changed = 1;
			}
			i++;
		}
	}	
}

void	ft_mouse_button_down_menu(t_world *world, SDL_Event event)
{
	int		i;
	int		x;
	int		y;
	int		start;

	x = event.button.x;
	y = event.button.y;
	start = world->canvas->win_size.x;
	if (world->menu.type != MENU_OBJECTS && x >= (start + 30) &&
			x <= (start + 30 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OBJECTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_LIGHTS && x >= (start + 30 + 150) &&
			x <= (start + 30 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_LIGHTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_OTHERS && x >= (start + 30 + 150 + 150) &&
			x <= (start + 30 + 150 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OTHERS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type == MENU_OTHERS)
	{
		if (world->menu.filter_active == 0)
		{
			if (x >= (world->menu.filters.pos.x) && x <= (world->menu.filters.pos.x + world->menu.filters.size.x) &&
					y >= (world->menu.filters.pos.y) && y <= (world->menu.filters.pos.y + world->menu.filters.size.y))
			{
				world->menu.filter_active = 1;
				update_progress_bar(world);
				return ;
			}
		}
		else if (world->menu.filter_active == 1)
		{
			int x0 = world->menu.filters.pos.x;
			int x1 = world->menu.filters.pos.x + world->menu.filters.size.x;
			int tmp = world->menu.filters_list[0];
			int i = 0;
			while (i < (e_nfilters + 1))
			{
				int y0 = world->menu.filters.pos.y + i * (world->menu.filters.size.y + 2);
				int y1 = y0 + world->menu.filters.size.y;
				if (x >= x0 && x <= x1 && y >= y0 && y <= y1)
					break ;
				i++;
			}
			if (i == (e_nfilters + 1))
			{
				i = 0;
				world->menu.filters_list[0] = world->menu.filters_list[i];
				world->menu.filters_list[i] = tmp;
				ft_sort_menu_filters(world);
				world->menu.filter_active = 0;
				if (i < (e_nfilters + 1))
				{
					world->filters[tmp] = 0;
					world->filters[world->menu.filters_list[0]] = 1;
				}
				update_progress_bar(world);
			}
			else
			{
				world->menu.filters_list[0] = world->menu.filters_list[i];
				world->menu.filters_list[i] = tmp;
				ft_sort_menu_filters(world);
				world->menu.filter_active = 0;
				if (i < (e_nfilters + 1))
				{
					world->filters[tmp] = 0;
					world->filters[world->menu.filters_list[0]] = 1;
				}
				update_progress_bar(world);
				return ;
			}
		}
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		i = 0;
		while (i < world->menu.nb_others_rb)
		{
			//int x0 = world->menu.others_rb[i].pix.x + ((*(world->menu.others_rb[i].value) * 100) / world->menu.others_rb[i].max);
			int x0 = world->menu.others_rb[i].pix.x + ((world->menu.others_rb[i].min * 100) / world->menu.others_rb[i].max);
			int x1 = world->menu.others_rb[i].pix.x + ((world->menu.others_rb[i].max * 100) / world->menu.others_rb[i].max);
			int y0 = world->menu.others_rb[i].pix.y;
			if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) && y <= (y0 - 3 + 12))
			{
				world->menu.active_rb = i;
				ft_mouse_motion(world, event);
				return ;
			}
			i++;
		}
		i = 0;
		while (i < world->menu.nb_others_cp)
		{
			int x0 = world->menu.others_cp[i].pix.x;
			int y0 = world->menu.others_cp[i].pix.y;
			if (x >= (x0) && x <= (x0 + 100) && y >= (y0) && y <= (y0 + 100))
			{
				world->menu.active_cp = i;
				ft_mouse_motion(world, event);
				return ;
			}
			i++;
		}
	}
}

void	ft_mouse_button_down(t_world *world, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		if (world->mouse_press == 1)
		{
			world->mouse_press = 0;
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_WarpMouseInWindow(world->canvas->window,
					(HRES + MENU_WIDTH) / 2, (VRES + PROGRESS_BAR_HEIGHT) / 2);
		}
		else if (world->mouse_press == 0)
		{
			if (event.button.x <= HRES)
			{
				SDL_SetRelativeMouseMode(SDL_TRUE);
				world->mouse_press = 1;
			}
		}
	}
	else if (event.button.button == SDL_BUTTON_LEFT && event.button.x > HRES)
		ft_mouse_button_down_menu(world, event);
}

void	ft_mouse_button_up_menu(t_world *world, SDL_Event event)
{
	(void)event;
	if (world->menu.active_rb >= 0)
		world->menu.active_rb = -1;
	if (world->menu.active_cp >= 0)
		world->menu.active_cp = -1;
}

void	ft_mouse_button_up(t_world *world, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT && event.button.x > HRES)
		ft_mouse_button_up_menu(world, event);
}
