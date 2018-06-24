/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:55:34 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 09:02:49 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc2_shine(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 2 * 55;
	world->menu.rect.w = 240;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 2 * 55;
	world->menu.rect.w = 100;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 73;
	world->menu.rect.y = 451 + 2 * 55;
	world->menu.rect.w = 50;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Shine", world->menu.white_color);
}

void	ft_menu_objects_bloc2_scale(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 1 * 55;
	world->menu.rect.w = 240;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440 + 1 * 55;
	world->menu.rect.w = 100;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 73;
	world->menu.rect.y = 451 + 1 * 55;
	world->menu.rect.w = 50;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Scale", world->menu.white_color);
}

void	ft_menu_objects_bloc2_position_3(t_world *world)
{
	char	*str;

	if (world->selected_cobject->id == world->menu.active_object)
		str = ft_itoa((int)(world->selected_cobject->o.z));
	else
		str = ft_itoa((int)(world->selected_object->o.z));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 260 - world->menu.rect.w / 2;
	world->menu.rect.y = 450;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str, world->menu.black_color);
	free(str);
}

void	ft_menu_objects_bloc2_position_2(t_world *world)
{
	char	*str;

	if (world->selected_cobject->id == world->menu.active_object)
		str = ft_itoa((int)(world->selected_cobject->o.x));
	else
		str = ft_itoa((int)(world->selected_object->o.x));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 180 - world->menu.rect.w / 2;
	world->menu.rect.y = 450;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str, world->menu.black_color);
	free(str);
	if (world->selected_cobject->id == world->menu.active_object)
		str = ft_itoa((int)(world->selected_cobject->o.y));
	else
		str = ft_itoa((int)(world->selected_object->o.y));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 220 - world->menu.rect.w / 2;
	world->menu.rect.y = 450;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str, world->menu.black_color);
	free(str);
}

void	ft_menu_objects_bloc2_position_1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440;
	world->menu.rect.w = 240;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 50;
	world->menu.rect.y = 440;
	world->menu.rect.w = 100;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 451;
	world->menu.rect.w = 70;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Position", world->menu.white_color);
}
