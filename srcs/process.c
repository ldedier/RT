/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:28:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/14 17:36:44 by ldedier          ###   ########.fr       */
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

	if (e->keys[key_o])
	{
		e->selected_cobject->s.x += e->cam->speed;
		e->selected_cobject->s.y += e->cam->speed;
		e->selected_cobject->s.z += e->cam->speed;
	}
	if (e->keys[key_p])
	{
		e->selected_cobject->s.x -= e->cam->speed;
		e->selected_cobject->s.y -= e->cam->speed;
		e->selected_cobject->s.z -= e->cam->speed;
	}

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
		e->selected_cobject->r.x += M_PI / 16;
	if (e->keys[key_q])
		e->selected_cobject->r.x -= M_PI / 16;
	
	ft_compute_matrices_clist(e->cobjlist);
}
