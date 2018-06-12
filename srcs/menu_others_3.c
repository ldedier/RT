/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_others_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 07:05:04 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 00:24:05 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_others_bloc1_rangebars_2(t_world *world, int i, int pos)
{
	world->menu.rect.x = pos;
	world->menu.rect.y = world->menu.others_rb[i].pix.y - 3;
	world->menu.rect.w = 8;
	world->menu.rect.h = 12;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_rangebars(t_world *world)
{
	int		i;
	int		pos;

	i = 0;
	while (i < world->menu.nb_others_rb)
	{
		world->menu.rect.x = world->menu.others_rb[i].pix.x;
		world->menu.rect.y = world->menu.others_rb[i].pix.y;
		world->menu.rect.w = 108;
		world->menu.rect.h = 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x888888);
		ft_add_menu_surface(world);
		pos = world->menu.others_rb[i].pix.x
			+ ((*(world->menu.others_rb[i].value) * 100)
					/ world->menu.others_rb[i].max);
		if (pos >= world->menu.others_rb[i].pix.x &&
				pos <= (world->menu.others_rb[i].pix.x + 100))
			ft_menu_others_bloc1_rangebars_2(world, i, pos);
		i++;
	}
}

void	ft_menu_others_bloc1_antialiasing(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 265;
	world->menu.rect.y = 440;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 265;
	world->menu.rect.y = 440;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 289;
	world->menu.rect.y = 450;
	world->menu.rect.w = 125;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Anti-Aliasing", world->menu.white_color);
}

void	ft_menu_others_bloc1_bounces(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 440;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 440;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 111;
	world->menu.rect.y = 450;
	world->menu.rect.w = 80;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Bounces", world->menu.white_color);
}

void	ft_menu_others_bloc1_filters(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 380;
	world->menu.rect.w = (MENU_WIDTH - 160) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 122;
	world->menu.rect.y = 390;
	world->menu.rect.w = 55;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Filter", world->menu.white_color);
	world->menu.rect.x = world->menu.filters.pos.x;
	world->menu.rect.y = world->menu.filters.pos.y;
	world->menu.rect.w = world->menu.filters.size.x;
	world->menu.rect.h = world->menu.filters.size.y;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	ft_switch_filter(world, world->menu.filters_list[0], 0);
}
