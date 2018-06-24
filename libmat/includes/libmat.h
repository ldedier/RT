/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 00:16:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 11:12:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBMAT_H
# define FT_LIBMAT_H

# include <stdlib.h>
# include <math.h>

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_point3d
{
	double			x;
	double			y;
	double			z;
}					t_point3d;

typedef struct		s_ivec3
{
	int				x;
	int				y;
	int				z;
}					t_ivec3;

typedef struct		s_vec4
{
	double			x;
	double			y;
	double			z;
	double			w;
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
	double			as_mat[16];
}					t_mat4;

typedef struct		s_camera_l
{
	double			fov;
	double			ratio;
	double			near;
	double			far;
	double			yaw;
	double			pitch;
	double			roll;
	t_point3d		position;
	t_point3d		rotation;
}					t_camera_l;

t_point3d			ft_new_vec3(double x, double y, double z);
double				ft_point3d_get_norm(t_point3d vec);
void				ft_point3d_normalize(t_point3d *vec);

t_point3d			ft_point3d_add(t_point3d vec1, t_point3d vec2);
t_point3d			ft_point3d_mult(t_point3d vec1, t_point3d vec2);
t_point3d			ft_point3d_cmp(t_point3d vec1, t_point3d vec2);
t_point3d			ft_point3d_scalar(t_point3d vec1, double k);
t_point3d			ft_point3d_cross_product(t_point3d vec1, t_point3d vec2);
double				ft_dot_product(t_point3d vec1, t_point3d vec2);

t_mat4				ft_mat4_mult(t_mat4 mat1, t_mat4 mat2);
t_point3d			ft_point3d_mat4_mult(t_point3d vec, t_mat4 mat);

t_mat4				ft_mat4_transpose(t_mat4 mat);
t_mat4				ft_mat4_eye(void);
t_mat4				ft_mat4_scale(double zoom);
t_mat4				ft_mat4_scale_vec(t_point3d vec);
t_mat4				ft_mat4_translate_vec(t_point3d vec);
t_mat4				ft_mat4_rotate_x(double alpha);
t_mat4				ft_mat4_rotate_y(double beta);
t_mat4				ft_mat4_rotate_z(double gamma);
t_mat4				ft_mat4_rotate(double alpha, double beta, double gamma);
t_mat4				ft_mat4_rotate_vec(t_point3d v);
t_mat4				ft_mat4_look_at(t_point3d camera, t_point3d target,
		t_point3d up_axis);
t_mat4				ft_mat4_look_fps(t_point3d camera, double yaw, double p);
t_mat4				ft_mat4_perspective(t_camera_l cam);
t_mat4				ft_mat4_model_view_matrix_vec(t_point3d translate,
		t_point3d scale, t_point3d rotate);
t_mat4				ft_mat4_model_view_matrix_mat(t_mat4 translate,
		t_mat4 scale, t_mat4 rotate);
void				ft_print_mat4(t_mat4 mat);
void				ft_print_point3d(t_point3d vec);
void				ft_print_ivec3(t_ivec3 vec);
#endif
