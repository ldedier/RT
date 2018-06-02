/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:28:01 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/02 07:14:23 by aherriau         ###   ########.fr       */
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
		int x = event.motion.x - (world->menu.others_cp[i].pix.x + world->menu.others_cp[i].pos.x);
		int y = event.motion.y - (world->menu.others_cp[i].pix.y + world->menu.others_cp[i].pos.y);
		
		//regarder si x, y dans l'intervalle [0, 100]
		//si oui, diviser x et y par 100
		//trouver le r,g.b et donc la couleur correspondante
		//pour cela faire la double boucle et s'arreter quand trouver
		//soit exactement, soit tres proche si 1er donne pas de solution
		
		//world->menu.others_cp[i].color->col = value;
		printf("%d %d\n", x, y);
		paint_threaded_fast(world);;
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
	else if (world->menu.type == MENU_OTHERS)
	{
		i = 0;
		while (i < world->menu.nb_others_rb)
		{
			int x0 = world->menu.others_rb[i].pix.x + ((*(world->menu.others_rb[i].value) * 100) / world->menu.others_rb[i].max);
			int y0 = world->menu.others_rb[i].pix.y;
			if (x >= (x0) && x <= (x0 + 8) && y >= (y0 - 3) && y <= (y0 - 3 + 12))
			{
				world->menu.active_rb = i;
				break;
			}
			i++;
		}
		i = 0;
		while (i < world->menu.nb_others_cp)
		{
			int x0 = world->menu.others_cp[i].pix.x + world->menu.others_cp[i].pos.x;
			int y0 = world->menu.others_cp[i].pix.y + world->menu.others_cp[i].pos.x;
			if (x >= (x0) && x <= (x0 + 7) && y >= (y0) && y <= (y0 + 7))
			{
				world->menu.active_cp = i;
				break;
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
	int		x;
	int		y;
	int		start;

	x = event.button.x;
	y = event.button.y;
	start = world->canvas->win_size.x;
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
