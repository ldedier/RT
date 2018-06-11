/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:55:50 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 09:12:03 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc2_perturbations_4(t_world *world)
{
	if (world->selected_cobject->id == world->menu.active_object)
		ft_menu_objects_bloc2_perturbations_5(world);
	else
		ft_menu_objects_bloc2_perturbations_6(world);
	world->menu.rect.y = 789;
	world->menu.rect.w = 42;
	world->menu.rect.h = 42;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
}

void	ft_menu_objects_bloc2_perturbations_3(t_world *world)
{
	if (world->selected_object->pert == e_none)
		world->menu.rect.x = world->canvas->win.w + 75;
	else if (world->selected_object->pert == e_ripple)
		world->menu.rect.x = world->canvas->win.w + 75 + 50;
	else if (world->selected_object->pert == e_waves)
		world->menu.rect.x = world->canvas->win.w + 75 + 100;
	else if (world->selected_object->pert == e_noise)
		world->menu.rect.x = world->canvas->win.w + 75 + 150;
	else if (world->selected_object->pert == e_chess)
		world->menu.rect.x = world->canvas->win.w + 75 + 200;
	else if (world->selected_object->pert == e_perlin)
		world->menu.rect.x = world->canvas->win.w + 75 + 250;
	else
		world->menu.rect.x = world->canvas->win.w + 75 + 300;
}

void	ft_menu_objects_bloc2_perturbations_2(t_world *world)
{
	if (world->selected_cobject->pert == e_none)
		world->menu.rect.x = world->canvas->win.w + 75;
	else if (world->selected_cobject->pert == e_ripple)
		world->menu.rect.x = world->canvas->win.w + 75 + 50;
	else if (world->selected_cobject->pert == e_waves)
		world->menu.rect.x = world->canvas->win.w + 75 + 100;
	else if (world->selected_cobject->pert == e_noise)
		world->menu.rect.x = world->canvas->win.w + 75 + 150;
	else if (world->selected_cobject->pert == e_chess)
		world->menu.rect.x = world->canvas->win.w + 75 + 200;
	else if (world->selected_cobject->pert == e_perlin)
		world->menu.rect.x = world->canvas->win.w + 75 + 250;
	else
		world->menu.rect.x = world->canvas->win.w + 75 + 300;
}

void	ft_menu_objects_bloc2_perturbations(t_world *world)
{
	t_bmp_parser	bmp;

	world->menu.rect.x = world->canvas->win.w + 65;
	world->menu.rect.y = 775;
	world->menu.rect.w = 370;
	world->menu.rect.h = 70;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	if (world->selected_cobject->id == world->menu.active_object)
		ft_menu_objects_bloc2_perturbations_2(world);
	else
		ft_menu_objects_bloc2_perturbations_3(world);
	world->menu.rect.y = 785;
	world->menu.rect.w = 50;
	world->menu.rect.h = 50;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_menu_objects_bloc2_perturbations_4(world);
	bmp = world->menu.none;
	ft_menu_objects_bloc2_perturbations_7(world, bmp);
	ft_menu_objects_bloc2_perturbations_8(world, bmp);
	ft_menu_objects_bloc2_perturbations_9(world, bmp);
}

void	ft_menu_objects_bloc2_rotation(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 300;
	world->menu.rect.y = 625;
	world->menu.rect.w = 150;
	world->menu.rect.h = 130;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 300;
	world->menu.rect.y = 625;
	world->menu.rect.w = 150;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 338;
	world->menu.rect.y = 635;
	world->menu.rect.w = 75;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Rotation", world->menu.white_color);
}
