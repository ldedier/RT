/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_lights.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 01:17:35 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 02:52:21 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_lights_5(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		x1;
	int		y0;

	i = 0;
	while (i < world->menu.nb_lights_rb)
	{
		x0 = world->menu.lights_rb[i].pix.x + ((world->menu.lights_rb[i].min
					* 100) / world->menu.lights_rb[i].max);
		x1 = world->menu.lights_rb[i].pix.x + ((world->menu.lights_rb[i].max
					* 100) / world->menu.lights_rb[i].max);
		y0 = world->menu.lights_rb[i].pix.y;
		if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) &&
				y <= (y0 - 3 + 12))
		{
			world->menu.active_rb = i;
			ft_mouse_motion(world, event);
			return ;
		}
		i++;
	}
	ft_mouse_button_lights_6(world, event, x, y);
}

void	ft_mouse_button_lights_4(t_world *world, int i)
{
	world->menu.active_light = world->menu.lights[i];
	world->menu.lights_rb[0].value =
		&(world->lights[world->menu.active_light].angle);
	world->menu.lights_rb[1].value =
		&(world->lights[world->menu.active_light].intensity);
	world->menu.lights_rb[2].value =
		&(world->lights[world->menu.active_light].v.x);
	world->menu.lights_rb[3].value =
		&(world->lights[world->menu.active_light].v.y);
	world->menu.lights_rb[4].value =
		&(world->lights[world->menu.active_light].v.z);
	world->menu.lights_cp[0].color =
		&(world->lights[world->menu.active_light].c);
	world->menu.lights_cp[0].pos = ft_color_pos(world,
			world->lights[world->menu.active_light].c);
}

void	ft_mouse_button_lights_3(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		y0;
	int		y1;

	i = 0;
	x0 = world->canvas->win.w + 55;
	y0 = world->menu.first_light.y;
	while (i < world->menu.nb_lights)
	{
		y1 = y0 + i * (50 + 15);
		if (x >= (x0) && x <= (x0 + 360) && y >= (y1) && y <= (y1 + 50))
		{
			ft_mouse_button_lights_4(world, i);
			update_progress_bar(world);
			return ;
		}
		i++;
	}
	ft_mouse_button_lights_5(world, event, x, y);
}

void	ft_mouse_button_lights_2(t_world *world, SDL_Event event, int x, int y)
{
	int		x0;
	int		y0;

	x0 = world->canvas->win.w + 443;
	y0 = 140 + world->menu.scroll_lights.pos;
	if (x >= (x0) && x <= (x0 + 10) && y >= (y0) && y <= (y0 +
				world->menu.scroll_lights.height))
	{
		world->menu.scroll_lights.active = 1;
		world->menu.scroll_lights.step = y - 140 -
			world->menu.scroll_lights.pos;
		return ;
	}
	if (x >= (x0) && x <= (x0 + 10) && y >= (140) &&
			y <= (140 + world->menu.scroll_lights.len - 10))
	{
		world->menu.scroll_lights.active = 1;
		world->menu.scroll_lights.step = world->menu.scroll_lights.height /
			2;
		ft_mouse_motion(world, event);
		return ;
	}
	ft_mouse_button_lights_3(world, event, x, y);
}

void	ft_mouse_button_lights(t_world *world, SDL_Event event)
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
	else if (x >= (world->canvas->win.w + 330) && x <= (world->canvas->win.w +
				470) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OTHERS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else
		ft_mouse_button_lights_2(world, event, x, y);
}
