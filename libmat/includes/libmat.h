/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 00:16:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/01 05:16:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBMAT_H
# define FT_LIBMAT_H
#include <stdio.h> // TO DELL
#include <stdlib.h>
#include <math.h>

typedef struct		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_point3d
{
	double			x;
	double			y;
	double			z;
}					t_point3d;


typedef struct		s_vec4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec4;

typedef struct		s_vec4_repr
{
	t_vec4			vec1;
	t_vec4			vec2;
	t_vec4			vec3;
	t_vec4			vec4;
}					t_vec4_repr;

typedef union		u_mat4
{
	t_vec4_repr		as_vec4;
	float			as_mat[16];
}					t_mat4;

typedef struct		s_camera_l
{
	float				fov;
	float				ratio;
	float				near;
	float				far;
	float				yaw;
	float				pitch;
	float				roll;
	t_point3d			position;
	t_point3d			rotation;
}					t_camera_l;


t_point3d				ft_new_vec3(float x, float y, float z);
float				ft_point3d_get_norm(t_point3d vec);
void				ft_point3d_normalize(t_point3d *vec);

t_point3d				ft_point3d_add(t_point3d vec1, t_point3d vec2);
t_point3d				ft_point3d_cmp(t_point3d vec1, t_point3d vec2);
t_point3d				ft_point3d_scalar(t_point3d vec1, float k);
t_point3d				ft_point3d_cross_product(t_point3d vec1, t_point3d vec2);
float				ft_dot_product(t_point3d vec1, t_point3d vec2);

t_mat4				ft_mat4_mult(t_mat4 mat1, t_mat4 mat2);
t_point3d			ft_point3d_mat4_mult(t_point3d vec, t_mat4 mat);

t_mat4				ft_mat4_transpose(t_mat4 mat);
t_mat4				ft_mat4_eye(void);
t_mat4				ft_mat4_scale(float zoom);
t_mat4				ft_mat4_scale_vec(t_point3d vec);
t_mat4				ft_mat4_translate_vec(t_point3d vec);
t_mat4				ft_mat4_rotate_x(float alpha);
t_mat4				ft_mat4_rotate_y(float beta);
t_mat4				ft_mat4_rotate_z(float gamma);
t_mat4				ft_mat4_rotate(float alpha, float beta, float gamma);
t_mat4				ft_mat4_rotate_vec(t_point3d);
t_mat4				ft_mat4_look_at(t_point3d camera, t_point3d target, t_point3d up_axis);
t_mat4				ft_mat4_look_fps(t_point3d camera, float yaw, float pitch);
t_mat4				ft_mat4_perspective(t_camera_l cam);
t_mat4				ft_mat4_model_view_matrix_vec(t_point3d translate, t_point3d scale, t_point3d rotate);
t_mat4				ft_mat4_model_view_matrix_mat(t_mat4 translate, t_mat4 scale, t_mat4 rotate);
void				ft_print_mat4(t_mat4 mat);
void				ft_print_point3d(t_point3d vec);
#endif
