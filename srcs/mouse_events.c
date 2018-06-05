/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:28:01 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/06 01:20:13 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_mouse_motion(t_world *world, SDL_Event event)
{
	if (world->focus == 1)
	{
		world->cam->rotation.x = world->cam->rotation.x -
			(event.motion.xrel) * M_PI / 1024.0;
		world->cam->rotation.y = ft_fclamp(-M_PI / 2,
				world->cam->rotation.y - (event.motion.yrel) * M_PI / 1024.0,
				M_PI / 2);
		apply_rotation(world->cam);
		world->keys[mouse_move] = 1;
	}
	if (world->menu.active_rb >= 0)
	{
		int i = world->menu.active_rb;
		float value = ((float)(event.motion.x - (world->menu.others_rb[i].pix.x + 4)) / 100) * world->menu.others_rb[i].max;
		if (value >= world->menu.others_rb[i].min && value <= world->menu.others_rb[i].max)
			*(world->menu.others_rb[i].value) = value;
		else
		{
			if (value < world->menu.others_rb[i].min)
				*(world->menu.others_rb[i].value) = world->menu.others_rb[i].min;
			if (value > world->menu.others_rb[i].max)
				*(world->menu.others_rb[i].value) = world->menu.others_rb[i].max;
		}
		paint_threaded_fast(world);;
	}
	if (world->menu.active_cp >= 0)
	{
		int i = world->menu.active_cp;
		int x = event.motion.x - world->menu.others_cp[i].pix.x;
		int y = event.motion.y - world->menu.others_cp[i].pix.y;
		if (x < 0)
			x = 0;
		else if (x > 99)
			x = 99;
		if (y < 0)
			y = 0;
		else if (y > 99)
			y = 99;
		*(world->menu.others_cp[i].color) = world->menu.color_map[y * 100 + x];
		world->menu.others_cp[i].pos.x = x;
		world->menu.others_cp[i].pos.y = y;
		paint_threaded_fast(world);;
	}
}

void	ft_sort_menu_filters(t_world *world)
{
	int		changed;
	int		i;
	int		tmp;

	changed = 1;
	while (changed == 1)
	{
		changed = 0;
		i = 1;
		while ((i + 1) < (5 + 1))
		{
			if (world->menu.filters_list[i] > world->menu.filters_list[i + 1])
			{
				tmp = world->menu.filters_list[i];
				world->menu.filters_list[i] = world->menu.filters_list[i + 1];
				world->menu.filters_list[i + 1] = tmp;
				changed = 1;
			}
			i++;
		}
	}
}

void	ft_mouse_button_down_menu(t_world *world, SDL_Event event)
{
	int		i;
	int		x;
	int		y;

	x = event.button.x;
	y = event.button.y;
	if (world->menu.type != MENU_OBJECTS && x >= (HWIN + 30) &&
			x <= (HWIN + 30 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OBJECTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_LIGHTS && x >= (HWIN + 30 + 150) &&
			x <= (HWIN + 30 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_LIGHTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_OTHERS && x >= (HWIN + 30 + 150 + 150) &&
			x <= (HWIN + 30 + 150 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OTHERS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type == MENU_OTHERS)
	{
		if (world->menu.filter_active == 0)
		{
			if (x >= (world->menu.filters.pos.x) && x <= (world->menu.filters.pos.x + world->menu.filters.size.x) &&
					y >= (world->menu.filters.pos.y) && y <= (world->menu.filters.pos.y + world->menu.filters.size.y))
			{
				world->menu.filter_active = 1;
				update_progress_bar(world);
				return ;
			}
		}
		else if (world->menu.filter_active == 1)
		{
			int x0 = world->menu.filters.pos.x;
			int x1 = world->menu.filters.pos.x + world->menu.filters.size.x;
			int tmp = world->menu.filters_list[0];
			int i = 0;
			while (i < (5 + 1))
			{
				int y0 = world->menu.filters.pos.y + i * (world->menu.filters.size.y + 2);
				int y1 = y0 + world->menu.filters.size.y;
				if (x >= x0 && x <= x1 && y >= y0 && y <= y1)
					break ;
				i++;
			}
			if (i == (5 + 1))
			{
				i = 0;
				world->menu.filters_list[0] = world->menu.filters_list[i];
				world->menu.filters_list[i] = tmp;
				ft_sort_menu_filters(world);
				world->menu.filter_active = 0;
				if (i < (5 + 1))
				{
					world->filters[tmp] = 0;
					world->filters[world->menu.filters_list[0]] = 1;
				}
				update_progress_bar(world);
			}
			else
			{
				world->menu.filters_list[0] = world->menu.filters_list[i];
				world->menu.filters_list[i] = tmp;
				ft_sort_menu_filters(world);
				world->menu.filter_active = 0;
				if (i < (5 + 1))
				{
					world->filters[tmp] = 0;
					world->filters[world->menu.filters_list[0]] = 1;
				}
				update_progress_bar(world);
				return ;
			}
		}
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		i = 0;
		while (i < world->menu.nb_others_rb)
		{
			//int x0 = world->menu.others_rb[i].pix.x + ((*(world->menu.others_rb[i].value) * 100) / world->menu.others_rb[i].max);
			int x0 = world->menu.others_rb[i].pix.x + ((world->menu.others_rb[i].min * 100) / world->menu.others_rb[i].max);
			int x1 = world->menu.others_rb[i].pix.x + ((world->menu.others_rb[i].max * 100) / world->menu.others_rb[i].max);
			int y0 = world->menu.others_rb[i].pix.y;
			if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) && y <= (y0 - 3 + 12))
			{
				world->menu.active_rb = i;
				ft_mouse_motion(world, event);
				return ;
			}
			i++;
		}
		i = 0;
		while (i < world->menu.nb_others_cp)
		{
			int x0 = world->menu.others_cp[i].pix.x;
			int y0 = world->menu.others_cp[i].pix.y;
			if (x >= (x0) && x <= (x0 + 100) && y >= (y0) && y <= (y0 + 100))
			{
				world->menu.active_cp = i;
				ft_mouse_motion(world, event);
				return ;
			}
			i++;
		}
		int x0 = HWIN + 20 + 54;
		int y0 = 556;
		if (x >= (x0) && x <= (x0 + world->menu.cartoon.width) && y >= (y0) && y <= (y0 + world->menu.cartoon.height))
		{
			if (world->shader == 2)
				world->shader = 1;
			else
				world->shader = 2;
			paint_threaded_fast(world);;
		}
		x0 = HWIN + 20 + 75;
		y0 = 750;
		if (x >= (x0) && x <= (x0 + world->menu.photo.width) && y >= (y0) && y <= (y0 + world->menu.photo.height))
			ft_export_rt(world, ".ppm");
		x0 = HWIN + 20 + 75 + 250;
		y0 = 752;
		if (x >= (x0) && x <= (x0 + world->menu.save.width) && y >= (y0) && y <= (y0 + world->menu.save.height))
			ft_export_scene(world);
		if (world->exporting_video == 1)
		{
			x0 = HWIN + 20 + 75 + 130;
			y0 = 751;
			if (x >= (x0) && x <= (x0 + world->menu.stop.width) && y >= (y0) && y <= (y0 + world->menu.stop.height))
			{
				world->exporting_video = 0;
				ft_export_y4m(world->video);
				update_progress_bar(world);
			}
		}
		else
		{
			x0 = HWIN + 20 + 75 + 125;
			y0 = 760;
			if (x >= (x0) && x <= (x0 + world->menu.video.width) && y >= (y0) && y <= (y0 + world->menu.video.height))
			{
				world->exporting_video = 1;
				update_progress_bar(world);
			}
		}
	}
}

void	ft_pivot_camera(t_camera *cam, t_point3d tolook)
{
	t_point3d vec_dist;
	double dist;
	double anglep = atan2(cam->o.z - tolook.z, cam->o.x - tolook.x);
	anglep += M_PI / 48.0;
	vec_dist = ft_point3d_cmp(tolook, cam->o);
	dist = sqrt(vec_dist.x * vec_dist.x + vec_dist.z * vec_dist.z);
	cam->o.x = dist * cos(anglep) + tolook.x;
	cam->o.z = dist * sin(anglep) + tolook.z;
	printf("%f\n", dist);
}

void	ft_look_at(t_camera *cam, t_point3d tolook)
{
	t_point3d	vec_look_at;
	cam->look = CAMERA_LOOK;
	vec_look_at = normalize(ft_point3d_cmp(tolook, cam->o));
//	double angle = atan2(ft_point3d_get_norm(
//				ft_point3d_cross_product(ft_new_vec3(0, 0, 1), vec_look_at)),
//			ft_dot_product(ft_new_vec3(0, 0, 1), vec_look_at));
//	printf("angle: %f\n", angle);
//i	printf("on veut regarder par AL\n");
//	ft_print_point3d(vec_look_at);
//	printf("alors qu'on regarde al:\n");
//	ft_print_point3d(cam->look);
//	printf("%f\n", atan2(look.x, look.z));
//	printf("%f\n\n", atan2(vec_look_at.x, vec_look_at.z));

	double angle_x = -atan2(vec_look_at.x, vec_look_at.z);
//	if (angle_x < -M_PI_2)
//	{
//		angle_x += M_PI_2;
////		exit(1);
	//}
//	rotate_hor(cam, angle_x);
//	double angle_y = -atan2(vec_look_at.y, vec_look_at.z);
	double angle_y = vec_look_at.y;
//	if (angle_y < -M_PI_2)
//	{
//		angle_y +=  M_PI_2;
//		exit(1);
//	}
//	printf("angle_x: %f\n", angle_x);
//	printf("\n\n\nangle_y: %f\n\n\n", angle_y);
//	printf("\n\n\n-atan(angle_y): %f\n\n\n", -atan(angle_y));
	cam->rotation.x = angle_x;
(void)angle_y;
//	cam->rotation.y = -atan(angle_y) * 2.0;
//	cam->look = normalize(ft_point3d_cmp(tolook, cam->o));
}

void	ft_left_click_event(t_world *e, SDL_Event event)
{
	t_pixel pix;
	t_hit *hit;
	t_line line;
	t_point3d point;
	t_pixel pixel;

	pixel.x = 1;
	pixel.y = 1;

	hit = NULL;
	pix.x = event.button.x;
	pix.y = event.button.y;
	point = screen2world(pix, e, pixel);
	line = newray(point, newvector(e->cam->o, point));
	if ((hit = trace(line, e->cobjlist)))
	{
		e->selected_cobject = hit->obj.cobject;
		//ft_look_at(e->cam, hit->obj.cobject->o);
	}
}

void	ft_mouse_button_down(t_world *world, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		if (world->focus == 1)
		{
			world->focus = 0;
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_WarpMouseInWindow(world->canvas->window,
					(HRES + MENU_WIDTH) / 2, (VRES + PROGRESS_BAR_HEIGHT) / 2);
		}
		else if (world->focus == 0)
		{
			if (event.button.x <= HRES)
			{
				SDL_SetRelativeMouseMode(SDL_TRUE);
				world->focus = 1;
			}
		}
	}
	else if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (event.button.x > HRES)
			ft_mouse_button_down_menu(world, event);
		else if (world->focus == 0)
			ft_left_click_event(world, event);
	}
}

void	ft_mouse_button_up_menu(t_world *world, SDL_Event event)
{
	(void)event;
	if (world->menu.active_rb >= 0)
		world->menu.active_rb = -1;
	if (world->menu.active_cp >= 0)
		world->menu.active_cp = -1;
}

void	ft_mouse_button_up(t_world *world, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT && event.button.x > HRES)
		ft_mouse_button_up_menu(world, event);
}
