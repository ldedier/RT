/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:02:45 by lcavalle          #+#    #+#             */
/*   Updated: 2018/03/04 02:17:34 by lcavalle         ###   ########.fr       */
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

# define NTHREADS 1

# define HRES 1600
# define VRES 1200
# define PERSPECTIVE 2
# define ZOOM 1.5
# define CAMERA_FD 1

# define CAMERA_POS (t_point3d){.x=0.0,.y=-0.0,.z=-2.0}
# define CAMERA_LOOK (t_point3d){.x=-0.0,.y=0.0,.z=1.0}
# define CAMERA_UP (t_point3d){.x=-0.0,.y=1.0,.z=0.0}
# define H_ROTATION (t_point3d){.x=0.0,.y=0.3,.z=0.0}

# define KEY_UP 49
# define KEY_DOWN 257
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_FORWARD 13
# define KEY_BACKWARD 1
# define KEY_RESET 15

# define NLIGHTS 1
# define AMBIENT_LIGHT 0.07
# define PHONG 20.0
# define EPSILON 0.00000001

# define POINT_ZERO (t_point3d){.x=0.0,.y=0.0,.z=0.0}
# define BLACK_COLOR (t_color){.r=0,.g=0,.b=0,.col=0x0}
# define WHITE_COLOR (t_color){.r=255,.g=255,.b=255,.col=0XFFFFFF}
# define BACKGROUND_COLOR get_color(0x0)
# define SPHERE1_POS (t_point3d){.x=0.0,.y=0.0,.z=3.0}
# define SPHERE1_RAD 0.5
# define SPHERE1_COL get_color(0xFF0000)
# define SPHERE2_POS (t_point3d){.x=-0.0,.y=-0.0,.z=0.0}
# define SPHERE2_RAD 0.2
# define SPHERE2_COL get_color(0x00FF00)
# define SPHERE3_POS (t_point3d){.x=0.07,.y=0.4,.z=2.8}
# define SPHERE3_RAD 0.34
# define SPHERE3_COL get_color(0x0000FF)
# define PLANE1_POS (t_point3d){.x=0.0,.y=2.0,.z=0.0}
# define PLANE1_VEC (t_point3d){.x=0.0,.y=-1.0,.z=-0.0}
# define PLANE1_COL get_color(0xFF00FF)
# define PLANE2_POS (t_point3d){.x=-1.0,.y=0.0,.z=0.0}
# define PLANE2_VEC (t_point3d){.x=1,.y=0.0,.z=-0.0}
# define PLANE2_COL get_color(0xFFFF00)
# define CONE1_POS (t_point3d){.x=0.1,.y=0.05,.z=2.55}
# define CONE1_VEC (t_point3d){.x=1.0,.y=1.0,.z=0.0}
# define CONE1_ANG 0.3
# define CONE1_COL get_color(0x00FFFF)
# define CYL1_POS (t_point3d){.x=0.3,.y=0.7,.z=3.0}
# define CYL1_VEC (t_point3d){.x=0.7,.y=0.2,.z=1.0}
# define CYL1_RAD 0.17
# define CYL1_COL get_color(0xFFAADD)
# define LIGHT1_POS (t_point3d){.x=1.4,.y=-1.0,.z=0.6}
# define LIGHT1_INT 0.95
# define LIGHT2_POS (t_point3d){.x=-0.4,.y=0.1,.z=2.0}
# define LIGHT2_INT 0.4

typedef struct			s_pixel
{
	int					x;
	int					y;
}						t_pixel;

typedef struct			s_canvas
{
	void				*mlx;
	void				*win;
	void				*next_img;
	int					*img_arr;
	t_pixel				win_size;
	t_pixel				halved_win_size;
	int					bpp;
	int					size_line;
	int					endian;
	double				ratio;
}						t_canvas;

typedef struct			s_quadratic
{
	double				a;
	double				b;
	double				c;
	double				radic;
}						t_quadratic;

typedef struct			s_quadsol
{
	double				t1;
	double				t2;
}						t_quadsol;

typedef struct			s_point3d
{
	double				x;
	double				y;
	double				z;
}						t_point3d;

/*
** o = origin
** v = vector
** s = scale
** r = rotation
** fd = focal distance
** pd = pixel distance (in 3d world)
*/
typedef struct			s_line
{
	t_point3d			o;
	t_point3d			v;
}						t_line;

typedef struct			s_camera
{
	t_point3d			o;
	t_point3d			look;
	t_point3d			up;
	double				fd;
	double				pd;
}						t_camera;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned int		col;
}						t_color;

/*
** the scanhit function is what determines what the object is, as we
** only need the object to calculate the intersection with the ray
*/
typedef struct			s_object
{
	int					(*intersect_func)(t_line, struct s_object, t_point3d*);
	t_point3d			(*normal_func)(struct s_object, t_point3d);
	t_point3d			o;
	t_point3d			s;
	t_point3d			r;
	t_color				c;
}						t_object;

typedef struct			s_auxcone
{
	double				sqcos;
	double				dv;
	t_point3d			co;
	double				cov;
}						t_auxcone;

typedef struct			s_auxcyl
{
	t_point3d			colo;
	t_point3d			ddv;
	t_point3d			scolol;
	t_point3d			scolol2;
}						t_auxcyl;

typedef struct			s_objlist
{
	t_object			object;
	struct s_objlist	*next;
}						t_objlist;

typedef struct			s_hit
{
	t_object			obj;
	t_point3d			point;
	t_point3d			normal;
	t_point3d			bounce;
}						t_hit;

typedef struct			s_light
{
	double				intensity;
	t_point3d			o;
}						t_light;

typedef struct			s_world
{
	t_canvas			*canvas;
	t_camera			*cam;
	t_objlist			*objlist;
	t_light				lights[NLIGHTS];
}						t_world;

typedef struct			s_thr_par
{
	t_world				*world;
	int					p_y;
}						t_thr_par;

/*
** input
*/
int						draw_frame(void *param);
int						key_press(int keycode, void *param);
int						expose(void *param);

/*
** world
*/
t_world					*new_world(unsigned char map);
void					populate_world(t_world *world, unsigned char scene);
t_object				create_sphere(t_point3d pos, double red, t_color color);
void					add_obj(t_objlist **lst, t_object object);
void					del_lst(t_objlist **lst);

/*
**vector
*/
t_point3d				newvector(t_point3d from, t_point3d to);
double					dotprod(t_point3d v1, t_point3d v2);
t_point3d				crossprod(t_point3d v1, t_point3d v2);
double					magnitude(t_point3d v);
t_point3d				normalize(t_point3d v);

/*
**render
*/
void					paint_threaded(t_world *world);
t_color					render_pixel(t_world *world, t_pixel pix);
t_color					interpole_color(double t, t_color c1, t_color c2);
t_color					get_color(int color);
void					paint_pixel(t_pixel p, t_color c, t_canvas *canvas);
t_hit					*trace(t_line line, t_objlist *objlist);
/*
** intersections
*/
int						intersect_sphere(t_line line, t_object obj,
		t_point3d *hit);
int						intersect_cone(t_line line, t_object obj,
		t_point3d *hit);
int						intersect_plane(t_line line, t_object obj,
		t_point3d *hit);
int						intersect_cylinder(t_line line, t_object obj,
		t_point3d *hit);
/*
**normals
*/
t_point3d				normal_sphere(t_object sphere, t_point3d hitpoint);
t_point3d				normal_cone(t_object sphere, t_point3d hitpoint);
t_point3d				normal_plane(t_object sphere, t_point3d hitpoint);
t_point3d				normal_cylinder(t_object sphere, t_point3d hitpoint);

/*
**transforms
*/
t_point3d				translate_vec(t_point3d p, t_point3d v, double scale);
void					translate(t_object *obj, t_point3d v);
t_point3d				scale(t_point3d p, double scale);
t_point3d				rotate_vec(t_point3d v, t_point3d a);
void					rotate(t_object *obj, t_point3d a);
#endif
