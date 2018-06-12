/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:28:01 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 02:26:37 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//Bons Noms pour Cobj / Obj (a mettre au parsing)
//Ne pas afficher les objects des Cobj OBJ (42/teapot)

//Reprendre l'exporter de scene
//	- on peut avoir plusieurs filtres
//	- ...

void	ft_mouse_motion(t_world *world, SDL_Event event)
{
	if (world->focus == 1)
	{
		world->cam->rotation.x = world->cam->rotation.x -
			(event.motion.xrel) * M_PI / 1024.0;
		world->cam->rotation.y = ft_fclamp(-M_PI / 2,
				world->cam->rotation.y - (event.motion.yrel) * M_PI / 1024.0,
				M_PI / 2);
		apply_rotation(world->cam);
		world->keys[mouse_move] = 1;
	}
	else if (world->menu.type == MENU_OBJECTS)
		ft_mouse_motion_objects(world, event);
	else if (world->menu.type == MENU_LIGHTS)
		ft_mouse_motion_lights(world, event);
	else if (world->menu.type == MENU_OTHERS)
		ft_mouse_motion_others(world, event);
}

void	ft_mouse_button_down_2(t_world *world, SDL_Event event)
{
	if (event.button.x > world->canvas->win_size.x)
	{
		if (world->menu.type == MENU_OBJECTS)
			ft_mouse_button_objects(world, event);
		else if (world->menu.type == MENU_LIGHTS)
			ft_mouse_button_lights(world, event);
		else if (world->menu.type == MENU_OTHERS)
			ft_mouse_button_others(world, event);
	}
	else if (world->focus == 0)
		ft_left_click_event(world, event);
}

void	ft_mouse_button_down(t_world *world, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		if (world->focus == 1)
		{
			world->focus = 0;
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_WarpMouseInWindow(world->canvas->window,
					(world->canvas->win_size.x + MENU_WIDTH) / 2,
					world->canvas->win.h / 2);
		}
		else if (world->focus == 0)
		{
			if (event.button.x <= world->canvas->win_size.x)
			{
				SDL_SetRelativeMouseMode(SDL_TRUE);
				world->focus = 1;
			}
		}
	}
	else if (event.button.button == SDL_BUTTON_LEFT)
		ft_mouse_button_down_2(world, event);
}

void	ft_mouse_button_up(t_world *world, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT &&
			event.button.x > world->canvas->win_size.x)
	{
		if (world->menu.active_rb >= 0)
			world->menu.active_rb = -1;
		else if (world->menu.active_grb >= 0)
			world->menu.active_grb = -1;
		else if (world->menu.active_cp >= 0)
			world->menu.active_cp = -1;
		else if (world->menu.scroll_objects.active == 1)
			world->menu.scroll_objects.active = 0;
		else if (world->menu.scroll_lights.active == 1)
			world->menu.scroll_lights.active = 0;
	}
}
