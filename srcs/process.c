/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:28:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 05:27:37 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void    ft_process(t_world *e)
{
	if (e->keys[up])
		e->cam->rotation.y += e->cam->speed;
	if (e->keys[down])
		e->cam->rotation.y -= e->cam->speed;
	if (e->keys[right])
		e->cam->rotation.x -= e->cam->speed;
	if (e->keys[left])
		e->cam->rotation.x += e->cam->speed;
	if (e->keys[key_w])
		e->cam->o = translate_vec(e->cam->o, e->cam->look, e->cam->speed);
	if (e->keys[key_s])
		e->cam->o = translate_vec(e->cam->o, e->cam->look, -e->cam->speed);
	if (e->keys[key_a])
		e->cam->o = translate_vec(e->cam->o, e->cam->right, -e->cam->speed);
	if (e->keys[key_d])
		e->cam->o = translate_vec(e->cam->o, e->cam->right, e->cam->speed);
	if (e->keys[key_ctrl])
		e->cam->o = translate_vec(e->cam->o, e->cam->up, -e->cam->speed);
	if (e->keys[key_space])
		e->cam->o = translate_vec(e->cam->o, e->cam->up, e->cam->speed);

	if (e->selected_cobject && e->selected_cobject->id == e->menu.active_object)
	{
		if (e->keys[key_o])
		{
			e->selected_cobject->s.x += e->cam->speed;
			e->selected_cobject->s.y += e->cam->speed;
			e->selected_cobject->s.z += e->cam->speed;
			e->selected_cobject->objlist->object->object_union.plane.texture_trans_x -= 100;
		}
		if (e->keys[key_p])
		{
			if (e->selected_cobject->s.x - e->cam->speed > 1.f && 
					e->selected_cobject->s.y - e->cam->speed > 1.f &&
					e->selected_cobject->s.z - e->cam->speed > 1.f)
			{
				e->selected_cobject->s.x -= e->cam->speed;
				e->selected_cobject->s.y -= e->cam->speed;
				e->selected_cobject->s.z -= e->cam->speed;
				e->selected_cobject->objlist->object->object_union.plane.texture_trans_x += 100;
			}
		}
		if (e->keys[key_n])
		{
			printf("%f\n", e->selected_cobject->objlist->object->object_union.plane.texture_stretch_x);
			e->selected_cobject->objlist->object->object_union.plane.texture_stretch_x += 0.1;
		}
		if (e->keys[key_m])
			e->selected_cobject->objlist->object->object_union.plane.texture_stretch_x -= 0.1;

		if (e->keys[key_k])
			e->selected_cobject->objlist->object->object_union.plane.texture_trans_y += 100;
		if (e->keys[key_l])
			e->selected_cobject->objlist->object->object_union.plane.texture_trans_y -= 100;

		if (e->keys[key_7])
			e->selected_cobject->o.y += e->cam->speed;
		if (e->keys[key_8])
			e->selected_cobject->o.y -= e->cam->speed;

		if (e->keys[key_4])
			e->selected_cobject->o.x += e->cam->speed;
		if (e->keys[key_5])
			e->selected_cobject->o.x -= e->cam->speed;

		if (e->keys[key_1])
			e->selected_cobject->o.z += e->cam->speed;
		if (e->keys[key_2])
			e->selected_cobject->o.z -= e->cam->speed;

		if (e->keys[key_e])
		{
			double angle = fmod(e->selected_cobject->r.x + M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_cobject->r.x = angle;
		}
		if (e->keys[key_q])
		{
			double angle = fmod(e->selected_cobject->r.x - M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_cobject->r.x = angle;
		}
		if (e->keys[key_c])
		{
			double angle = fmod(e->selected_cobject->r.y + M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_cobject->r.y = angle;
		}
		if (e->keys[key_z])
		{
			double angle = fmod(e->selected_cobject->r.y - M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_cobject->r.y = angle;
		}
		if (e->keys[key_x])
		{
			double angle = fmod(e->selected_cobject->r.z + M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_cobject->r.z = angle;
		}
		if (e->keys[key_v])
		{
			double angle = fmod(e->selected_cobject->r.z - M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_cobject->r.z = angle;
		}
		if (e->animate)
		{
			ft_pivot_camera(e->cam, e->selected_cobject->o);
			ft_look_at(e->cam, e->selected_cobject->o);
		}
	}
	else if (e->selected_object && e->selected_object->id == e->menu.active_object)
	{
		if (e->keys[key_o])
		{
			e->selected_object->s.x += e->cam->speed;
			e->selected_object->s.y += e->cam->speed;
			e->selected_object->s.z += e->cam->speed;
			e->selected_object->object_union.plane.texture_trans_x -= 100;
		}
		if (e->keys[key_p])
		{
			if (e->selected_object->s.x - e->cam->speed > 1.f && 
					e->selected_object->s.y - e->cam->speed > 1.f &&
					e->selected_object->s.z - e->cam->speed > 1.f)
			{
				e->selected_object->s.x -= e->cam->speed;
				e->selected_object->s.y -= e->cam->speed;
				e->selected_object->s.z -= e->cam->speed;
				e->selected_object->object_union.plane.texture_trans_x += 100;
			}
		}
		if (e->keys[key_n])
		{
			printf("%f\n", e->selected_object->object_union.plane.texture_stretch_x);
			e->selected_object->object_union.plane.texture_stretch_x += 0.1;
		}
		if (e->keys[key_m])
			e->selected_object->object_union.plane.texture_stretch_x -= 0.1;

		if (e->keys[key_k])
			e->selected_object->object_union.plane.texture_trans_y += 100;
		if (e->keys[key_l])
			e->selected_object->object_union.plane.texture_trans_y -= 100;

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

		if (e->keys[key_e])
		{
			double angle = fmod(e->selected_object->r.x + M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_object->r.x = angle;
		}
		if (e->keys[key_q])
		{
			double angle = fmod(e->selected_object->r.x - M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_object->r.x = angle;
		}
		if (e->keys[key_c])
		{
			double angle = fmod(e->selected_object->r.y + M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_object->r.y = angle;
		}
		if (e->keys[key_z])
		{
			double angle = fmod(e->selected_object->r.y - M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_object->r.y = angle;
		}
		if (e->keys[key_x])
		{
			double angle = fmod(e->selected_object->r.z + M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_object->r.z = angle;
		}
		if (e->keys[key_v])
		{
			double angle = fmod(e->selected_object->r.z - M_PI / 16, 2 * M_PI);
			if (angle < 0.0f)
				angle += 2 * M_PI;
			e->selected_object->r.z = angle;
		}
		if (e->animate)
		{
			ft_pivot_camera(e->cam, e->selected_object->o);
			ft_look_at(e->cam, e->selected_object->o);
		}
	}
	apply_rotation(e->cam);
	ft_compute_matrices_clist(e->cobjlist);
}
