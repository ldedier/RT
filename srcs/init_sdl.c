/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 04:36:22 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 23:23:13 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_canvas	*new_canvas(void)
{
	t_canvas		*canvas;

	if ((canvas = malloc(sizeof(t_canvas))) == NULL)
		return (NULL);
	canvas->win_size.x = -1;
	canvas->win_size.y = -1;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (NULL);
	if (TTF_Init() != 0)
		return (NULL);
	return (canvas);
}

int			ft_init_sdl_3(t_world *world)
{
	if (!(world->canvas->window = SDL_CreateWindow("rt",
			world->canvas->win.x, world->canvas->win.y,
			world->canvas->win.w + MENU_WIDTH, world->canvas->win.h, 0)))
		return (0);
	if (!(world->canvas->renderer = SDL_CreateRenderer(world->canvas->window,
			-1, 0)))
		return (0);
	if (SDL_RenderSetLogicalSize(world->canvas->renderer,
			world->canvas->win.w + MENU_WIDTH, world->canvas->win.h) < 0)
		return (0);
	if (SDL_SetRenderDrawColor(world->canvas->renderer, 0, 0, 0, 255) < 0)
		return (0);
	if (!(world->canvas->win_surface = SDL_CreateRGBSurface(0,
			world->canvas->win.w, world->canvas->win.h, 32, 0, 0, 0, 0)))
		return (0);
	if (!(world->canvas->surface = SDL_CreateRGBSurface(0,
			world->canvas->screen.w, world->canvas->screen.h, 32, 0, 0, 0, 0)))
		return (0);
	if (!(world->canvas->red_pixels = (int *)malloc(sizeof(int)
					* world->canvas->win_size.x * world->canvas->win_size.y)))
		return (0);
	return (1);
}

void		ft_init_sdl_2(t_world *world)
{
	t_pixel			div;

	div = fast_div(world->canvas);
	world->canvas->fast_win_size.x = world->canvas->win_size.x / div.x
		/ FAST_RATIO;
	world->canvas->fast_win_size.y = world->canvas->win_size.y / div.y
		/ FAST_RATIO;
	world->canvas->halved_win_size.x = world->canvas->win_size.x / 2;
	world->canvas->halved_win_size.y = world->canvas->win_size.y / 2;
	world->canvas->ratio = (double)(world->canvas->win_size.x)
		/ (double)(world->canvas->win_size.y);
	world->canvas->pb_rect.x = 0;
	world->canvas->pb_rect.w = 0;
	world->canvas->pb_rect.h = PROGRESS_BAR_HEIGHT;
	world->canvas->npixels = world->canvas->win_size.x
		* world->canvas->win_size.y;
	world->cam->pd = ZOOM / world->canvas->win_size.x;
	world->canvas->win.x = 0;
	world->canvas->win.y = 0;
	world->canvas->win.w = world->canvas->win_size.x;
	if (world->canvas->win_size.y < MENU_HEIGHT)
		world->canvas->win.h = MENU_HEIGHT + PROGRESS_BAR_HEIGHT;
	else
		world->canvas->win.h = world->canvas->win_size.y + PROGRESS_BAR_HEIGHT;
}

int			ft_init_sdl(t_world *world)
{
	SDL_DisplayMode	dm;

	if (world->canvas->win_size.x == -1 && world->canvas->win_size.y == -1)
	{
		SDL_GetCurrentDisplayMode(0, &dm);
		if (dm.w >= 2560 && dm.h >= 1440)
		{
			world->canvas->win_size.x = 1600 - MENU_WIDTH;
			world->canvas->win_size.y = 1200 - PROGRESS_BAR_HEIGHT;
		}
		else
		{
			world->canvas->win_size.x = 1200 - MENU_WIDTH;
			world->canvas->win_size.y = 600 - PROGRESS_BAR_HEIGHT - 44;
		}
	}
	ft_init_sdl_2(world);
	world->canvas->pb_rect.y = world->canvas->win.h - PROGRESS_BAR_HEIGHT;
	world->canvas->screen.w = world->canvas->win_size.x;
	world->canvas->screen.h = world->canvas->win_size.y;
	world->canvas->screen.x = 0;
	world->canvas->screen.y = ((world->canvas->win.h - PROGRESS_BAR_HEIGHT) / 2)
		- (world->canvas->screen.h / 2);
	return (ft_init_sdl_3(world));
}
