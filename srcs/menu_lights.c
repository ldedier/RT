/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:32:31 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 07:53:44 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_lights_bloc2(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 40;
	world->menu.rect.y = 420;
	world->menu.rect.w = MENU_WIDTH - 80;
	world->menu.rect.h = 440;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	ft_menu_lights_bloc2_position_1(world);
	ft_menu_lights_bloc2_position_2(world);
	ft_menu_lights_bloc2_angle(world);
	ft_menu_lights_bloc2_ebloui(world);
	ft_menu_lights_bloc2_stereoscope(world);
	ft_menu_lights_bloc2_intensity_color_1(world);
	ft_menu_lights_bloc2_intensity_color_2(world);
	ft_menu_lights_bloc2_rotation(world);
	ft_menu_lights_bloc2_type(world);
	ft_menu_lights_bloc2_rangebars(world);
}

void	ft_menu_lights_bloc1_scrollbar(t_world *world)
{
	int		i;
	int		j;
	int		y0;
	int		y1;

	i = 0;
	j = 0;
	world->menu.nb_lights = 0;
	world->menu.first_light.x = -1;
	while (i < world->nlights)
	{
		y0 = 145 + i * (50 + 15) -
			(world->menu.scroll_lights.pos * world->menu.fact_lights);
		y1 = y0 + 50;
		if ((y0 >= 135 && y0 <= 400) || (y1 >= 135 && y1 <= 400))
			ft_menu_lights_bloc1_scrollbar_2(world, i, &j, y0);
		i++;
	}
}

void	ft_menu_lights_bloc1_2(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_lights.len - 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140 + world->menu.scroll_lights.pos;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_lights.height;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
}

void	ft_menu_lights_bloc1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 40;
	world->menu.rect.y = 135;
	world->menu.rect.w = MENU_WIDTH - 80;
	world->menu.rect.h = world->menu.scroll_lights.len;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	ft_menu_lights_bloc1_2(world);
	ft_menu_lights_bloc1_scrollbar(world);
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

void	ft_menu_lights(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 180;
	world->menu.rect.y = 30;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);
	ft_menu_lights_bloc1(world);
	if (world->nlights > 0)
		ft_menu_lights_bloc2(world);
}
