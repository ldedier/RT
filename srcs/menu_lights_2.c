/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lights_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 07:53:51 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 08:15:32 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_lights_bloc1_scrollbar_6(t_world *world, int i, int y0)
{
	t_bmp_parser	bmp;

	if (world->lights[i].type == 'p')
		bmp = world->menu.light_point_t;
	else if (world->lights[i].type == 's')
		bmp = world->menu.light_spotlight_t;
	else
		bmp = world->menu.light_directional_t;
	world->menu.rect.x = world->canvas->win.w + 350;
	world->menu.rect.y = y0 + 5;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface_3(world, bmp, 0x222222);
	ft_add_menu_surface(world);
}

void	ft_menu_lights_bloc1_scrollbar_5(t_world *world, int i, int y0)
{
	world->menu.rect.x = world->canvas->win.w + 255;
	world->menu.rect.y = y0 + 17;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 258;
	world->menu.rect.y = y0 + 20;
	world->menu.rect.w = 34;
	world->menu.rect.h = 14;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, world->lights[i].c.col);
	ft_add_menu_surface(world);
}

void	ft_menu_lights_bloc1_scrollbar_4(t_world *world, int i, int y0)
{
	char	*str;
	char	*str2;

	world->menu.rect.x = world->canvas->win.w + 80;
	world->menu.rect.y = y0 + 15;
	world->menu.rect.w = 85;
	world->menu.rect.h = 25;
	str2 = ft_itoa(i);
	str = ft_strjoin("Light ", str2);
	ft_add_text(world, 0, str, world->menu.black_color);
	free(str);
	free(str2);
}

void	ft_menu_lights_bloc1_scrollbar_3(t_world *world, int i, int y0)
{
	char	*str;
	char	*str2;

	world->menu.rect.x = world->canvas->win.w + 55;
	world->menu.rect.y = y0;
	world->menu.rect.w = 140;
	world->menu.rect.h = 50;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 80;
	world->menu.rect.y = y0 + 15;
	world->menu.rect.w = 85;
	world->menu.rect.h = 25;
	str2 = ft_itoa(i);
	str = ft_strjoin("Light ", str2);
	ft_add_text(world, 0, str, world->menu.white_color);
	free(str);
	free(str2);
}

void	ft_menu_lights_bloc1_scrollbar_2(t_world *world, int i, int *j, int y0)
{
	if (world->menu.first_light.x == -1)
	{
		world->menu.first_light.x = i;
		world->menu.first_light.y = y0;
	}
	world->menu.lights[*j] = i;
	*j += 1;
	(world->menu.nb_lights)++;
	world->menu.rect.x = world->canvas->win.w + 55;
	world->menu.rect.y = y0;
	world->menu.rect.w = 360;
	world->menu.rect.h = 50;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	if (i == world->menu.active_light)
		ft_menu_lights_bloc1_scrollbar_3(world, i, y0);
	else
		ft_menu_lights_bloc1_scrollbar_4(world, i, y0);
	ft_menu_lights_bloc1_scrollbar_5(world, i, y0);
	ft_menu_lights_bloc1_scrollbar_6(world, i, y0);
}
