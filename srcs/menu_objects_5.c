/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:55:57 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 09:12:51 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc2_perturbations_9(t_world *world, t_bmp_parser bmp)
{
	bmp = world->menu.marble;
	world->menu.rect.x = world->canvas->win.w + 80 + 6 * 50;
	world->menu.rect.y = 790;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc2_perturbations_8(t_world *world, t_bmp_parser bmp)
{
	bmp = world->menu.noise;
	world->menu.rect.x = world->canvas->win.w + 80 + 3 * 50;
	world->menu.rect.y = 790;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
	bmp = world->menu.chess;
	world->menu.rect.x = world->canvas->win.w + 80 + 4 * 50;
	world->menu.rect.y = 790;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
	bmp = world->menu.perlin;
	world->menu.rect.x = world->canvas->win.w + 80 + 5 * 50;
	world->menu.rect.y = 790;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc2_perturbations_7(t_world *world, t_bmp_parser bmp)
{
	world->menu.rect.x = world->canvas->win.w + 80;
	world->menu.rect.y = 790;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
	bmp = world->menu.ripple;
	world->menu.rect.x = world->canvas->win.w + 80 + 1 * 50;
	world->menu.rect.y = 790;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
	bmp = world->menu.waves;
	world->menu.rect.x = world->canvas->win.w + 80 + 2 * 50;
	world->menu.rect.y = 790;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface(world, bmp);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc2_perturbations_6(t_world *world)
{
	if (world->selected_object->pert == e_none)
		world->menu.rect.x = world->canvas->win.w + 79;
	else if (world->selected_object->pert == e_ripple)
		world->menu.rect.x = world->canvas->win.w + 79 + 50;
	else if (world->selected_object->pert == e_waves)
		world->menu.rect.x = world->canvas->win.w + 79 + 100;
	else if (world->selected_object->pert == e_noise)
		world->menu.rect.x = world->canvas->win.w + 79 + 150;
	else if (world->selected_object->pert == e_chess)
		world->menu.rect.x = world->canvas->win.w + 79 + 200;
	else if (world->selected_object->pert == e_perlin)
		world->menu.rect.x = world->canvas->win.w + 79 + 250;
	else
		world->menu.rect.x = world->canvas->win.w + 79 + 300;
}

void	ft_menu_objects_bloc2_perturbations_5(t_world *world)
{
	if (world->selected_cobject->pert == e_none)
		world->menu.rect.x = world->canvas->win.w + 79;
	else if (world->selected_cobject->pert == e_ripple)
		world->menu.rect.x = world->canvas->win.w + 79 + 50;
	else if (world->selected_cobject->pert == e_waves)
		world->menu.rect.x = world->canvas->win.w + 79 + 100;
	else if (world->selected_cobject->pert == e_noise)
		world->menu.rect.x = world->canvas->win.w + 79 + 150;
	else if (world->selected_cobject->pert == e_chess)
		world->menu.rect.x = world->canvas->win.w + 79 + 200;
	else if (world->selected_cobject->pert == e_perlin)
		world->menu.rect.x = world->canvas->win.w + 79 + 250;
	else
		world->menu.rect.x = world->canvas->win.w + 79 + 300;
}
