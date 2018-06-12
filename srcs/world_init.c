/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 04:50:37 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 06:45:34 by lcavalle         ###   ########.fr       */
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

void	set_defaults_4(t_world *world)
{
	world->menu.stop = ft_parse_bmp(PATH"/resources/textures/stop.bmp");
	world->menu.save = ft_parse_bmp(PATH"/resources/textures/save.bmp");
	world->menu.light_point_t =
		ft_parse_bmp(PATH"/resources/textures/light-point_t.bmp");
	world->menu.light_spotlight_t =
		ft_parse_bmp(PATH"/resources/textures/light-spotlight_t.bmp");
	world->menu.light_directional_t =
		ft_parse_bmp(PATH"/resources/textures/light-directional_t.bmp");
	world->menu.light_point =
		ft_parse_bmp(PATH"/resources/textures/light-point.bmp");
	world->menu.light_spotlight =
		ft_parse_bmp(PATH"/resources/textures/light-spotlight.bmp");
	world->menu.light_directional =
		ft_parse_bmp(PATH"/resources/textures/light-directional.bmp");
	world->menu.ebloui = ft_parse_bmp(PATH"/resources/textures/ebloui.bmp");
	world->menu.stereoscope =
		ft_parse_bmp(PATH"/resources/textures/stereoscope.bmp");
	world->menu.none = ft_parse_bmp(PATH"/resources/textures/none.bmp");
	world->menu.ripple = ft_parse_bmp(PATH"/resources/textures/ripple.bmp");
	world->menu.waves = ft_parse_bmp(PATH"/resources/textures/waves.bmp");
	world->menu.noise = ft_parse_bmp(PATH"/resources/textures/noise.bmp");
	world->menu.chess = ft_parse_bmp(PATH"/resources/textures/chess.bmp");
	world->menu.perlin = ft_parse_bmp(PATH"/resources/textures/perlin.bmp");
	world->menu.marble = ft_parse_bmp(PATH"/resources/textures/marble.bmp");
	world->menu.negative = ft_parse_bmp(PATH"/resources/textures/negative.bmp");
}

void	set_defaults_3(t_world *world)
{
	ft_init_keys(world);
	world->max_bounce = 4;
	world->menu.type = MENU_OBJECTS;
	world->menu.black_color.r = 0;
	world->menu.black_color.g = 0;
	world->menu.black_color.b = 0;
	world->menu.black_color.a = 0;
	world->menu.white_color.r = 255;
	world->menu.white_color.g = 255;
	world->menu.white_color.b = 255;
	world->menu.white_color.a = 255;
	world->menu.fonts[0] = ft_load_font(PATH"/resources/fonts/Raleway.ttf",
			200);
	world->menu.fonts[1] = ft_load_font(PATH"/resources/fonts/Raleway-Bold.ttf",
			200);
	world->menu.active_rb = -1;
	world->menu.active_grb = -1;
	world->menu.active_cp = -1;
	world->menu.nb_others_rb = 2;
	world->menu.nb_others_grb = 2;
	world->menu.cartoon = ft_parse_bmp(PATH"/resources/textures/cartoon.bmp");
	world->menu.cartoon2 = ft_parse_bmp(PATH"/resources/textures/cartoon2.bmp");
	world->menu.photo = ft_parse_bmp(PATH"/resources/textures/photo.bmp");
	world->menu.video = ft_parse_bmp(PATH"/resources/textures/video.bmp");
	set_defaults_4(world);
}

void	set_defaults_2(t_world *world)
{
	int	i;

	world->stereoscopic = 0;
	world->exporting_video = 0;
	i = -1;
	while (++i < NTHREADS)
		world->thr_state[i] = 0;
	i = -1;
	while (++i < e_nfilters)
		world->filters[i] = 0;
}

void	set_defaults(t_world *world)
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
	world->ticks = SDL_GetTicks();
	world->aa_sq_size = AA_SQ_SIZE;
	set_defaults_2(world);
	set_defaults_3(world);
}
