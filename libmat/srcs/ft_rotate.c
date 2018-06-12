/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 22:57:58 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 11:08:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_mat4	ft_mat4_rotate_x(double alpha)
{
	t_mat4 mat;

	mat.as_mat[0] = 1;
	mat.as_mat[1] = 0;
	mat.as_mat[2] = 0;
	mat.as_mat[3] = 0;
	mat.as_mat[4] = 0;
	mat.as_mat[5] = cos(alpha);
	mat.as_mat[6] = sin(alpha);
	mat.as_mat[7] = 0;
	mat.as_mat[8] = 0;
	mat.as_mat[9] = -sin(alpha);
	mat.as_mat[10] = cos(alpha);
	mat.as_mat[11] = 0;
	mat.as_mat[12] = 0;
	mat.as_mat[13] = 0;
	mat.as_mat[14] = 0;
	mat.as_mat[15] = 1;
	return (mat);
}

t_mat4	ft_mat4_rotate_y(double beta)
{
	t_mat4 mat;

	mat.as_mat[0] = cos(beta);
	mat.as_mat[1] = 0;
	mat.as_mat[2] = -sin(beta);
	mat.as_mat[3] = 0;
	mat.as_mat[4] = 0;
	mat.as_mat[5] = 1;
	mat.as_mat[6] = 0;
	mat.as_mat[7] = 0;
	mat.as_mat[8] = sin(beta);
	mat.as_mat[9] = 0;
	mat.as_mat[10] = cos(beta);
	mat.as_mat[11] = 0;
	mat.as_mat[12] = 0;
	mat.as_mat[13] = 0;
	mat.as_mat[14] = 0;
	mat.as_mat[15] = 1;
	return (mat);
}

t_mat4	ft_mat4_rotate_z(double gamma)
{
	t_mat4 mat;

	mat.as_mat[0] = cos(gamma);
	mat.as_mat[1] = sin(gamma);
	mat.as_mat[2] = 0;
	mat.as_mat[3] = 0;
	mat.as_mat[4] = -sin(gamma);
	mat.as_mat[5] = cos(gamma);
	mat.as_mat[6] = 0;
	mat.as_mat[7] = 0;
	mat.as_mat[8] = 0;
	mat.as_mat[9] = 0;
	mat.as_mat[10] = 1;
	mat.as_mat[11] = 0;
	mat.as_mat[12] = 0;
	mat.as_mat[13] = 0;
	mat.as_mat[14] = 0;
	mat.as_mat[15] = 1;
	return (mat);
}

t_mat4	ft_mat4_rotate(double alpha, double beta, double gamma)
{
	t_mat4 mat_x;
	t_mat4 mat_y;
	t_mat4 mat_z;

	mat_x = ft_mat4_rotate_x(alpha);
	mat_y = ft_mat4_rotate_y(beta);
	mat_z = ft_mat4_rotate_z(gamma);
	return (ft_mat4_mult(ft_mat4_mult(mat_x, mat_y), mat_z));
}

t_mat4	ft_mat4_rotate_vec(t_point3d vec)
{
	t_mat4 mat_x;
	t_mat4 mat_y;
	t_mat4 mat_z;

	mat_x = ft_mat4_rotate_x(vec.x);
	mat_y = ft_mat4_rotate_y(vec.y);
	mat_z = ft_mat4_rotate_z(vec.z);
	return (ft_mat4_mult(ft_mat4_mult(mat_x, mat_y), mat_z));
}
