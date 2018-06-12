/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_others_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 00:17:49 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 00:18:00 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_others_bloc2_save(t_world *world)
{
	t_bmp_parser	bmp;

	bmp = world->menu.save;
	world->menu.rect.x = world->canvas->win.w + 345;
	world->menu.rect.y = 752;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface_2(world, bmp, 0xF8F8FF);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc2_video(t_world *world)
{
	t_bmp_parser	bmp;

	if (world->exporting_video == 1)
	{
		bmp = world->menu.stop;
		world->menu.rect.x = world->canvas->win.w + 225;
		world->menu.rect.y = 751;
	}
	else
	{
		bmp = world->menu.video;
		world->menu.rect.x = world->canvas->win.w + 220;
		world->menu.rect.y = 760;
	}
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface_2(world, bmp, 0xF8F8FF);
	ft_add_menu_surface(world);
}
