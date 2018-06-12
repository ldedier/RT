/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 03:28:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 06:04:32 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_process_camera(t_world *e)
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
}

void		ft_process(t_world *e)
{
	ft_process_camera(e);
	if (e->selected_cobject && e->selected_cobject->id == e->menu.active_object)
		ft_process_cobject(e);
	else if (e->selected_object &&
			e->selected_object->id == e->menu.active_object)
		ft_process_object(e);
	apply_rotation(e->cam);
	ft_compute_matrices_clist(e->cobjlist);
}
