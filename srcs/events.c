/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:25:54 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/04 09:15:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_keys_event(t_world *e, SDL_Event event, int press)
{
	if (e->focus || !e->focus)
	{
		if (event.key.keysym.sym == SDLK_UP)
			e->keys[up] = press;
		else if (event.key.keysym.sym == SDLK_DOWN)
			e->keys[down] = press;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			e->keys[right] = press;
		else if (event.key.keysym.sym == SDLK_LEFT)
			e->keys[left] = press;
		else if (event.key.keysym.sym == SDLK_KP_8)
			e->keys[key_8] = press;
		else if (event.key.keysym.sym == SDLK_KP_7)
			e->keys[key_7] = press;
		else if (event.key.keysym.sym == SDLK_KP_5)
			e->keys[key_5] = press;
		else if (event.key.keysym.sym == SDLK_KP_4)
			e->keys[key_4] = press;
		else if (event.key.keysym.sym == SDLK_KP_2)
			e->keys[key_2] = press;
		else if (event.key.keysym.sym == SDLK_KP_1)
			e->keys[key_1] = press;
		else if (event.key.keysym.sym == SDLK_w)
			e->keys[key_w] = press;
		else if (event.key.keysym.sym == SDLK_a)
			e->keys[key_a] = press;
		else if (event.key.keysym.sym == SDLK_s)
			e->keys[key_s] = press;
		else if (event.key.keysym.sym == SDLK_d)
			e->keys[key_d] = press;
		else if (event.key.keysym.sym == SDLK_q)
			e->keys[key_q] = press;
		else if (event.key.keysym.sym == SDLK_e)
			e->keys[key_e] = press;
		else if (event.key.keysym.sym == SDLK_z)
			e->keys[key_z] = press;
		else if (event.key.keysym.sym == SDLK_c)
			e->keys[key_c] = press;
		else if (event.key.keysym.sym == SDLK_x)
			e->keys[key_x] = press;
		else if (event.key.keysym.sym == SDLK_v)
			e->keys[key_v] = press;
		else if (event.key.keysym.sym == SDLK_o)
			e->keys[key_o] = press;
		else if (event.key.keysym.sym == SDLK_p)
			e->keys[key_p] = press;
		else if (event.key.keysym.sym == SDLK_f && press == 1)
			e->animate = !e->animate;
		else if (event.key.keysym.sym == SDLK_LCTRL)
			e->keys[key_ctrl] = press;
		else if (event.key.keysym.sym == SDLK_SPACE)
			e->keys[key_space] = press;
		else if (event.key.keysym.sym == SDLK_RETURN && e->progress == 0)
			e->keys[key_enter] = press;
		else if (event.key.keysym.sym == SDLK_LSHIFT)
		{
			if (press == 1)
				e->cam->speed = 1;
			else
				e->cam->speed = 0.2;
		}
		else if (event.key.keysym.sym == SDLK_r)
		{
			if (press == 1)
			{
				if (e->can_export)
				{
					ft_export_rt(e, ".ppm");
					e->can_export = 0;
				}
			}
			else
				e->can_export = 1;
		}
		else if (event.key.keysym.sym == SDLK_h)
		{
			if (press == 1 && e->can_export)
			{
				if (e->exporting_video)
				{
					ft_export_y4m(e->video);
					e->exporting_video = 0;
				}
				else
					e->exporting_video = 1;
			}
			else
				e->can_export = 1;
		}
	}
}

void	ft_mouse_motion(t_world *e, SDL_Event event)
{
	if (e->focus)
	{
		e->cam->rotation.x = e->cam->rotation.x - (event.motion.xrel) * M_PI / 1024.0;
		e->cam->rotation.y = ft_fclamp(-M_PI / 2, e->cam->rotation.y - (event.motion.yrel) * M_PI / 1024.0, M_PI / 2);
		apply_rotation(e->cam);
		e->keys[mouse_move] = 1;
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

void	ft_right_click_event(t_world *e, SDL_Event event)
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

void	ft_mouse_down(t_world *e, SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (!e->focus)
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
			e->focus = 1;
		}
		else
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			e->focus = 0;
		}
	}
	else if (event.button.button == SDL_BUTTON_RIGHT && !e->focus)
	{
		ft_right_click_event(e, event);
	}
}
