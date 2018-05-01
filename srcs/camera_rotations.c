/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 07:00:47 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 04:10:27 by ldedier          ###   ########.fr       */
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
	printf("camera: \n"
			"---pos: (%f, %f, %f)\n"
			"---rotation: (%f, %f, %f)\n"
			"---up: (%f, %f, %f)\n"
			"---look: (%f, %f, %f)\n"
			"---right: (%f, %f, %f)\n-----------------\n",
			cam->o.x, cam->o.y, cam->o.z,
			cam->rotation.x, cam->rotation.y, cam->rotation.z,
			cam->up.x, cam->up.y, cam->up.z,
			cam->look.x, cam->look.y, cam->look.z,
			cam->right.x, cam->right.y, cam->right.z);
	fflush(stdout);
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
