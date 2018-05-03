/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:28:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/03 15:41:49 by lcavalle         ###   ########.fr       */
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
	apply_rotation(e->cam);
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

/*
	if (e->keys[key_1)
		e->selected_object->o.z += e->cam->speed;
	if (e->keys[key_2)
		e->selected_object->o.z -= e->cam->speed;
	if (e->keys[key_o)
	{
		e->selected_object->scale.x += e->cam->speed;
		e->selected_object->scale.y += e->cam->speed;
		e->selected_object->scale.z += e->cam->speed;
	}
	if (e->keys[key_p)
	{
		e->selected_object->scale.x -= e->cam->speed;
		e->selected_object->scale.y -= e->cam->speed;
		e->selected_object->scale.z -= e->cam->speed;
	}
*/
	if (e->keys[key_7])
		e->cam->rotation.z += M_PI / 16;
	if (e->keys[key_8])
		e->cam->rotation.z -= M_PI / 16;

	if (e->keys[key_4])
		e->cam->rotation.x += M_PI / 16;
	if (e->keys[key_5])
		e->cam->rotation.x -= M_PI / 16;
/*	
	if (e->keys[key_e)
		e->selected_object->rotation.x += M_PI / 16;
	if (e->keys[key_q)
		e->selected_object->rotation.x -= M_PI / 16;
*/
}
