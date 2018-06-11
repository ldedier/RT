/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewplane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 04:10:48 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 07:56:07 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	screen2world(t_pixel pix, t_world *world, t_pixel aa)
{
	t_camera	*cam;
	t_point3d	p;
	t_point3d	scale;
	double		aa_offset;
	double		offset;

	cam = world->cam;
	aa_offset = cam->pd / world->aa_sq_size;
	offset = aa_offset * aa.x + aa_offset / 2;
	scale.x = -world->canvas->halved_win_size.x *
		cam->pd + cam->pd * pix.x + offset;
	offset = aa_offset * aa.y;
	scale.y = world->canvas->halved_win_size.y *
		cam->pd - cam->pd * pix.y + offset;
	scale.z = cam->fd;
	p = translate_vec(
			translate_vec(
				translate_vec(cam->o, cam->look, scale.z),
				cam->right, scale.x),
			cam->up, scale.y);
	return (p);
}
