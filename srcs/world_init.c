/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:37:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/05 06:43:49 by aherriau         ###   ########.fr       */
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

t_dropdown	ft_new_dropdown(t_pixel pos, t_pixel size, int levels)
{
	t_dropdown	dd;

	dd.pos = pos;
	dd.size = size;
	dd.levels = levels;
	return(dd);
}

float	ft_hue_to_rgb(float v1, float v2, float vH)
{
	if (vH < 0)
		vH += 1.f;
	if (vH > 1)
		vH -= 1.f;
	if (6.f * vH < 1)
		return (v1 + (v2 - v1) * 6.f * vH);
	if (2.f * vH < 1)
		return (v2);
	if (3.f * vH < 2)
		return (v1 + (v2 - v1) * (0.666666f - vH) * 6.f);
	return (v1);
}

void	ft_color_pix(float x0, float y0, t_color *color)
{
	float	h;
	float	s;
	float	l;
	float	var_1;
	float	var_2;

	h = x0;
	s = 1.0f - y0;
	l = 1.0f - y0;
	if (s == 0)
	{
		color->r = ft_clamp(0, l * 255, 255);
		color->g = ft_clamp(0, l * 255, 255);
		color->b = ft_clamp(0, l * 255, 255);
	}
	else
	{
		var_1 = 0;
		var_2 = 0;
		if (l < 0.5f)
			var_2 = l * (1.0f + s);
		else
			var_2 = (l + s) - (s * l);
		var_1 = 2.0f * l - var_2;
		color->r = ft_clamp(0, ft_hue_to_rgb(var_1, var_2, h + 0.333333f) * 255, 255);
		color->g = ft_clamp(0, ft_hue_to_rgb(var_1, var_2, h) * 255, 255);
		color->b = ft_clamp(0, ft_hue_to_rgb(var_1, var_2, h - 0.333333f) * 255, 255);
	}
	color->col = (color->r << 16) | (color->g << 8) | color->b;
}

void	ft_color_map(t_world *world)
{
	int		x;
	float	x0;
	int		y;
	float	y0;
	t_color	color;

	y = 0;
	y0 = 0;
	while (y < 100)
	{
		y0 = (float)y / 100;
		x = 0;
		while (x < 100)
		{
			x0 = (float)x / 100;
			ft_color_pix(x0, y0, &color);
			world->menu.color_map[y * 100 + x] = color;
			x++;
		}
		y++;
	}
}

t_pixel	ft_color_pos(t_world *world, t_color color)
{
	int		x;
	int		y;
	t_pixel	pix;

	pix.x = 0;
	pix.y = 0;
	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			if (world->menu.color_map[y * 100 + x].col == color.col)
			{
				pix.x = x;
				pix.y = y;
				return (pix);
			}
			x++;
		}
		y++;
	}
	y = 0;
	float dist = 100;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			int r = world->menu.color_map[y * 100 + x].r;
            int g = world->menu.color_map[y * 100 + x].g;
            int b = world->menu.color_map[y * 100 + x].b;
            float tmp = sqrt((r - color.r) * (r - color.r) + (g - color.g) * (g - color.g) + (b - color.b) * (b - color.b));
			if (tmp < dist)
			{
				dist = tmp;
				printf("AAAAAAAA\n");
				pix.x = x;
				pix.y = y;
			}
			x++;
		}
		y++;
	}
	return (pix);
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
	world->defcobjlist = NULL;
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
	world->animate = 0;
	world->focus = 0;
	world->exporting_video = 0;
	init_video(&(world->video));
	world->ticks = SDL_GetTicks();
	world->aa_sq_size = AA_SQ_SIZE;
	world->nb_export = 0;
	set_defaults_2(world);
	ft_init_keys(world);
	world->max_bounce = 1;

	world->menu.type = 3;
	world->menu.fonts[0] = ft_load_font(PATH"/resources/fonts/Raleway.ttf", 200);
	world->menu.fonts[1] = ft_load_font(PATH"/resources/fonts/Raleway-Bold.ttf", 200);

	world->menu.active_rb = -1;
	world->menu.nb_others_rb = 3;
	world->menu.others_rb[0] = ft_new_rangebar(0, 1, ft_new_pixel(world->canvas->win_size.x + 20 + 45 + 30, 220), &(world->ambient.in));
	world->menu.others_rb[1] = ft_new_rangebar(0, 0.7, ft_new_pixel(world->canvas->win_size.x + 20 + 45 + 30 + 200, 220), &(world->fog.in));
	world->menu.others_rb[2] = ft_new_rangebar(0, 50, ft_new_pixel(world->canvas->win_size.x + 20 + 45 + 174 + 45, 402 + 80 + 15), &(world->max_bounce));

	ft_color_map(world);

	world->menu.active_cp = -1;
	world->menu.nb_others_cp = 2;
	world->menu.others_cp[0] = ft_new_colorpicker(ft_new_pixel(world->canvas->win_size.x + 20 + 45 + 34, 250), ft_color_pos(world, world->ambient.color), &(world->ambient.color));
	world->menu.others_cp[1] = ft_new_colorpicker(ft_new_pixel(world->canvas->win_size.x + 20 + 45 + 34 + 200, 250), ft_color_pos(world, world->fog.color), &(world->fog.color));


	world->menu.filter_active = 0;
	if (world->filters[0] == 1)
		world->menu.filters_list[0] = 0;
	else if (world->filters[1] == 1)
		world->menu.filters_list[0] = 1;
	else if (world->filters[2] == 1)
		world->menu.filters_list[0] = 2;
	else if (world->filters[3] == 1)
		world->menu.filters_list[0] = 3;
	else if (world->filters[4] == 1)
		world->menu.filters_list[0] = 4;
	else
		world->menu.filters_list[0] = 5;
	int i = 0;
	int j = 1;
	while (j < (e_nfilters + 1))
	{
		if (world->menu.filters_list[0] != i)
			world->menu.filters_list[j++] = i;
		i++;
	}
	world->menu.filters = ft_new_dropdown(ft_new_pixel(world->canvas->win_size.x + 20 + 45 + 174, 402), ft_new_pixel(195, 36), e_nfilters);

	world->menu.cartoon = ft_parse_bmp(PATH"/resources/textures/cartoon.bmp");
	world->menu.cartoon2 = ft_parse_bmp(PATH"/resources/textures/cartoon2.bmp");

	world->menu.photo = ft_parse_bmp(PATH"/resources/textures/photo.bmp");
	world->menu.video = ft_parse_bmp(PATH"/resources/textures/video.bmp");
	world->menu.stop = ft_parse_bmp(PATH"/resources/textures/stop.bmp");
	world->menu.save = ft_parse_bmp(PATH"/resources/textures/save.bmp");

	world->bmp_parser = ft_parse_bmp(PATH"/resources/textures/kirby.bmp");
}

t_canvas		*new_canvas(void)
{
	t_canvas	*canvas;
	t_pixel		div;

	if ((canvas = malloc(sizeof(t_canvas))) == NULL)
		return (NULL);
	canvas->win_size.x = HRES;
	canvas->win_size.y = VRES;
	div = fast_div(canvas);
	canvas->fast_win_size.x = canvas->win_size.x / div.x / FAST_RATIO;
	canvas->fast_win_size.y = canvas->win_size.y / div.y / FAST_RATIO;
	canvas->halved_win_size.x = HRES / 2;
	canvas->halved_win_size.y = VRES / 2;
	canvas->ratio = (double)HRES / (double)VRES;
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
