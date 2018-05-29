/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewplane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 04:10:48 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/20 08:21:52 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	screen2world(t_pixel pix, t_world *world)
{
	t_camera	*cam;
	t_point3d	p;
	t_point3d	scale;

	cam = world->cam;
	scale.x = -world->canvas->halved_win_size.x * cam->pd + cam->pd * pix.x + cam->pd / 2;;
	scale.y = world->canvas->halved_win_size.y * cam->pd - cam->pd * pix.y + cam->pd / 2;
	scale.z = cam->fd;
	p = translate_vec(
			translate_vec(
				translate_vec(cam->o, cam->look, scale.z),
				cam->right, scale.x),
			cam->up, scale.y);
	return (p);
}
