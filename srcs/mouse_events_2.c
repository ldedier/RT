/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:37:56 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 10:19:30 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	cam->look = (t_point3d){.x = 0, .y = 0, .z = 1};
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
		if (e->keys[key_shift] == 1)
		{
			e->selected_object = &(hit->obj);
			e->menu.active_object = e->selected_object->id;
		}
		else
		{
			e->selected_cobject = hit->obj.cobject;
			e->menu.active_object = e->selected_cobject->id;
		}
		ft_set_selected_object(e, e->menu.active_object);
		if (e->selected_cobject->id == e->menu.active_object)
			ft_mouse_button_objects_6(e);
		else
			ft_mouse_button_objects_7(e);
		update_progress_bar(e);

		//ft_look_at(e->cam, hit->obj.cobject->o);
	}
}
