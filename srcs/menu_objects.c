/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:31:49 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 09:02:05 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc2(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 40;
	world->menu.rect.y = 420;
	world->menu.rect.w = MENU_WIDTH - 80;
	world->menu.rect.h = 440;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	ft_menu_objects_bloc2_position_1(world);
	ft_menu_objects_bloc2_position_2(world);
	ft_menu_objects_bloc2_position_3(world);
	ft_menu_objects_bloc2_scale(world);
	ft_menu_objects_bloc2_shine(world);
	ft_menu_objects_bloc2_reflection(world);
	ft_menu_objects_bloc2_refraction(world);
	ft_menu_objects_bloc2_transparency(world);
	ft_menu_objects_bloc2_color_1(world);
	ft_menu_objects_bloc2_color_2(world);
	ft_menu_objects_bloc2_rotation(world);
	ft_menu_objects_bloc2_perturbations(world);
	ft_menu_objects_bloc2_negative(world);
	ft_menu_objects_bloc2_rangebars(world);
}

void	ft_menu_objects_bloc1_end(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 55;
	world->menu.rect.y = 80;
	world->menu.rect.w = 360;
	world->menu.rect.h = 55;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 55;
	world->menu.rect.y = 400;
	world->menu.rect.w = 360;
	world->menu.rect.h = 65;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 40;
	world->menu.rect.y = 135;
	world->menu.rect.w = MENU_WIDTH - 80;
	world->menu.rect.h = world->menu.scroll_lights.len;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_lights.len - 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140 + world->menu.scroll_objects.pos;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_objects.height;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_menu_objects_bloc1_scrollbar(world);
	ft_menu_objects_bloc1_end(world);
}

void	ft_menu_objects(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 30;
	world->menu.rect.y = 30;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);
	ft_menu_objects_bloc1(world);
	if (world->menu.nobjects > 0)
		ft_menu_objects_bloc2(world);
}
