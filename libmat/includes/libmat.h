/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 00:16:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/15 17:29:39 by ldedier          ###   ########.fr       */
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

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

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

typedef struct		s_camera
{
	float			fov;
	float			ratio;
	float			near;
	float			far;
	float			yaw;
	float			pitch;
	float			roll;
	t_vec3			position;
	t_vec3			rotation;
}					t_camera;


t_vec3				ft_new_vec3(float x, float y, float z);
float				ft_vec3_get_norm(t_vec3 vec);
void				ft_vec3_normalize(t_vec3 *vec);

t_vec3				ft_vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3				ft_vec3_cmp(t_vec3 vec1, t_vec3 vec2);
t_vec3				ft_vec3_scalar(t_vec3 vec1, float k);
t_vec3				ft_vec3_cross_product(t_vec3 vec1, t_vec3 vec2);
float				ft_dot_product(t_vec3 vec1, t_vec3 vec2);


t_mat4				ft_mat4_mult(t_mat4 mat1, t_mat4 mat2);
t_vec3				ft_vec3_mat4_mult(t_vec3 vec, t_mat4 mat);

t_mat4				ft_mat4_transpose(t_mat4 mat);
t_mat4				ft_mat4_eye(void);
t_mat4				ft_mat4_scale(float zoom);
t_mat4				ft_mat4_scale_vec(t_vec3 vec);
t_mat4				ft_mat4_translate_vec(t_vec3 vec);
t_mat4				ft_mat4_rotate_x(float alpha);
t_mat4				ft_mat4_rotate_y(float beta);
t_mat4				ft_mat4_rotate_z(float gamma);
t_mat4				ft_mat4_rotate(float alpha, float beta, float gamma);
t_mat4				ft_mat4_rotate_vec(t_vec3);
t_mat4				ft_mat4_look_at(t_vec3 camera, t_vec3 target, t_vec3 up_axis);
t_mat4				ft_mat4_look_fps(t_vec3 camera, float yaw, float pitch);
t_mat4				ft_mat4_perspective(t_camera cam);
t_mat4				ft_mat4_model_view_matrix_vec(t_vec3 translate, t_vec3 scale, t_vec3 rotate);
t_mat4				ft_mat4_model_view_matrix_mat(t_mat4 translate, t_mat4 scale, t_mat4 rotate);
void				ft_print_mat4(t_mat4 mat);
void				ft_print_vec3(t_vec3 vec);
#endif
