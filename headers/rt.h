/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:02:45 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/17 04:12:10 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../minilibx_macos/mlx.h"
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>

# define NTHREADS 4

# define BACKGROUND_COLOR = (t_color){.r=80,.g=80,.b=80,.col=0x505050}
# define SPHERE1_POS p = (t_point3d){.x=0.0,.y=0.0,.z=0.0}, 1.0
# define SPHERE1_COL c = (t_color){.r=255,.g=0,.b=0,.col=0xFF0000}
# define SPHERE2_POS p = (t_point3d){.x=0.0,.y=0.0,.z=0.0}
# define SPHERE2_COL c = (t_color){.r=255,.g=255,.b=255,.col=0xFFFFFF}
# define PLANE1_POS p = (t_point3d){.x=0.0,.y=0.0,.z=0.0}
# define PLANE1_COL c = (t_color){.r=255,.g=255,.b=255,.col=0xFFFFFF}
# define PLANE2_POS p = (t_point3d){.x=0.0,.y=0.0,.z=0.0}
# define PLANE2_COL c = (t_color){.r=255,.g=255,.b=255,.col=0xFFFFFF}
# define CUBE1_POS p = (t_point3d){.x=0.0,.y=0.0,.z=0.0}
# define CUBE1_COL c = (t_color){.r=255,.g=255,.b=255,.col=0xFFFFFF}
# define CUBE2_POS p = (t_point3d){.x=0.0,.y=0.0,.z=0.0}
# define CUBE2_COL c = (t_color){.r=255,.g=255,.b=255,.col=0xFFFFFF}

typedef struct	s_pixel
{
	int			x;
	int			y;
}				t_pixel;

typedef struct	s_canvas
{
	void		*mlx;
	void		*win;
	void		*next_img;
	int			*img_arr;
	t_pixel		win_size;
	int			bpp;
	int			size_line;
	int			endian;
}				t_canvas;

typedef struct	s_point3d
{
	double		x;
	double		y;
	double		z;
}				t_point3d;

/*
** o = origin
** v = vector
** s = scale
** r = rotation
** df = distancia focal
*/
typedef struct	s_line
{
	t_point3d	o;
	t_point3d	v;
}				t_line;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	col;
}						t_color;

/*
** the scanhit function is what determines what the object is, as we
** only need the object to calculate the intersection with the ray
*/
typedef t_point3d	(*scanhit)(t_line, t_object);
typedef struct	s_object
{
	scanhit		intersect_func;
	t_point3d	o;
	t_point3d	s;
	t_point3d	r;
	t_color		c;
}				t_object;

typedef struct			s_objlist
{
	t_object			object;
	struct s_objlist	*next;
}						t_objlist;

typedef struct			s_hit
{
	t_object 			obj;
	t_point3d			point;
}						t_hit;

typedef struct	s_camera
{
	t_point3d	o;
	t_point3d	r;
	double		df;
}				t_camera;

typedef struct	s_world
{
	t_canvas	*canvas;
	t_camera	*cam;
	t_objlist	*objlist;
}				t_world;

typedef struct	s_thr_par
{
	t_world		*world;
	int			p_y;
}				t_thr_par;

/*
** input
*/
int				draw_frame(void *param);
int				key_press(int keycode, void *param);

/*
** world
*/
t_world			*new_world(unsigned char map);
void			populate_world(t_world *world, unsigned char scene);
t_object		create_sphere(t_point3d pos, double red, t_color color);
void			add_obj(t_objlist **lst, t_object object);
void			del_lst(t_objlist **lst);

/*
**render
*/
void			paint_threaded(t_world *world);
t_color			render_pixel(t_world *world, t_pixel pix);
void			paint_pixel(t_pixel p, t_color c, t_canvas *canvas);

/*
** intersections
*/
t_point3d		intersect_shpere(t_line line, t_object obj);
t_point3d		intersect_cone(t_line line, t_object obj);
t_point3d		intersect_plane(t_line line, t_object obj);
t_point3d		intersect_cylinder(t_line line, t_object obj);

#endif
