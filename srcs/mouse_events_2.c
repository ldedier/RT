/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:37:56 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 06:04:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_pivot_camera(t_camera *cam, t_point3d tolook)
{
	t_point3d	vec_dist;
	double		dist;
	double		anglep;

	anglep = atan2(cam->o.z - tolook.z, cam->o.x - tolook.x);
	anglep += M_PI / 48.0;
	vec_dist = ft_point3d_cmp(tolook, cam->o);
	dist = sqrt(vec_dist.x * vec_dist.x + vec_dist.z * vec_dist.z);
	cam->o.x = dist * cos(anglep) + tolook.x;
	cam->o.z = dist * sin(anglep) + tolook.z;
}

void	ft_look_at(t_camera *cam, t_point3d tolook)
{
	t_point3d	vec_look_at;
	double		angle_x;

	cam->look = CAMERA_LOOK;
	vec_look_at = normalize(ft_point3d_cmp(tolook, cam->o));
	angle_x = -atan2(vec_look_at.x, vec_look_at.z);
	cam->rotation.x = angle_x;
}

void	ft_process_hit_left_click(t_world *e, t_hit *hit)
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
}

void	ft_left_click_event(t_world *e, SDL_Event event)
{
	t_pixel		pix;
	t_hit		*hit;
	t_line		line;
	t_point3d	point;
	t_pixel		pixel;

	pixel.x = 1;
	pixel.y = 1;
	hit = NULL;
	pix.x = event.button.x;
	pix.y = event.button.y - e->canvas->screen.y;
	render_pixel(e, pix, 0);
	point = screen2world(pix, e, pixel);
	line = newray(point, newvector(e->cam->o, point));
	if ((hit = trace(line, e->cobjlist)))
		ft_process_hit_left_click(e, hit);
}
