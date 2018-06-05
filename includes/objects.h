/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 21:04:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/04 02:07:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTS_H
# define FT_OBJECTS_H

#include "libmat.h"

typedef struct		s_box
{
	double			width;
	double			height;
}					t_box;

typedef struct		s_triangle
{
	t_point3d		v1;
	t_point3d		v2;
	t_point3d		v3;
}					t_triangle;

typedef struct		s_goursat
{
	double			a;
	double			b;
}					t_goursat;

typedef struct		s_torus
{
	double			small_rad;
	double			big_rad;
}					t_torus;

typedef struct		s_ellipsoid
{
	double			radius;
	t_point3d		abc;
}					t_ellipsoid;

typedef struct		s_paraboloid
{
}					t_paraboloid;

typedef struct		s_hyperboloid
{
	double			radius;
}					t_hyperboloid;

typedef struct		s_sphere
{
	double			radius;
}					t_sphere;

typedef struct		s_cone
{
	double			angle;
}					t_cone;

typedef struct		s_plane
{
	double			texture_stretch_x;
	double			texture_stretch_y;
	int				texture_trans_x;
	int				texture_trans_y;
}					t_plane;

typedef struct		s_cylinder
{
	double			radius;
}					t_cylinder;

typedef struct		s_sphere_torus
{
	int				nb_spheres;
	double			radius;
	double			spheres_radius;
}					t_sphere_torus;

typedef enum		e_style
{
	e_plain,
	e_irregular
}					t_style;

typedef struct		s_adn
{
	int				length;
	double			radius;
	int				color1;
	int				color2;
	int				color3;
	t_style			style;
}					t_adn;

#endif
