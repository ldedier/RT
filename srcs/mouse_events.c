/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:28:01 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/08 07:26:57 by aherriau         ###   ########.fr       */
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
		if (world->menu.type == MENU_LIGHTS)
		{
			float value = ((float)(event.motion.x - (world->menu.lights_rb[i].pix.x + 4)) / 100) * world->menu.lights_rb[i].max;
			if (i <= 1)
			{
				if (value >= world->menu.lights_rb[i].min && value <= world->menu.lights_rb[i].max)
					*(world->menu.lights_rb[i].value) = value;
				else
				{
					if (value < world->menu.lights_rb[i].min)
						*(world->menu.lights_rb[i].value) = world->menu.lights_rb[i].min;
					if (value > world->menu.others_rb[i].max)
						*(world->menu.lights_rb[i].value) = world->menu.lights_rb[i].max;
				}
			}
			else
			{
				if (value >= world->menu.lights_rb[i].min && value <= world->menu.lights_rb[i].max)
					*(world->menu.lights_rb[i].value) = value - 1;
				else
				{
					if (value < world->menu.lights_rb[i].min)
						*(world->menu.lights_rb[i].value) = world->menu.lights_rb[i].min - 1;
					if (value > world->menu.others_rb[i].max)
						*(world->menu.lights_rb[i].value) = world->menu.lights_rb[i].max - 1;
				}
			}
		}
		else if (world->menu.type == MENU_OTHERS)
		{
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
		}
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
	}
	if (world->menu.active_grb >= 0)
	{
		int i = world->menu.active_grb;
		int nb_val = world->menu.others_grb[i].max - world->menu.others_grb[i].min + 1;
		float step = 108 / (float)(nb_val - 1);
		int value = ft_clamp(0, event.motion.x - (world->menu.others_grb[i].pix.x + 4), 100);
		int j = 0;
		while (((j * step) - (step / 2)) <= value)
			j++;
		if (world->menu.others_grb[i].min == 0 && value < 100)
			j--;
		value = j;
		if (value >= world->menu.others_grb[i].min && value <= world->menu.others_grb[i].max)
			*(world->menu.others_grb[i].value) = (int)value;
		else
		{
			if (value < world->menu.others_grb[i].min)
				*(world->menu.others_grb[i].value) = world->menu.others_grb[i].min;
			if (value > world->menu.others_grb[i].max)
				*(world->menu.others_grb[i].value) = world->menu.others_grb[i].max;
		}
		world->cancel_render = 1;
		join_threads(world);
		paint_threaded_fast(world);
		update_progress_bar(world);
	}
	if (world->menu.active_cp >= 0)
	{
		int i = world->menu.active_cp;
		if (world->menu.type == MENU_LIGHTS)
		{
			int x = event.motion.x - world->menu.lights_cp[i].pix.x;
			int y = event.motion.y - world->menu.lights_cp[i].pix.y;
			if (x < 0)
				x = 0;
			else if (x > 99)
				x = 99;
			if (y < 0)
				y = 0;
			else if (y > 99)
				y = 99;
			*(world->menu.lights_cp[i].color) = world->menu.color_map[y * 100 + x];
			world->menu.lights_cp[i].pos.x = x;
			world->menu.lights_cp[i].pos.y = y;
		}
		else if (world->menu.type == MENU_OTHERS)
		{
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
		}
		paint_threaded_fast(world);
	}
	if (world->menu.scroll_objects.active == 1)
	{
		int new_pos = event.motion.y - 140 - world->menu.scroll_objects.step;
		if (new_pos < 0)
			new_pos = 0;
		else if ((new_pos + world->menu.scroll_objects.height) > (world->menu.scroll_objects.len - 10))
			new_pos = world->menu.scroll_objects.len - 10 - world->menu.scroll_objects.height;
		world->menu.scroll_objects.pos = new_pos;
		update_progress_bar(world);
	}
	if (world->menu.scroll_lights.active == 1)
	{
		int new_pos = event.motion.y - 140 - world->menu.scroll_lights.step;
		if (new_pos < 0)
			new_pos = 0;
		else if ((new_pos + world->menu.scroll_lights.height) > (world->menu.scroll_lights.len - 10))
			new_pos = world->menu.scroll_lights.len - 10 - world->menu.scroll_lights.height;
		world->menu.scroll_lights.pos = new_pos;
		update_progress_bar(world);
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
		while ((i + 1) < (e_nfilters + 1))
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
	if (world->menu.type != MENU_OBJECTS && x >= (world->canvas->win.w + 30) &&
			x <= (world->canvas->win.w + 30 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OBJECTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_LIGHTS && x >= (world->canvas->win.w + 30 + 150) &&
			x <= (world->canvas->win.w + 30 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_LIGHTS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type != MENU_OTHERS && x >= (world->canvas->win.w + 30 + 150 + 150) &&
			x <= (world->canvas->win.w + 30 + 150 + 150 + 140) && y >= 30 && y <= 70)
	{
		world->menu.type = MENU_OTHERS;
		if (world->menu.filter_active == 1)
			world->menu.filter_active = 0;
		update_progress_bar(world);
	}
	else if (world->menu.type == MENU_OBJECTS)
	{
		int x0 = world->canvas->win.w + 443;
		int y0 = 140 + world->menu.scroll_objects.pos;
		if (x >= (x0) && x<= (x0 + 10) && y >= (y0) && y <= (y0 + world->menu.scroll_objects.height))
		{
			world->menu.scroll_objects.active = 1;
			world->menu.scroll_objects.step = y - 135 - world->menu.scroll_objects.pos;
		}
		else if (x >= (x0) && x<= (x0 + 10) && y >= (140) && y <= (140 + world->menu.scroll_objects.len - 10))
		{
			world->menu.scroll_objects.active = 1;
			world->menu.scroll_objects.step = world->menu.scroll_objects.height / 2;
			ft_mouse_motion(world, event);
		}
	}
	else if (world->menu.type == MENU_LIGHTS)
	{
		int x0 = world->canvas->win.w + 443;
		int y0 = 140 + world->menu.scroll_lights.pos;
		if (x >= (x0) && x<= (x0 + 10) && y >= (y0) && y <= (y0 + world->menu.scroll_lights.height))
		{
			world->menu.scroll_lights.active = 1;
			world->menu.scroll_lights.step = y - 135 - world->menu.scroll_lights.pos;
		}
		else if (x >= (x0) && x<= (x0 + 10) && y >= (140) && y <= (140 + world->menu.scroll_lights.len - 10))
		{
			world->menu.scroll_lights.active = 1;
			world->menu.scroll_lights.step = world->menu.scroll_lights.height / 2;
			ft_mouse_motion(world, event);
		}
		int i = 0;
		x0 = world->canvas->win.w + 55;
		y0 = world->menu.first_light.y;
		while (i < world->menu.nb_lights)
		{
			int y1 = y0 + i * (50 + 15);
			if (x >= (x0) && x<= (x0 + 360) && y >= (y1) && y <= (y1 + 50))
			{
				world->menu.active_light = world->menu.lights[i];
				world->menu.lights_rb[0].value = &(world->lights[world->menu.active_light].angle);
				world->menu.lights_rb[1].value = &(world->lights[world->menu.active_light].intensity);
				world->menu.lights_rb[2].value = &(world->lights[world->menu.active_light].v.x);
				world->menu.lights_rb[3].value = &(world->lights[world->menu.active_light].v.y);
				world->menu.lights_rb[4].value = &(world->lights[world->menu.active_light].v.z);
				world->menu.lights_cp[0].color = &(world->lights[world->menu.active_light].c);
				world->menu.lights_cp[0].pos = ft_color_pos(world, world->lights[world->menu.active_light].c);
				update_progress_bar(world);
				break ;
			}
			i++;
		}
		i = 0;
		while (i < world->menu.nb_lights_rb)
		{
			int x0 = world->menu.lights_rb[i].pix.x + ((world->menu.lights_rb[i].min * 100) / world->menu.lights_rb[i].max);
			int x1 = world->menu.lights_rb[i].pix.x + ((world->menu.lights_rb[i].max * 100) / world->menu.lights_rb[i].max);
			int y0 = world->menu.lights_rb[i].pix.y;
			if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) && y <= (y0 - 3 + 12))
			{
				world->menu.active_rb = i;
				ft_mouse_motion(world, event);
				return ;
			}
			i++;
		}
		i = 0;
		while (i < world->menu.nb_lights_cp)
		{
			int x0 = world->menu.lights_cp[i].pix.x;
			int y0 = world->menu.lights_cp[i].pix.y;
			if (x >= (x0) && x <= (x0 + 100) && y >= (y0) && y <= (y0 + 100))
			{
				world->menu.active_cp = i;
				ft_mouse_motion(world, event);
				return ;
			}
			i++;
		}
		y0 = 765;
		x0 = world->canvas->win.w + 105;
		if (x >= (x0) && x <= (x0 + 60) && y >= (y0) && y <= (y0 + 60))
		{
			world->lights[world->menu.active_light].type = 'p';
			world->cancel_render = 1;
			join_threads(world);
			paint_threaded_fast(world);
			update_progress_bar(world);
		}
		x0 = world->canvas->win.w + 105 + 115;
		if (x >= (x0) && x <= (x0 + 60) && y >= (y0) && y <= (y0 + 60))
		{
			world->lights[world->menu.active_light].type = 's';
			world->cancel_render = 1;
			join_threads(world);
			paint_threaded_fast(world);
			update_progress_bar(world);
		}
		x0 = world->canvas->win.w + 105 + 230;
		if (x >= (x0) && x <= (x0 + 60) && y >= (y0) && y <= (y0 + 60))
		{
			world->lights[world->menu.active_light].type = 'd';
			world->cancel_render = 1;
			join_threads(world);
			paint_threaded_fast(world);
			update_progress_bar(world);
		}
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
			while (i < (e_nfilters + 1))
			{
				int y0 = world->menu.filters.pos.y + i * (world->menu.filters.size.y + 2);
				int y1 = y0 + world->menu.filters.size.y;
				if (x >= x0 && x <= x1 && y >= y0 && y <= y1)
					break ;
				i++;
			}
			if (i == (e_nfilters + 1))
			{
				world->menu.filter_active = 0;
				update_progress_bar(world);
			}
			else
			{
				world->menu.filters_list[0] = world->menu.filters_list[i];
				world->menu.filters_list[i] = tmp;
				ft_sort_menu_filters(world);
				world->menu.filter_active = 0;
				world->filters[tmp] = 0;
				world->filters[world->menu.filters_list[0]] = 1;
				if (i > 0)
				{
					world->cancel_render = 1;
					join_threads(world);
					paint_threaded_fast(world);
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
		while (i < world->menu.nb_others_grb)
		{
			int x0 = world->menu.others_grb[i].pix.x;
			int x1 = x0 + 108;
			int y0 = world->menu.others_grb[i].pix.y;
			if (x >= (x0) && x <= (x1 + 8) && y >= (y0 - 3) && y <= (y0 - 3 + 12))
			{
				world->menu.active_grb = i;
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
		int x0 = world->canvas->win.w + 20 + 55;
		int y0 = 565;
		if (x >= (x0) && x <= (x0 + world->menu.cartoon.width) && y >= (y0) && y <= (y0 + world->menu.cartoon.height))
		{
			if (world->shader == 2)
				world->shader = 1;
			else
				world->shader = 2;
			world->cancel_render = 1;
			join_threads(world);
			paint_threaded_fast(world);
			update_progress_bar(world);
		}
		x0 = world->canvas->win.w + 20 + 75;
		y0 = 750;
		if (x >= (x0) && x <= (x0 + world->menu.photo.width) && y >= (y0) && y <= (y0 + world->menu.photo.height))
			ft_export_rt(world, ".ppm");
		x0 = world->canvas->win.w + 20 + 75 + 250;
		y0 = 752;
		if (x >= (x0) && x <= (x0 + world->menu.save.width) && y >= (y0) && y <= (y0 + world->menu.save.height))
			ft_export_scene(world);
		if (world->exporting_video == 1)
		{
			x0 = world->canvas->win.w + 20 + 75 + 130;
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
			x0 = world->canvas->win.w + 20 + 75 + 125;
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
	pix.y = event.button.y - e->canvas->screen.y;
	printf("DEBUG PIXEL\n");//DELETE
	render_pixel(e, pix, 0);
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
					(world->canvas->win_size.x + MENU_WIDTH) / 2, world->canvas->win.h / 2);
		}
		else if (world->focus == 0)
		{
			if (event.button.x <= world->canvas->win_size.x)
			{
				SDL_SetRelativeMouseMode(SDL_TRUE);
				world->focus = 1;
			}
		}
	}
	else if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (event.button.x > world->canvas->win_size.x)
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
	if (world->menu.active_grb >= 0)
		world->menu.active_grb = -1;
	if (world->menu.active_cp >= 0)
		world->menu.active_cp = -1;
	if (world->menu.scroll_objects.active == 1)
		world->menu.scroll_objects.active = 0;
	if (world->menu.scroll_lights.active == 1)
		world->menu.scroll_lights.active = 0;
}

void	ft_mouse_button_up(t_world *world, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT && event.button.x > world->canvas->win_size.x)
		ft_mouse_button_up_menu(world, event);
}
