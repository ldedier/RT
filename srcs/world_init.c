/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:37:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/02 06:44:16 by aherriau         ###   ########.fr       */
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

static void		set_defaults_2(t_world *world)
{
	int	i;

	i = -1;
	while (++i < NTHREADS)
		world->thr_state[i] = 0;
	i = -1;
	while (++i < e_nfilters)
		world->filters[i] = 0;
}

TTF_Font		*ft_load_font(char *str, int quality)
{
	TTF_Font	*font;

	font = TTF_OpenFont(str, quality);
	if (font == NULL)
		exit (1);
	return (font);
}

t_pixel			ft_new_pixel(int x, int y)
{
	t_pixel		pix;

	pix.x = x;
	pix.y = y;
	return (pix);
}

t_rangebar		ft_new_rangebar(double min, double max, t_pixel pix, double *value)
{
	t_rangebar	rb;

	rb.min = min;
	rb.max = max;
	rb.pix = pix;
	rb.value = value;
	return(rb);
}

t_colorpicker	ft_new_colorpicker(t_pixel pix, t_pixel pos, t_color *color)
{
	t_colorpicker	cp;

	cp.pix = pix;
	cp.pos = pos;
	cp.color = color;
	return(cp);
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
	world->shader = 1;
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
	world->can_export = 1;
	world->nb_export = 0;
	set_defaults_2(world);
	ft_init_keys(world);

	world->mouse_press = 0;
	world->menu.type = 3;
	world->menu.fonts[0] = ft_load_font("Raleway.ttf", 200);
	world->menu.fonts[1] = ft_load_font("Raleway-Bold.ttf", 200);

	world->menu.active_rb = -1;
	world->menu.nb_others_rb = 2;
	world->menu.others_rb[0] = ft_new_rangebar(0, 1, ft_new_pixel(world->canvas->win_size.x + 20 + 10 + 80, 200), &(world->ambient.in));
	world->menu.others_rb[1] = ft_new_rangebar(0, 0.7, ft_new_pixel(world->canvas->win_size.x + 20 + 10 + 50, 310), &(world->fog.in));
	
	world->menu.active_cp = -1;
	world->menu.nb_others_cp = 2;
	world->menu.others_cp[0] = ft_new_colorpicker(ft_new_pixel(world->canvas->win_size.x + 20 + 10 + 30 + 210, 120), ft_new_pixel(0, 0), &(world->ambient.color));
	world->menu.others_cp[1] = ft_new_colorpicker(ft_new_pixel(world->canvas->win_size.x + 20 + 10 + 30 + 210, 270), ft_new_pixel(0, 0), &(world->fog.color));

	world->bmp_parser = ft_parse_bmp("kirby.bmp");
}

t_canvas		*new_canvas(void)
{
	t_canvas	*canvas;

	if ((canvas = malloc(sizeof(t_canvas))) == NULL)
		return (NULL);
	canvas->win_size.x = HRES;
	canvas->win_size.y = VRES;
	canvas->fast_win_size.x = FAST_HRES;
	canvas->fast_win_size.x = FAST_VRES;
	canvas->halved_win_size.x = HRES / 2;
	canvas->halved_win_size.y = VRES / 2;
	canvas->ratio = HRES / VRES;
	canvas->pb_rect.x = 0;
	canvas->pb_rect.y = canvas->win_size.y;
	canvas->pb_rect.w = 0;
	canvas->pb_rect.h = PROGRESS_BAR_HEIGHT;
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
	if (TTF_Init() < 0)
		return (0);
	canvas->screen.w = canvas->win_size.x;
	canvas->screen.h = canvas->win_size.y + PROGRESS_BAR_HEIGHT;
	if (!(canvas->window = SDL_CreateWindow("rt",
		canvas->screen.x, canvas->screen.y,
		canvas->screen.w + MENU_WIDTH, canvas->screen.h, 0)))
			return (0);
	if(!(canvas->renderer = SDL_CreateRenderer(canvas->window, -1, 0)))
		return (0);
	if (SDL_RenderSetLogicalSize(canvas->renderer,
				canvas->screen.w + MENU_WIDTH, canvas->screen.h) < 0)
		return (0);
	if (SDL_SetRenderDrawColor(canvas->renderer, 0, 0, 0, 255) < 0)
		return (0);
	if (!(canvas->surface = SDL_CreateRGBSurface(0,
			canvas->screen.w, canvas->screen.h, 32, 0, 0, 0, 0)))
		return (0);
	return (1);
}
