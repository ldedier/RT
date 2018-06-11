/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lights_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 07:54:41 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 22:43:13 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_lights_bloc2_stereoscope(t_world *world)
{
	t_bmp_parser	bmp;

	bmp = world->menu.stereoscope;
	if (world->stereoscopic == 1)
	{
		world->menu.rect.x = world->canvas->win.w + 362;
		world->menu.rect.y = 492;
		world->menu.rect.w = bmp.width + 6;
		world->menu.rect.h = bmp.height + 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
	}
	world->menu.rect.x = world->canvas->win.w + 365;
	world->menu.rect.y = 495;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
}

void	ft_menu_lights_bloc2_ebloui(t_world *world)
{
	t_bmp_parser	bmp;

	bmp = world->menu.ebloui;
	if (1)
	{
		world->menu.rect.x = world->canvas->win.w + 362;
		world->menu.rect.y = 432;
		world->menu.rect.w = bmp.width + 6;
		world->menu.rect.h = bmp.height + 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
	}
	world->menu.rect.x = world->canvas->win.w + 365;
	world->menu.rect.y = 435;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
}

void	ft_menu_lights_bloc2_angle(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 500;
	world->menu.rect.w = 280;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 500;
	world->menu.rect.w = 120;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 92;
	world->menu.rect.y = 510;
	world->menu.rect.w = 65;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Angle", world->menu.white_color);
}

void	ft_menu_lights_bloc2_position_2(t_world *world)
{
	char	*str;

	str = ft_itoa((int)(world->lights[world->menu.active_light].o.x));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 215 - world->menu.rect.w / 2;
	world->menu.rect.y = 450;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str, world->menu.black_color);
	free(str);
	str = ft_itoa((int)(world->lights[world->menu.active_light].o.y));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 262 - world->menu.rect.w / 2;
	world->menu.rect.y = 450;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str, world->menu.black_color);
	free(str);
	str = ft_itoa((int)(world->lights[world->menu.active_light].o.z));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 309 - world->menu.rect.w / 2;
	world->menu.rect.y = 450;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str, world->menu.black_color);
	free(str);
}

void	ft_menu_lights_bloc2_position_1(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 440;
	world->menu.rect.w = 280;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 440;
	world->menu.rect.w = 120;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 82;
	world->menu.rect.y = 450;
	world->menu.rect.w = 85;
	world->menu.rect.h = 22;
	ft_add_text(world, 1, "Position", world->menu.white_color);
}
