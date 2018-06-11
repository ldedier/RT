/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lights_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 07:55:53 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 07:57:01 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_lights_bloc2_type_2(t_world *world)
{
	if (world->lights[world->menu.active_light].type == 'p')
		world->menu.rect.x = world->canvas->win.w + 95;
	else if (world->lights[world->menu.active_light].type == 's')
		world->menu.rect.x = world->canvas->win.w + 210;
	else
		world->menu.rect.x = world->canvas->win.w + 325;
	world->menu.rect.y = 755;
	world->menu.rect.w = 80;
	world->menu.rect.h = 80;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	if (world->lights[world->menu.active_light].type == 'p')
		world->menu.rect.x = world->canvas->win.w + 103;
	else if (world->lights[world->menu.active_light].type == 's')
		world->menu.rect.x = world->canvas->win.w + 218;
	else
		world->menu.rect.x = world->canvas->win.w + 333;
	world->menu.rect.y = 763;
	world->menu.rect.w = 64;
	world->menu.rect.h = 64;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
}

void	ft_menu_lights_bloc2_type(t_world *world)
{
	t_bmp_parser	bmp;

	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 750;
	world->menu.rect.w = 370;
	world->menu.rect.h = 90;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	ft_menu_lights_bloc2_type_2(world);
	bmp = world->menu.light_point;
	ft_menu_lights_bloc2_type_3(world, bmp);
}

void	ft_menu_lights_bloc2_rotation(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 265;
	world->menu.rect.y = 560;
	world->menu.rect.w = 150;
	world->menu.rect.h = 170;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 265;
	world->menu.rect.y = 560;
	world->menu.rect.w = 150;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 299;
	world->menu.rect.y = 569;
	world->menu.rect.w = 85;
	world->menu.rect.h = 24;
	ft_add_text(world, 1, "Rotation", world->menu.white_color);
}

void	ft_menu_lights_bloc2_intensity_color_2(t_world *world)
{
	t_color	color;

	color.r = 255 - world->menu.lights_cp[0].color->r;
	color.g = 255 - world->menu.lights_cp[0].color->g;
	color.b = 255 - world->menu.lights_cp[0].color->b;
	color.col = (color.r << 16) | (color.g << 8) | color.b;
	world->menu.rect.x = world->menu.lights_cp[0].pix.x
	+ world->menu.lights_cp[0].pos.x - 5;
	world->menu.rect.y = world->menu.lights_cp[0].pix.y
	+ world->menu.lights_cp[0].pos.y - 1;
	world->menu.rect.w = 10;
	world->menu.rect.h = 2;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.lights_cp[0].pix.x
	+ world->menu.lights_cp[0].pos.x - 1;
	world->menu.rect.y = world->menu.lights_cp[0].pix.y
	+ world->menu.lights_cp[0].pos.y - 5;
	world->menu.rect.w = 2;
	world->menu.rect.h = 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
}

void	ft_menu_lights_bloc2_intensity_color_1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 85;
	world->menu.rect.y = 560;
	world->menu.rect.w = 150;
	world->menu.rect.h = 170;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.lights_cp[0].pix.x;
	world->menu.rect.y = world->menu.lights_cp[0].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
}
