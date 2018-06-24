/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_others_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 07:01:23 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 07:03:09 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_others_bloc1_fog_color_2(t_world *world)
{
	t_color	color;

	color.r = 255 - world->menu.others_cp[1].color->r;
	color.g = 255 - world->menu.others_cp[1].color->g;
	color.b = 255 - world->menu.others_cp[1].color->b;
	color.col = (color.r << 16) | (color.g << 8) | color.b;
	world->menu.rect.x = world->menu.others_cp[1].pix.x
		+ world->menu.others_cp[1].pos.x - 5;
	world->menu.rect.y = world->menu.others_cp[1].pix.y
		+ world->menu.others_cp[1].pos.y - 1;
	world->menu.rect.w = 10;
	world->menu.rect.h = 2;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[1].pix.x
		+ world->menu.others_cp[1].pos.x - 1;
	world->menu.rect.y = world->menu.others_cp[1].pix.y
		+ world->menu.others_cp[1].pos.y - 5;
	world->menu.rect.w = 2;
	world->menu.rect.h = 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_fog_color_1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 329;
	world->menu.rect.y = 180;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 332;
	world->menu.rect.y = 183;
	world->menu.rect.w = 34;
	world->menu.rect.h = 14;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL,
			world->menu.others_cp[1].color->col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[1].pix.x;
	world->menu.rect.y = world->menu.others_cp[1].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_ambient_color_2(t_world *world)
{
	t_color	color;

	color.r = 255 - world->menu.others_cp[0].color->r;
	color.g = 255 - world->menu.others_cp[0].color->g;
	color.b = 255 - world->menu.others_cp[0].color->b;
	color.col = (color.r << 16) | (color.g << 8) | color.b;
	world->menu.rect.x = world->menu.others_cp[0].pix.x
		+ world->menu.others_cp[0].pos.x - 5;
	world->menu.rect.y = world->menu.others_cp[0].pix.y
		+ world->menu.others_cp[0].pos.y - 1;
	world->menu.rect.w = 10;
	world->menu.rect.h = 2;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[0].pix.x
		+ world->menu.others_cp[0].pos.x - 1;
	world->menu.rect.y = world->menu.others_cp[0].pix.y
		+ world->menu.others_cp[0].pos.y - 5;
	world->menu.rect.w = 2;
	world->menu.rect.h = 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_ambient_color_1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 129;
	world->menu.rect.y = 180;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 132;
	world->menu.rect.y = 183;
	world->menu.rect.w = 34;
	world->menu.rect.h = 14;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL,
			world->menu.others_cp[0].color->col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[0].pix.x;
	world->menu.rect.y = world->menu.others_cp[0].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_fog(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 265;
	world->menu.rect.y = 130;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 230;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 265;
	world->menu.rect.y = 130;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 329;
	world->menu.rect.y = 140;
	world->menu.rect.w = 40;
	world->menu.rect.h = 18;
	ft_add_text(world, 1, "Fog", world->menu.white_color);
}
