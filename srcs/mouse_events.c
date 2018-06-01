/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:28:01 by aherriau          #+#    #+#             */
/*   Updated: 2018/05/31 23:00:49 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_motion(t_world *e, SDL_Event event)
{
	if (e->mouse_press == 1)
	{
		e->cam->rotation.x = e->cam->rotation.x -
			(event.motion.xrel) * M_PI / 1024.0;
		e->cam->rotation.y = ft_fclamp(-M_PI / 2,
				e->cam->rotation.y - (event.motion.yrel) * M_PI / 1024.0,
				M_PI / 2);
		apply_rotation(e->cam);
		e->keys[mouse_move] = 1;
	}
}

void	ft_mouse_button_menu(t_world *world, SDL_Event event)
{
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
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_LIGHTS && x >= (start + 30 + 150) &&
			x <= (start + 30 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_LIGHTS;
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_OTHERS && x >= (start + 30 + 150 + 150) &&
			x <= (start + 30 + 150 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OTHERS;
		update_progress_bar(world);
	}
}

void	ft_mouse_button(t_world *world, SDL_Event event)
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
		ft_mouse_button_menu(world, event);
}
