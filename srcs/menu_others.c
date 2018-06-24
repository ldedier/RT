/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:33:14 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 07:09:24 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_others_bloc2_2(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 680;
	world->menu.rect.w = MENU_WIDTH - 130;
	world->menu.rect.h = 160;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 680;
	world->menu.rect.w = MENU_WIDTH - 130;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 210;
	world->menu.rect.y = 690;
	world->menu.rect.w = 70;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Export", world->menu.white_color);
}

void	ft_menu_others_bloc2(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 40;
	world->menu.rect.y = 660;
	world->menu.rect.w = MENU_WIDTH - 80;
	world->menu.rect.h = 200;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	ft_menu_others_bloc2_2(world);
	ft_menu_others_bloc2_photo(world);
	ft_menu_others_bloc2_video(world);
	ft_menu_others_bloc2_save(world);
}

void	ft_menu_others_bloc1_ambient(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 130;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 230;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 130;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 109;
	world->menu.rect.y = 140;
	world->menu.rect.w = 80;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Ambient", world->menu.white_color);
}

void	ft_menu_others_bloc1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 40;
	world->menu.rect.y = 110;
	world->menu.rect.w = MENU_WIDTH - 80;
	world->menu.rect.h = 530;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	ft_menu_others_bloc1_ambient(world);
	ft_menu_others_bloc1_fog(world);
	ft_menu_others_bloc1_ambient_color_1(world);
	ft_menu_others_bloc1_ambient_color_2(world);
	ft_menu_others_bloc1_fog_color_1(world);
	ft_menu_others_bloc1_fog_color_2(world);
	ft_menu_others_bloc1_filters(world);
	ft_menu_others_bloc1_bounces(world);
	ft_menu_others_bloc1_antialiasing(world);
	ft_menu_others_bloc1_rangebars(world);
	ft_menu_others_bloc1_grangebars(world);
	ft_menu_others_bloc1_cartoon(world);
	if (world->menu.filter_active == 1)
		ft_show_filters(world);
}

void	ft_menu_others(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 330;
	world->menu.rect.y = 30;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);
	ft_menu_others_bloc1(world);
	ft_menu_others_bloc2(world);
}
