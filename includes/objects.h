/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 21:04:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/29 21:20:50 by ldedier          ###   ########.fr       */
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

typedef struct		s_adn
{
	int				length;
	int				radius;
}					t_adn;

#endif
