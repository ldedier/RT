/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_look_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 22:17:00 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/15 17:31:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_mat4	ft_mat4_view(t_vec3 x_axis, t_vec3 y_axis, t_vec3 z_axis, t_vec3 cam_pos)
{
	t_mat4 res;

	res.as_mat[0] = x_axis.x;
	res.as_mat[1] = x_axis.y;
	res.as_mat[2] = x_axis.z;
	res.as_mat[3] = -ft_dot_product(x_axis, cam_pos);

	res.as_mat[4] = y_axis.x;
	res.as_mat[5] = y_axis.y;
	res.as_mat[6] = y_axis.z;
	res.as_mat[7] = -ft_dot_product(y_axis, cam_pos);

	res.as_mat[8] = z_axis.x;
	res.as_mat[9] = z_axis.y;
	res.as_mat[10] = z_axis.z;
	res.as_mat[11] = -ft_dot_product(z_axis, cam_pos);

	res.as_mat[12] = 0;
	res.as_mat[13] = 0;
	res.as_mat[14] = 0;
	res.as_mat[15] = 1;

	return (res);
}

t_mat4	ft_mat4_orientation(t_vec3 x_axis, t_vec3 y_axis, t_vec3 z_axis)
{
	t_mat4 res;

	res.as_mat[0] = x_axis.x;
	res.as_mat[1] = x_axis.y;
	res.as_mat[2] = x_axis.z;
	res.as_mat[3] = 0;

	res.as_mat[4] = y_axis.x;
	res.as_mat[5] = y_axis.y;
	res.as_mat[6] = y_axis.z;
	res.as_mat[7] = 0;

	res.as_mat[8] = z_axis.x;
	res.as_mat[9] = z_axis.y;
	res.as_mat[10] = z_axis.z;
	res.as_mat[11] = 0;

	res.as_mat[12] = 0;
	res.as_mat[13] = 0;
	res.as_mat[14] = 0;
	res.as_mat[15] = 1;

	return (res);
}





t_mat4	ft_mat4_look_at(t_vec3 cam_pos, t_vec3 target_pos, t_vec3 up_axis)
{

	t_vec3	forward;
	t_vec3	left;
	t_vec3	up;
	t_mat4	res;

	forward = ft_vec3_cmp(cam_pos, target_pos);

	ft_vec3_normalize(&forward);


	left = ft_vec3_cross_product(up_axis, forward);
	ft_vec3_normalize(&left);

	up = ft_vec3_cross_product(forward, left);

	res = ft_mat4_eye();
	res.as_mat[0] = left.x;
	res.as_mat[4] = left.y;
	res.as_mat[8] = left.z;
	res.as_mat[1] = up.x;
	res.as_mat[5] = up.y;
	res.as_mat[9] = up.z;
	res.as_mat[2] = forward.x;
	res.as_mat[6] = forward.y;
	res.as_mat[10] = forward.z;
	/*	
		res.as_mat[12] =  -left.x * cam_pos.x - left.y * cam_pos.y - left.z * cam_pos.z;
		res.as_mat[13] = -up.x * cam_pos.x - up.y * cam_pos.y - up.z * cam_pos.z;
		res.as_mat[14] = -forward.x * cam_pos.x - forward.y * cam_pos.y - forward.z * cam_pos.z;
		*/
	res.as_mat[12] =  -ft_dot_product(left, cam_pos);
	res.as_mat[13] =  -ft_dot_product(up, cam_pos);
	res.as_mat[14] =  -ft_dot_product(forward, cam_pos);

	return (res);
}


t_mat4	ft_mat4_look_fps(t_vec3 cam_pos, float yaw, float pitch)
{

	t_vec3	forward;
	t_vec3	left;
	t_vec3	up;
	t_mat4	res;

	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	left = ft_new_vec3(cosYaw, 0, -sinYaw);
	up = ft_new_vec3(sinYaw* sinPitch, cosPitch, cosYaw * sinPitch);
	forward = ft_new_vec3(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

	res = ft_mat4_eye();
	res.as_mat[0] = left.x;
	res.as_mat[4] = left.y;
	res.as_mat[8] = left.z;
	res.as_mat[1] = up.x;
	res.as_mat[5] = up.y;
	res.as_mat[9] = up.z;
	res.as_mat[2] = forward.x;
	res.as_mat[6] = forward.y;
	res.as_mat[10] = forward.z;
	/*	
		res.as_mat[12] =  -left.x * cam_pos.x - left.y * cam_pos.y - left.z * cam_pos.z;
		res.as_mat[13] = -up.x * cam_pos.x - up.y * cam_pos.y - up.z * cam_pos.z;
		res.as_mat[14] = -forward.x * cam_pos.x - forward.y * cam_pos.y - forward.z * cam_pos.z;
		*/
	res.as_mat[12] =  -ft_dot_product(left, cam_pos);
	res.as_mat[13] =  -ft_dot_product(up, cam_pos);
	res.as_mat[14] =  -ft_dot_product(forward, cam_pos);

	return (res);
}

