/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:37:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/25 18:20:05 by aherriau         ###   ########.fr       */
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
	int	i;

	world->cam->o = CAMERA_POS;
	world->cam->look = normalize(CAMERA_LOOK);
	world->cam->up = normalize(CAMERA_UP);
	world->cam->right = normalize(crossprod(world->cam->look, world->cam->up));
	world->cam->fd = CAMERA_FD;
	world->cam->pd = ZOOM / HRES;
	world->cam->rotation = POINT_ZERO;
	world->nlights = 0;
	world->cobjlist = NULL;
	world->ambient.in = AMBIENT_LIGHT;
	world->ambient.color = AMBIENT_LIGHT_COL;
	world->fog.in = 0.0;
	world->fog.color = BACKGROUND_COLOR;
	world->cam->speed = SPEED;
	world->progress = 0;
	world->cancel_render = 0;
	world->canvas->npixels = world->canvas->win_size.x *
		world->canvas->win_size.y;
	i = -1;
	while (++i < NTHREADS)
		world->thr_state[i] = 0;
	world->can_export = 1;
	ft_init_keys(world);
	world->bmp_parser = ft_parse_bmp("earth2.bmp");
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

static void	set_pb_rect(t_canvas *canvas)
{
	canvas->pb_rect.x = 0;
	canvas->pb_rect.y = canvas->win_size.y;
	canvas->pb_rect.w = 0;
	canvas->pb_rect.h = PROGRESS_BAR_HEIGHT;
}

int			ft_init_all(t_canvas *canvas)
{
	canvas->screen.x = 0;
	canvas->screen.y = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	canvas->screen.w = canvas->win_size.x;
	canvas->screen.h = canvas->win_size.y + PROGRESS_BAR_HEIGHT;
	if (!(canvas->window = SDL_CreateWindow("rt",
		canvas->screen.x, canvas->screen.y,
		canvas->screen.w, canvas->screen.h, 0)))
			return (0);
	if(!(canvas->renderer = SDL_CreateRenderer(canvas->window, -1, 0)))
		return (0);
	if (SDL_RenderSetLogicalSize(canvas->renderer,
				canvas->screen.w, canvas->screen.h) < 0)
		return (0);
	if (SDL_SetRenderDrawColor(canvas->renderer, 0, 0, 0, 255) < 0)
		return (0);
	if (!(canvas->surface = SDL_CreateRGBSurface(0,
			canvas->screen.w, canvas->screen.h, 32, 0, 0, 0, 0)))
		return (0);
	set_pb_rect(canvas);
	return (1);
}
