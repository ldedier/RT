/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 01:10:41 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 01:29:02 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_motion_objects_5(t_world *world, SDL_Event event)
{
	int		i;
	int		x;
	int		y;

	if (world->menu.active_cp >= 0)
	{
		i = world->menu.active_cp;
		x = event.motion.x - world->menu.objects_cp[i].pix.x;
		y = event.motion.y - world->menu.objects_cp[i].pix.y;
		if (x < 0)
			x = 0;
		else if (x > 99)
			x = 99;
		if (y < 0)
			y = 0;
		else if (y > 99)
			y = 99;
		*(world->menu.objects_cp[i].color) = world->menu.color_map[y * 100 + x];
		world->menu.objects_cp[i].pos.x = x;
		world->menu.objects_cp[i].pos.y = y;
		paint_threaded_fast(world);
		return ;
	}
	ft_mouse_motion_objects_6(world, event);
}

void	ft_mouse_motion_objects_4(t_world *world, float value, int i)
{
	if (value >= world->menu.objects_rb[i].min
			&& value <= world->menu.objects_rb[i].max)
		*(world->menu.objects_rb[i].value) = value;
	else
	{
		if (value < world->menu.objects_rb[i].min)
			*(world->menu.objects_rb[i].value) =
				world->menu.objects_rb[i].min;
		if (value > world->menu.objects_rb[i].max)
			*(world->menu.objects_rb[i].value) =
				world->menu.objects_rb[i].max;
	}
	ft_compute_matrices_clist(world->cobjlist);
}

void	ft_mouse_motion_objects_3(t_world *world)
{
	if (world->selected_cobject->id == world->menu.active_object)
	{
		world->selected_cobject->s.x = world->selected_cobject->scale;
		world->selected_cobject->s.y = world->selected_cobject->scale;
		world->selected_cobject->s.z = world->selected_cobject->scale;
	}
	else
	{
		world->selected_object->s.x = world->selected_object->scale;
		world->selected_object->s.y = world->selected_object->scale;
		world->selected_object->s.z = world->selected_object->scale;
	}
	ft_compute_matrices_clist(world->cobjlist);
}

void	ft_mouse_motion_objects_2(t_world *world, float value, int i)
{
	if (value >= world->menu.objects_rb[i].min &&
			value <= world->menu.objects_rb[i].max)
		*(world->menu.objects_rb[i].value) = value;
	else
	{
		if (value < world->menu.objects_rb[i].min)
			*(world->menu.objects_rb[i].value) =
				world->menu.objects_rb[i].min;
		if (value > world->menu.objects_rb[i].max)
			*(world->menu.objects_rb[i].value) =
				world->menu.objects_rb[i].max;
	}
	if (i == 0)
		ft_mouse_motion_objects_3(world);
}

void	ft_mouse_motion_objects(t_world *world, SDL_Event event)
{
	int		i;
	float	value;

	if (world->menu.active_rb >= 0)
	{
		i = world->menu.active_rb;
		value = ((float)(event.motion.x - (world->menu.objects_rb[i].pix.x + 4))
				/ 100) * world->menu.objects_rb[i].max;
		if (i <= 4)
			ft_mouse_motion_objects_2(world, value, i);
		else
			ft_mouse_motion_objects_4(world, value, i);
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
		return ;
	}
	ft_mouse_motion_objects_5(world, event);
}
