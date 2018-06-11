/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:56:07 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 09:10:41 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc2_rangebars_2(t_world *world, int i)
{
	world->menu.rect.y = world->menu.objects_rb[i].pix.y - 3;
	world->menu.rect.w = 8;
	world->menu.rect.h = 12;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc2_rangebars(t_world *world)
{
	int		i;

	i = 0;
	while (i < world->menu.nb_objects_rb)
	{
		world->menu.rect.x = world->menu.objects_rb[i].pix.x;
		world->menu.rect.y = world->menu.objects_rb[i].pix.y;
		world->menu.rect.w = 108;
		world->menu.rect.h = 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x888888);
		ft_add_menu_surface(world);
		if (i <= 4)
			world->menu.rect.x = world->menu.objects_rb[i].pix.x
				+ ((*(world->menu.objects_rb[i].value) * 100)
						/ world->menu.objects_rb[i].max);
		else
			world->menu.rect.x = world->menu.objects_rb[i].pix.x
				+ (((*(world->menu.objects_rb[i].value) + 2) * 100)
						/ world->menu.objects_rb[i].max);
		ft_menu_objects_bloc2_rangebars_2(world, i);
		i++;
	}
}

void	ft_menu_objects_bloc2_negative_2(t_world *world, t_bmp_parser bmp)
{
	if (world->selected_cobject->negative)
	{
		world->menu.rect.x = world->canvas->win.w + 347;
		world->menu.rect.y = 432;
		world->menu.rect.w = bmp.width + 6;
		world->menu.rect.h = bmp.height + 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
	}
}

void	ft_menu_objects_bloc2_negative(t_world *world)
{
	t_bmp_parser	bmp;

	bmp = world->menu.negative;
	if (world->selected_cobject->id == world->menu.active_object)
		ft_menu_objects_bloc2_negative_2(world, bmp);
	else if (world->selected_object->negative)
	{
		world->menu.rect.x = world->canvas->win.w + 347;
		world->menu.rect.y = 432;
		world->menu.rect.w = bmp.width + 6;
		world->menu.rect.h = bmp.height + 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
	}
	world->menu.rect.x = world->canvas->win.w + 350;
	world->menu.rect.y = 435;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
}
