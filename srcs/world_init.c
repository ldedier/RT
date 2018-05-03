/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:37:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/03 15:40:35 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_keys(t_world *e)
{
	int i;

	i = -1;
	while (++i < nkeys)
		e->keys[i] = 0;
}

void			set_defaults(t_world *world)
{
	world->cam->o = CAMERA_POS;
	world->cam->look = normalize(CAMERA_LOOK);
	world->cam->up = normalize(CAMERA_UP);
	world->cam->right = normalize(crossprod(world->cam->look, world->cam->up));
	world->cam->fd = CAMERA_FD;
	world->cam->pd = ZOOM / HRES;
	world->cam->rotation = POINT_ZERO;
	world->nlights = 0;
	world->objlist = NULL;
	world->ambient.in = AMBIENT_LIGHT;
	world->ambient.color = AMBIENT_LIGHT_COL;
	world->fog.in = 0.0;
	world->fog.color = BACKGROUND_COLOR;
	world->cam->speed = SPEED;
	ft_init_keys(world);
}

t_canvas		*new_canvas(void)
{
	t_canvas	*canvas;

	if ((canvas = malloc(sizeof(t_canvas))) == NULL)
		return (NULL);
	canvas->win_size.x = HRES;
	canvas->win_size.y = VRES;
	canvas->halved_win_size.x = HRES / 2;
	canvas->halved_win_size.y = VRES / 2;
	canvas->ratio = HRES / VRES;
	if (!(ft_init_all(canvas)))
		return (NULL);
	return (canvas);
}

int			ft_init_all(t_canvas *canvas)
{
	canvas->screen.x = 0;
	canvas->screen.y = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	canvas->screen.w = canvas->win_size.x;
	canvas->screen.h = canvas->win_size.y;
	if (!(canvas->window = SDL_CreateWindow("rt",
		canvas->screen.x, canvas->screen.y, canvas->screen.w, canvas->screen.h, 0)))
			return (0);
	if(!(canvas->renderer = SDL_CreateRenderer(canvas->window, -1, 0)))
		return (0);
	if (!(canvas->surface = SDL_CreateRGBSurface(0, canvas->screen.w, canvas->screen.h, 32, 0, 0, 0, 0)))
		return (0);
	if (SDL_RenderSetLogicalSize(canvas->renderer,
				canvas->screen.w, canvas->screen.h) < 0)
		return (0);
	if (SDL_SetRenderDrawColor(canvas->renderer, 0, 0, 0, 255) < 0)
		return (0);
	if (!(canvas->surface = SDL_CreateRGBSurface(0,
			canvas->screen.w, canvas->screen.h, 32, 0, 0, 0, 0)))
		return (0);
	return (1);
}
