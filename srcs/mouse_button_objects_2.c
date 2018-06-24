/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_objects_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 03:25:00 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 03:37:39 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_button_objects_10(t_world *world, int x, int y)
{
	int		x0;
	int		y0;

	y0 = 135 + 265 + 20 + 15;
	x0 = world->canvas->win.w + 40 + 25 + 280 + 5;
	if (x >= (x0) && x <= (x0 + 50) && y >= (y0) && y <= (y0 + 50))
	{
		ft_mouse_button_objects_11(world);
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_button_objects_12(world, x, y);
}

void	ft_mouse_button_objects_9(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		y0;

	i = 0;
	while (i < world->menu.nb_objects_cp)
	{
		x0 = world->menu.objects_cp[i].pix.x;
		y0 = world->menu.objects_cp[i].pix.y;
		if (x >= (x0) && x <= (x0 + 100) && y >= (y0) && y <= (y0 + 100))
		{
			world->menu.active_cp = i;
			ft_mouse_motion(world, event);
			return ;
		}
		i++;
	}
	ft_mouse_button_objects_10(world, x, y);
}

void	ft_mouse_button_objects_8(t_world *world, SDL_Event event, int x, int y)
{
	int		i;
	int		x0;
	int		x1;
	int		y0;

	i = 0;
	while (i < world->menu.nb_objects_rb)
	{
		x0 = world->menu.objects_rb[i].pix.x
			+ ((world->menu.objects_rb[i].min
						* 100) / world->menu.objects_rb[i].max);
		x1 = world->menu.objects_rb[i].pix.x
			+ ((world->menu.objects_rb[i].max
						* 100) / world->menu.objects_rb[i].max);
		y0 = world->menu.objects_rb[i].pix.y;
		if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) &&
				y <= (y0 - 3 + 12))
		{
			world->menu.active_rb = i;
			ft_mouse_motion(world, event);
			return ;
		}
		i++;
	}
	ft_mouse_button_objects_9(world, event, x, y);
}

void	ft_mouse_button_objects_7(t_world *world)
{
	world->menu.objects_rb[0].value =
		&(world->selected_object->scale);
	world->menu.objects_rb[1].value =
		&(world->selected_object->shine);
	world->menu.objects_rb[2].value =
		&(world->selected_object->reflect);
	world->menu.objects_rb[3].value =
		&(world->selected_object->refract);
	world->menu.objects_rb[4].value =
		&(world->selected_object->transp);
	world->menu.objects_rb[5].value =
		&(world->selected_object->r.x);
	world->menu.objects_rb[6].value =
		&(world->selected_object->r.y);
	world->menu.objects_rb[7].value =
		&(world->selected_object->r.z);
	world->menu.objects_cp[0].color =
		&(world->selected_object->c);
	world->menu.objects_cp[0].pos = ft_color_pos(world,
			world->selected_object->c);
}

void	ft_mouse_button_objects_6(t_world *world)
{
	world->menu.objects_rb[0].value =
		&(world->selected_cobject->scale);
	world->menu.objects_rb[1].value =
		&(world->selected_cobject->shine);
	world->menu.objects_rb[2].value =
		&(world->selected_cobject->reflect);
	world->menu.objects_rb[3].value =
		&(world->selected_cobject->refract);
	world->menu.objects_rb[4].value =
		&(world->selected_cobject->transp);
	world->menu.objects_rb[5].value =
		&(world->selected_cobject->r.x);
	world->menu.objects_rb[6].value =
		&(world->selected_cobject->r.y);
	world->menu.objects_rb[7].value =
		&(world->selected_cobject->r.z);
	world->menu.objects_cp[0].color =
		&(world->selected_cobject->c);
	world->menu.objects_cp[0].pos = ft_color_pos(world,
			world->selected_cobject->c);
}
