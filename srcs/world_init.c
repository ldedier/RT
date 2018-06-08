/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:37:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/08 08:16:41 by aherriau         ###   ########.fr       */
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

t_grangebar		ft_new_grangebar(double min, double max, t_pixel pix, int *value)
{
	t_grangebar	grb;

	grb.min = min;
	grb.max = max;
	grb.pix = pix;
	grb.value = value;
	return(grb);
}

t_colorpicker	ft_new_colorpicker(t_pixel pix, t_pixel pos, t_color *color)
{
	t_colorpicker	cp;

	cp.pix = pix;
	cp.pos = pos;
	cp.color = color;
	return(cp);
}

t_dropdown	ft_new_dropdown(t_pixel pos, t_pixel size)
{
	t_dropdown	dd;

	dd.pos = pos;
	dd.size = size;
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
				pix.x = x;
				pix.y = y;
			}
			x++;
		}
		y++;
	}
	return (pix);
}

int     		ft_objects_scrollbar_size(t_world *world, int len)
{
	int     	h;
	float   	size;
	t_cobjlist  *lst;
	t_objlist   *lst2;

	world->menu.nobjects = 0;
	lst = world->cobjlist;
	while (lst != NULL)
	{
		(world->menu.nobjects)++;
		lst2 = lst->cobject->objlist;
		while(lst2 != NULL)
		{
			(world->menu.nobjects)++;
			lst2 = lst2->next;
		}
		lst = lst->next;
	}
	h = (world->menu.nobjects) * (50 + 15);
	if (h <= len)
		size = 1;
	else
		size = len / (float)h;
	return ((len - 10) * size);
}

int     		ft_lights_scrollbar_size(t_world *world, int len)
{
	int     h;
	float   size;

	h = world->nlights * (50 + 15);
	if (h <= len)
		size = 1;
	else
		size = len / (float)h;
	return ((len - 10) * size);
}

t_scrollbar		ft_new_scrollbar(t_world *world, int len, int type)
{
	t_scrollbar	sb;

	sb.active = 0;
	sb.len = len;
	if (type == 0)
		sb.height = ft_lights_scrollbar_size(world, len);
	else
		sb.height = ft_objects_scrollbar_size(world, len);
	sb.pos = 0;
	sb.step = 0;
	return (sb);
}

void			ft_cobjlist_reverse(t_cobjlist **alst)
{
	t_cobjlist	*new;
	t_cobjlist	*next;
	t_cobjlist	*current;

	new = 0;
	current = *alst;
	while (current != NULL)
	{
		next = current->next;
		current->next = new;
		new = current;
		current = next;
	}
	*alst = new;
}

void			ft_objlist_reverse(t_objlist **alst)
{
	t_objlist	*new;
	t_objlist	*next;
	t_objlist	*current;

	new = 0;
	current = *alst;
	while (current != NULL)
	{
		next = current->next;
		current->next = new;
		new = current;
		current = next;
	}
	*alst = new;
}

void			set_positions(t_world *world)
{
	ft_cobjlist_reverse(&(world->cobjlist));
	t_cobjlist *lst = world->cobjlist;
	while (lst != NULL)
	{
		ft_objlist_reverse(&(lst->cobject->objlist));
		lst = lst->next;
	}
	init_video(world, &(world->video));
	world->menu.others_rb[0] = ft_new_rangebar(0, 1, ft_new_pixel(world->canvas->win.w + 20 + 45 + 30, 220), &(world->ambient.in));
	world->menu.others_rb[1] = ft_new_rangebar(0, 0.7, ft_new_pixel(world->canvas->win.w + 20 + 45 + 30 + 200, 220), &(world->fog.in));
	world->menu.others_grb[0] = ft_new_grangebar(0, 10, ft_new_pixel(world->canvas->win.w + 20 + 45 + 32, 505), &(world->max_bounce));
	world->menu.others_grb[1] = ft_new_grangebar(1, 4, ft_new_pixel(world->canvas->win.w + 20 + 45 + 32 + 200, 505), &(world->aa_sq_size));
	world->menu.filters = ft_new_dropdown(ft_new_pixel(world->canvas->win.w + 20 + 45 + 174, 383), ft_new_pixel(195, 34));
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
	else if (world->filters[5] == 1)
		world->menu.filters_list[0] = 5;
	else
		world->menu.filters_list[0] = 6;
	int i = 0;
	int j = 1;
	while (j < (e_nfilters + 1))
	{
		if (world->menu.filters_list[0] != i)
			world->menu.filters_list[j++] = i;
		i++;
	}

	world->menu.scroll_lights = ft_new_scrollbar(world, 265, 0);
	ft_color_map(world);
	world->menu.nb_others_cp = 2;
	world->menu.others_cp[0] = ft_new_colorpicker(ft_new_pixel(world->canvas->win.w + 20 + 45 + 34, 250), ft_color_pos(world, world->ambient.color), &(world->ambient.color));
	world->menu.others_cp[1] = ft_new_colorpicker(ft_new_pixel(world->canvas->win.w + 20 + 45 + 34 + 200, 250), ft_color_pos(world, world->fog.color), &(world->fog.color));
	if (world->nlights > 0)
	{
		world->menu.active_light = 0;
		world->menu.first_light.x = 0;
		world->menu.first_light.y = 145;
		world->menu.nb_lights_rb = 5;

		world->menu.lights_rb[0] = ft_new_rangebar(0, 2 * M_PI, ft_new_pixel(world->canvas->win.w + 40 + 25 + 145, 518), &(world->lights[world->menu.active_light].angle));
		world->menu.lights_rb[1] = ft_new_rangebar(0, 1, ft_new_pixel(world->canvas->win.w + 40 + 25 + 42, 580), &(world->lights[world->menu.active_light].intensity));
		world->lights[world->menu.active_light].v = normalize(world->lights[world->menu.active_light].v);
		world->menu.lights_rb[2] = ft_new_rangebar(0, 2, ft_new_pixel(world->canvas->win.w + 40 + 25 + 222, 630), &(world->lights[world->menu.active_light].v.x));
		world->menu.lights_rb[3] = ft_new_rangebar(0, 2, ft_new_pixel(world->canvas->win.w + 40 + 25 + 222, 665), &(world->lights[world->menu.active_light].v.y));
		world->menu.lights_rb[4] = ft_new_rangebar(0, 2, ft_new_pixel(world->canvas->win.w + 40 + 25 + 222, 700), &(world->lights[world->menu.active_light].v.z));
		world->menu.nb_lights_cp = 1;
		world->menu.lights_cp[0] = ft_new_colorpicker(ft_new_pixel(world->canvas->win.w + 65 + 46, 615), ft_color_pos(world,
					world->lights[world->menu.active_light].c), &(world->lights[world->menu.active_light].c));
	}
	else
	{
		world->menu.active_light = -1;
		world->menu.first_light.x = -1;
		world->menu.first_light.y = -1;
		world->menu.nb_lights_rb = 0;
		world->menu.nb_lights_cp = 0;
	}
	if (world->nlights <= 4)
		world->menu.nb_lights = world->nlights;
	else
		world->menu.nb_lights = 4;
	i = 0;
	while (i < 5)
		world->menu.lights[i++] = -1;

	int n = world->nlights;
	float k;
	if (n == 5)
		k = 2;
	else if (n <= 10)
		k = 1;
	else
		k = ((float)n / 10) - 1;
	float size = world->menu.scroll_lights.len / (float)(n * (50 + 15) + k * (50 + 15));
	world->menu.fact_lights = 1 / size;

	world->menu.scroll_objects = ft_new_scrollbar(world, 265, 1);
	if (world->menu.nobjects <= 4)
		world->menu.nb_objects = world->menu.nobjects;
	else
		world->menu.nb_objects = 4;
	n = world->menu.nobjects;
	if (n == 5)
		k = 2;
	else if (n <= 10)
		k = 1;
	else
		k = ((float)n / 10) - 1;
	size = world->menu.scroll_objects.len / (float)(n * (50 + 15) + k * (50 + 15));
	world->menu.fact_objects = 1 / size;
}

void			set_defaults(t_world *world)
{
	world->cam->o = CAMERA_POS;
	world->cam->look = normalize(CAMERA_LOOK);
	world->cam->up = normalize(CAMERA_UP);
	world->cam->right = normalize(crossprod(world->cam->look, world->cam->up));
	world->cam->fd = CAMERA_FD;
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
	world->can_export = 1;
	world->animate = 0;
	world->focus = 0;
	world->exporting_video = 0;
	world->ticks = SDL_GetTicks();
	world->aa_sq_size = AA_SQ_SIZE;
	world->nb_export = 0;
	set_defaults_2(world);
	ft_init_keys(world);
	world->max_bounce = 4;
	world->menu.type = MENU_OBJECTS;
	world->menu.fonts[0] = ft_load_font(PATH"/resources/fonts/Raleway.ttf", 200);
	world->menu.fonts[1] = ft_load_font(PATH"/resources/fonts/Raleway-Bold.ttf", 200);
	world->menu.active_rb = -1;
	world->menu.active_grb = -1;
	world->menu.active_cp = -1;
	world->menu.nb_others_rb = 2;
	world->menu.nb_others_grb = 2;
	world->menu.cartoon = ft_parse_bmp(PATH"/resources/textures/cartoon.bmp");
	world->menu.cartoon2 = ft_parse_bmp(PATH"/resources/textures/cartoon2.bmp");
	world->menu.photo = ft_parse_bmp(PATH"/resources/textures/photo.bmp");
	world->menu.video = ft_parse_bmp(PATH"/resources/textures/video.bmp");
	world->menu.stop = ft_parse_bmp(PATH"/resources/textures/stop.bmp");
	world->menu.save = ft_parse_bmp(PATH"/resources/textures/save.bmp");
	world->menu.light_point_t = ft_parse_bmp(PATH"/resources/textures/light-point_t.bmp");
	world->menu.light_spotlight_t = ft_parse_bmp(PATH"/resources/textures/light-spotlight_t.bmp");
	world->menu.light_directional_t = ft_parse_bmp(PATH"/resources/textures/light-directional_t.bmp");
	world->menu.light_point = ft_parse_bmp(PATH"/resources/textures/light-point.bmp");
	world->menu.light_spotlight = ft_parse_bmp(PATH"/resources/textures/light-spotlight.bmp");
	world->menu.light_directional = ft_parse_bmp(PATH"/resources/textures/light-directional.bmp");
	world->menu.ebloui = ft_parse_bmp(PATH"/resources/textures/ebloui.bmp");
	world->menu.stereoscope = ft_parse_bmp(PATH"/resources/textures/stereoscope.bmp");
}

t_canvas		*new_canvas(void)
{
	t_canvas	*canvas;

	if ((canvas = malloc(sizeof(t_canvas))) == NULL)
		return (NULL);
	canvas->win_size.x = -1;
	canvas->win_size.y = -1;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (NULL);
	if (TTF_Init() < 0)
		return (NULL);
	return (canvas);
}

int			ft_init_sdl(t_world *world)
{
	t_pixel	div;

	if (world->canvas->win_size.x == -1 && world->canvas->win_size.y == -1)
	{
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		printf("DIM %d\n", dm.h);
		if (dm.w >= 2560 && dm.h >= 1440)
		{
			world->canvas->win_size.x = 1600 - MENU_WIDTH;
			world->canvas->win_size.y = 1200 - PROGRESS_BAR_HEIGHT;
		}
		else
		{
			world->canvas->win_size.x = dm.w - MENU_WIDTH;
			world->canvas->win_size.y = dm.h - PROGRESS_BAR_HEIGHT - 44;
		}
	}
	div = fast_div(world->canvas);
	world->canvas->fast_win_size.x = world->canvas->win_size.x / div.x / FAST_RATIO;
	world->canvas->fast_win_size.y = world->canvas->win_size.y / div.y / FAST_RATIO;
	world->canvas->halved_win_size.x = world->canvas->win_size.x / 2;
	world->canvas->halved_win_size.y = world->canvas->win_size.y / 2;
	world->canvas->ratio = (double)(world->canvas->win_size.x) / (double)(world->canvas->win_size.y);
	world->canvas->pb_rect.x = 0;
	world->canvas->pb_rect.w = 0;
	world->canvas->pb_rect.h = PROGRESS_BAR_HEIGHT;
	world->canvas->npixels = world->canvas->win_size.x * world->canvas->win_size.y;
	world->cam->pd = ZOOM / world->canvas->win_size.x;

	world->canvas->win.x = 0;
	world->canvas->win.y = 0;
	world->canvas->win.w = world->canvas->win_size.x;
	if (world->canvas->win_size.y < MENU_HEIGHT)
		world->canvas->win.h = MENU_HEIGHT + PROGRESS_BAR_HEIGHT;
	else
		world->canvas->win.h = world->canvas->win_size.y + PROGRESS_BAR_HEIGHT;
	world->canvas->pb_rect.y = world->canvas->win.h - PROGRESS_BAR_HEIGHT;
	world->canvas->screen.w = world->canvas->win_size.x;
	world->canvas->screen.h = world->canvas->win_size.y;
	//world->canvas->screen.x = (world->canvas->win.w / 2) - (world->canvas->screen.w / 2);
	world->canvas->screen.x = 0;
	world->canvas->screen.y = ((world->canvas->win.h - PROGRESS_BAR_HEIGHT) / 2) - (world->canvas->screen.h / 2);
	if (!(world->canvas->window = SDL_CreateWindow("rt",
					world->canvas->win.x, world->canvas->win.y,
					world->canvas->win.w + MENU_WIDTH, world->canvas->win.h, 0)))
		return (0);
	if(!(world->canvas->renderer = SDL_CreateRenderer(world->canvas->window, -1, 0)))
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
	return (1);
}
