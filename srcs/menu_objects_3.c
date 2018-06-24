/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:55:42 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 09:03:32 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc2_color_2(t_world *world)
{
	t_color	color;

	color.r = 255 - world->menu.objects_cp[0].color->r;
	color.g = 255 - world->menu.objects_cp[0].color->g;
	color.b = 255 - world->menu.objects_cp[0].color->b;
	color.col = (color.r << 16) | (color.g << 8) | color.b;
	world->menu.rect.x = world->menu.objects_cp[0].pix.x
		+ world->menu.objects_cp[0].pos.x - 5;
	world->menu.rect.y = world->menu.objects_cp[0].pix.y
		+ world->menu.objects_cp[0].pos.y - 1;
	world->menu.rect.w = 10;
	world->menu.rect.h = 2;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.objects_cp[0].pix.x
		+ world->menu.objects_cp[0].pos.x - 1;
	world->menu.rect.y = world->menu.objects_cp[0].pix.y
		+ world->menu.objects_cp[0].pos.y - 5;
	world->menu.rect.w = 2;
	world->menu.rect.h = 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc2_color_1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 300;
	world->menu.rect.y = 495;
	world->menu.rect.w = 150;
	world->menu.rect.h = 120;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.objects_cp[0].pix.x;
	world->menu.rect.y = world->menu.objects_cp[0].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc2_transparency(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 5 * 55;
	world->menu.rect.w = 240;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 5 * 55;
	world->menu.rect.w = 100;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 58;
	world->menu.rect.y = 451 + 5 * 55;
	world->menu.rect.w = 85;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Transparency", world->menu.white_color);
}

void	ft_menu_objects_bloc2_refraction(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 4 * 55;
	world->menu.rect.w = 240;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 4 * 55;
	world->menu.rect.w = 100;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 63;
	world->menu.rect.y = 451 + 4 * 55;
	world->menu.rect.w = 75;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Refraction", world->menu.white_color);
}

void	ft_menu_objects_bloc2_reflection(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 3 * 55;
	world->menu.rect.w = 240;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 3 * 55;
	world->menu.rect.w = 100;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 63;
	world->menu.rect.y = 451 + 3 * 55;
	world->menu.rect.w = 75;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Reflection", world->menu.white_color);
}
