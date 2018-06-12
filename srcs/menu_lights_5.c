/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lights_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 07:57:11 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 05:29:50 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_lights_bloc2_rangebars_2(t_world *world, int i, int pos)
{
	if (pos >= world->menu.lights_rb[i].pix.x &&
			pos <= (world->menu.lights_rb[i].pix.x + 100))
	{
		world->menu.rect.x = pos;
		world->menu.rect.y = world->menu.lights_rb[i].pix.y - 3;
		world->menu.rect.w = 8;
		world->menu.rect.h = 12;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x222222);
		ft_add_menu_surface(world);
	}
}

void	ft_menu_lights_bloc2_rangebars(t_world *world)
{
	int		i;
	int		pos;

	i = 0;
	while (i < world->menu.nb_lights_rb)
	{
		world->menu.rect.x = world->menu.lights_rb[i].pix.x;
		world->menu.rect.y = world->menu.lights_rb[i].pix.y;
		world->menu.rect.w = 108;
		world->menu.rect.h = 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x888888);
		ft_add_menu_surface(world);
		if (i <= 1)
			pos = world->menu.lights_rb[i].pix.x
				+ ((*(world->menu.lights_rb[i].value) * 100)
						/ world->menu.lights_rb[i].max);
		else
			pos = world->menu.lights_rb[i].pix.x
				+ (((*(world->menu.lights_rb[i].value) + 1) * 100)
						/ world->menu.lights_rb[i].max);
		ft_menu_lights_bloc2_rangebars_2(world, i, pos);
		i++;
	}
}

void	ft_menu_lights_bloc2_type_3(t_world *world, t_bmp_parser bmp)
{
	world->menu.rect.x = world->canvas->win.w + 105;
	world->menu.rect.y = 765;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
	bmp = world->menu.light_spotlight;
	world->menu.rect.x = world->canvas->win.w + 220;
	world->menu.rect.y = 765;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
	bmp = world->menu.light_directional;
	world->menu.rect.x = world->canvas->win.w + 335;
	world->menu.rect.y = 765;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
}
