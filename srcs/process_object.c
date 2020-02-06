/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 06:02:14 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 06:41:34 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		process_scale(t_world *e)
{
	if (e->keys[key_o])
	{
	//	e->selected_object->s.x += e->cam->speed;
	//	e->selected_object->s.y += e->cam->speed;
	//	e->selected_object->s.z += e->cam->speed;
//	printf("%f\n", e->cam->speed);
		if (e->cam->speed == 0.2)
			e->selected_object->object_union.plane.texture_trans_x -= 10;
		else
			e->selected_object->object_union.plane.texture_trans_x += 10;

	}
	if (e->keys[key_p])
	{
		//if (e->selected_object->s.x - e->cam->speed > 1.f &&
		//		e->selected_object->s.y - e->cam->speed > 1.f &&
	//			e->selected_object->s.z - e->cam->speed > 1.f)
	//	{
	//		e->selected_object->s.x -= e->cam->speed;
	//		e->selected_object->s.y -= e->cam->speed;
	//		e->selected_object->s.z -= e->cam->speed; // TO REMOVE

		if (e->cam->speed == 0.2)
			e->selected_object->object_union.plane.texture_trans_y -= 10;
		else
			e->selected_object->object_union.plane.texture_trans_y += 10;

	//	}
	}
	if (e->keys[key_n])
		e->selected_object->object_union.plane.texture_stretch_x += 0.1;
	if (e->keys[key_m])
		e->selected_object->object_union.plane.texture_stretch_x -= 0.1;
}

static void		process_position(t_world *e)
{
	if (e->keys[key_7])
		e->selected_object->o.y += e->cam->speed;
	if (e->keys[key_8])
		e->selected_object->o.y -= e->cam->speed;
	if (e->keys[key_4])
		e->selected_object->o.x += e->cam->speed;
	if (e->keys[key_5])
		e->selected_object->o.x -= e->cam->speed;
	if (e->keys[key_1])
		e->selected_object->o.z += e->cam->speed;
	if (e->keys[key_2])
		e->selected_object->o.z -= e->cam->speed;
}

static double	rot_angle(double val_axis, int mul)
{
	double	angle;

	angle = fmod(val_axis + M_PI / 16 * mul, 2 * M_PI);
	if (angle < 0.0f)
		angle += 2 * M_PI;
	return (angle);
}

static void		process_rotation(t_world *e)
{
	if (e->keys[key_e])
		e->selected_object->r.x = rot_angle(e->selected_object->r.x, 1);
	if (e->keys[key_q])
		e->selected_object->r.x = rot_angle(e->selected_object->r.x, -1);
	if (e->keys[key_c])
		e->selected_object->r.y = rot_angle(e->selected_object->r.y, 1);
	if (e->keys[key_z])
		e->selected_object->r.y = rot_angle(e->selected_object->r.y, -1);
	if (e->keys[key_x])
		e->selected_object->r.z = rot_angle(e->selected_object->r.z, 1);
	if (e->keys[key_v])
		e->selected_object->r.z = rot_angle(e->selected_object->r.z, -1);
}

void			ft_process_object(t_world *e)
{
	process_scale(e);
	process_position(e);
	process_rotation(e);
	if (e->keys[key_k])
		e->selected_object->object_union.plane.texture_trans_y += 100;
	if (e->keys[key_l])
		e->selected_object->object_union.plane.texture_trans_y -= 100;
	if (e->animate)
	{
		ft_pivot_camera(e->cam, e->selected_object->o);
		ft_look_at(e->cam, e->selected_object->o);
	}
}
