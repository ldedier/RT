/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 07:00:47 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/10 01:02:50 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		apply_rotation(t_camera *cam)
{
	camera_reset(cam);
	cam->rotation.y = cam->rotation.y > M_PI_2 ? M_PI_2 : cam->rotation.y;
	cam->rotation.y = cam->rotation.y < -M_PI_2 ? -M_PI_2 : cam->rotation.y;
	rotate_hor(cam, cam->rotation.x);
	rotate_ver(cam, cam->rotation.y);
}

void		rotate_hor(t_camera *cam, double angle)
{
	cam->look = normalize(rotate_axis(cam->look, cam->up, angle));
	cam->right = normalize(crossprod(cam->look, cam->up));
}

void		rotate_ver(t_camera *cam, double angle)
{
	cam->look = normalize(rotate_axis(cam->look, cam->right, angle));
	cam->up = normalize(crossprod(cam->right, cam->look));
}

void		camera_reset(t_camera *cam)
{
	cam->up = CAMERA_UP;
	cam->look = CAMERA_LOOK;
	cam->right = normalize(crossprod(cam->look, cam->up));
}
