/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 05:23:28 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 05:23:42 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc1_scrollbar_13(t_world *world, t_object obj, int y0)
{
	t_bmp_parser	bmp;

	if (obj.pert == e_none)
		bmp = world->menu.none;
	else if (obj.pert == e_ripple)
		bmp = world->menu.ripple;
	else if (obj.pert == e_waves)
		bmp = world->menu.waves;
	else if (obj.pert == e_noise)
		bmp = world->menu.noise;
	else if (obj.pert == e_chess)
		bmp = world->menu.chess;
	else if (obj.pert == e_perlin)
		bmp = world->menu.perlin;
	else
		bmp = world->menu.marble;
	world->menu.rect.x = world->canvas->win.w + 350;
	world->menu.rect.y = y0 + 5;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface_3(world, bmp, 0x222222);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc1_scrollbar_12(t_world *world, t_object obj, int y0)
{
	world->menu.rect.x = world->canvas->win.w + 275;
	world->menu.rect.y = y0 + 17;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 278;
	world->menu.rect.y = y0 + 20;
	world->menu.rect.w = 34;
	world->menu.rect.h = 14;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, obj.c.col);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc1_scrollbar_11(t_world *world, t_object obj, int y0)
{
	char	*str;
	char	*str2;

	if (obj.descriptor)
		str = obj.descriptor;
	else
	{
		str2 = ft_itoa(obj.id);
		str = ft_strjoin("Obj ", str2);
	}
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 168 - world->menu.rect.w / 2;
	world->menu.rect.y = y0 + 15;
	world->menu.rect.h = 25;
	ft_add_text(world, 0, str, world->menu.black_color);
	if (obj.descriptor == NULL)
	{
		free(str);
		free(str2);
	}
}
