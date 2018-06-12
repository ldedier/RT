/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 05:32:34 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 01:26:23 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_positions_10(t_world *world)
{
	int		n;
	float	k;
	float	size;

	n = world->menu.nobjects;
	if (n == 5)
		k = 2;
	else if (n <= 10)
		k = 1;
	else
		k = ((float)n / 10) - 1;
	size = world->menu.scroll_objects.len / (float)(n * 65 + k * 65);
	world->menu.fact_objects = 1 / size;
}

void	set_positions_9(t_world *world)
{
	world->menu.objects_rb[6] =
		ft_new_rangebar(0, 2 * M_PI, ft_new_pixel(world->canvas->win.w + 320,
					678 + 30), &(world->selected_cobject->r.y));
	world->menu.objects_rb[7] =
		ft_new_rangebar(0, 2 * M_PI, ft_new_pixel(world->canvas->win.w + 320,
					678 + 60), &(world->selected_cobject->r.z));
	world->menu.nb_objects_cp = 1;
	world->menu.objects_cp[0] =
		ft_new_colorpicker(ft_new_pixel(world->canvas->win.w + 325, 505),
				ft_color_pos(world, world->selected_cobject->c),
				&(world->selected_cobject->c));
}

void	set_positions_8(t_world *world)
{
	world->menu.active_object = 0;
	ft_set_selected_object(world, 0);
	world->menu.first_object = 145;
	ft_init_objects(world);
	world->menu.nb_objects_rb = 8;
	world->menu.objects_rb[0] =
		ft_new_rangebar(1, 10, ft_new_pixel(world->canvas->win.w + 165,
					370 + 1 * 55 + 87), &(world->selected_cobject->scale));
	world->menu.objects_rb[1] =
		ft_new_rangebar(0, 100, ft_new_pixel(world->canvas->win.w + 165,
					370 + 2 * 55 + 87), &(world->selected_cobject->shine));
	world->menu.objects_rb[2] =
		ft_new_rangebar(0, 1, ft_new_pixel(world->canvas->win.w + 165,
					370 + 3 * 55 + 87), &(world->selected_cobject->reflect));
	world->menu.objects_rb[3] =
		ft_new_rangebar(0, 5, ft_new_pixel(world->canvas->win.w + 165,
					370 + 4 * 55 + 87), &(world->selected_cobject->refract));
	world->menu.objects_rb[4] =
		ft_new_rangebar(0, 1, ft_new_pixel(world->canvas->win.w + 165,
					370 + 5 * 55 + 87), &(world->selected_cobject->transp));
	world->menu.objects_rb[5] =
		ft_new_rangebar(0, 2 * M_PI, ft_new_pixel(world->canvas->win.w + 320,
					678), &(world->selected_cobject->r.x));
	set_positions_9(world);
}

void	set_positions_7(t_world *world)
{
	int		i;

	if (world->menu.nobjects > 0)
		set_positions_8(world);
	else
	{
		world->menu.active_object = -1;
		world->menu.first_object = -1;
		world->menu.nb_objects_rb = 0;
		world->menu.nb_objects_cp = 0;
	}
	if (world->menu.nobjects <= 4)
		world->menu.nb_objects = world->menu.nobjects;
	else
		world->menu.nb_objects = 4;
	i = 0;
	while (i < 5)
	{
		world->menu.objects[i].x = -1;
		world->menu.objects[i].y = -1;
		i++;
	}
	set_positions_10(world);
}

void	set_positions_6(t_world *world)
{
	int		i;
	int		n;
	float	k;
	float	size;

	i = 0;
	while (i < 5)
		world->menu.lights[i++] = -1;
	n = world->nlights;
	if (n == 5)
		k = 2;
	else if (n <= 10)
		k = 1;
	else
		k = ((float)n / 10) - 1;
	size = world->menu.scroll_lights.len / (float)(n * 65 + k * 65);
	world->menu.fact_lights = 1 / size;
	world->menu.scroll_objects = ft_new_scrollbar(world, 265, 1);
	world->selected_cobject = NULL;
	world->selected_object = NULL;
	set_positions_7(world);
}
