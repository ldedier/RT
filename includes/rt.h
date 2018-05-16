/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:02:45 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/16 21:13:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DONE	reflexion
//DONE	directional light
//DONE	nimin valors atribut (si reflection es 0 no cal calcular...)
//TODO	perturbation (wave, random, spikes...)
//TODO	negative object
//TODO	antialiasing / other filters
//TODO	cartoon shading: if radic ~= 0, its a border.
//		then just check illum < val for shadow
//DONE	low resolution when moving camera
//DONE	paint_threaded only when a key is pressed, and not always
//DONE	paint threaded on enter press.
//DONE	fix enter detection (only push start threading)
//TODO	fps counter
//TODO	progress bar
//TODO	better distribution of pixels in threads, to avoid very expensive zones
//DONE	mr bean
//TODO	(?)start rendering detailed scene when not moving, cancel if move again

#ifndef RT_H
# define RT_H

# include <SDL.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include "libmat.h"
# include "objects.h"
# include "export.h"
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>

# define NTHREADS 8
# define STACK 0
# define POP 1

# define FAST_HRES 160
# define FAST_VRES 120
# define HRES 1600
# define VRES 1200
# define PROGRESS_BAR_HEIGHT 100
# define PERSPECTIVE 2
# define ZOOM 1.5
# define CAMERA_FD 1

# define AXIS_X (t_point3d){.x=1.0,.y=0.0,.z=0.0}
# define AXIS_Y (t_point3d){.x=0.0,.y=1.0,.z=0.0}
# define AXIS_Z (t_point3d){.x=0.0,.y=0.0,.z=1.0}

# define CAMERA_POS (t_point3d){.x=0.0,.y=-0.0,.z=-2.0}
# define CAMERA_LOOK (t_point3d){.x=-0.0,.y=0.0,.z=1.0}
# define CAMERA_UP (t_point3d){.x=-0.0,.y=-1.0,.z=0.0}

# define KEY_UP 49
# define KEY_DOWN 257
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_FORWARD 13
# define KEY_BACKWARD 1
# define KEY_RESET 15
# define KEY_TLEFT 124
# define KEY_TRIGHT 123
# define KEY_ABOVE 126
# define KEY_BELOW 125

# define MAX_LIGHTS 10
# define AMBIENT_LIGHT 0.17
# define AMBIENT_LIGHT_COL get_color(0xFFFFFF)
# define PHONG 30.0
# define EPSILON 0.00001
# define SPEED 0.1
# define MAX_BOUNCE 2

# define POINT_ZERO (t_point3d){.x=0.0,.y=0.0,.z=0.0}
# define BLACK_COLOR (t_color){.r=0,.g=0,.b=0,.col=0x0}
# define WHITE_COLOR (t_color){.r=255,.g=255,.b=255,.col=0XFFFFFF}
# define BACKGROUND_COLOR get_color(0x222222)

typedef struct	s_hit t_hit;

typedef enum	e_keys
{
				up,
				down,
				left,
				right,
				key_o,
				key_p,
				key_7,
				key_8,
				key_5,
				key_4,
				key_2,
				key_1,
				key_w,
				key_a,
				key_s,
				key_d,
				key_e,
				key_q,
				key_z,
				key_c,
				key_x,
				key_v,
				key_ctrl,
				key_space,
				key_shift,
				mouse_move,
				key_enter,
				nkeys
}				t_keys;

typedef struct			s_pixel
{
	int					x;
	int					y;
}						t_pixel;

typedef struct			s_canvas
{
	SDL_Renderer		*renderer;
	SDL_Window			*window;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
	SDL_Rect			pb_rect;
	SDL_Rect			screen;
	t_pixel				win_size;
	t_pixel				halved_win_size;
	int					npixels;
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
	t_point3d			right;
	t_point3d			rotation;
	double				fd;
	double				pd;
	double				speed;
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

typedef union			s_object_union
{
	t_sphere			sphere;
	t_cone				cone;
	t_plane				plane;
	t_cylinder			cylinder;
}						t_object_union;

typedef struct			s_object
{
	t_mat4				transform_pos;
	t_mat4				transform_dir;
	t_mat4				transform_dir_inv;
	t_mat4				transform_pos_inv;
	t_object_union		object_union;
	int					(*intersect_func)(t_line, struct s_object, t_hit*);
//	t_point3d			(*normal_func)(struct s_object, t_point3d);
	t_point3d			o;
	t_point3d			s;
	t_point3d			r;
	t_color				c;
	double				shine;
	double				reflect;
	double				refract;
	double				transp;
}						t_object;

struct			s_hit
{
	t_object			obj;
	t_point3d			point;
	t_point3d			normal;
	t_point3d			bounce;
	double				t;
};

typedef struct			s_auxcone
{
	double				dv;
	t_point3d			colo;
	t_point3d			slvdv;
	t_point3d			slvdvv;
	double				colod;
	t_point3d			sdcolod;
	t_point3d			sdcolo2d;
	double				sqcos;
	double				sqsin;
	/*
	double				sqcos;
	double				dv;
	t_point3d			co;
	double				cov;
	*/
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
	t_object			*object;
	struct s_objlist	*next;
}						t_objlist;

typedef struct			s_cobject
{
	t_point3d			o;
	t_point3d			s;
	t_point3d			r;
	t_color				c;
	double				shine;
	double				reflect;
	double				refract;
	double				transp;
	t_objlist			*objlist;
}						t_cobject;

typedef struct			s_cobjlist
{

	t_cobject			*cobject;
	struct s_cobjlist	*next;
}						t_cobjlist;

typedef struct			s_light
{
	t_point3d			o;
	t_point3d			v;
	t_color				c;
	double				intensity;
	double				angle;
	char				type;
}						t_light;

typedef struct			s_illum
{
	double				in;
	t_color				color;
}						t_illum;

typedef struct			s_world
{
	t_light				lights[MAX_LIGHTS];
	t_canvas			*canvas;
	t_camera			*cam;
	int					keys[nkeys];
	pthread_t			threads[NTHREADS];
	int					thr_state[NTHREADS];
	t_cobjlist			*cobjlist;
	t_cobject			*selected_cobject;
	t_illum				ambient;
	t_illum				fog;
	int					nlights;
	int					progress;
	int					cancel_render;
	int					can_export;
}						t_world;

typedef struct			s_thr_par
{
	t_world				*world;
	int					p_y;
	int					id;
}						t_thr_par;

typedef struct			s_shadowsfree
{
	t_line				**srays;
	int					nlights;
}						t_shadowsfree;

typedef enum			e_parse_enum
{
	e_parse_camera,
	e_parse_object,
	e_parse_cobject,
	e_parse_light,
	e_parse_ambient,
	e_parse_fog,
	e_parse_scene
}						t_parse_enum;


typedef struct			s_parser
{
	t_list				*tag_stack;
	char				*tag;
	char				*attribute;
	t_parse_enum		parse_enum;
	int					nb_lines;
	int					op;
	int					got_scene;
}						t_parser;

/*
** input
*/
void					ft_loop(t_world *world);
int						draw_frame(void *param);
int						key_press(int keycode, void *param);
int						end(t_world *world);
int						get_input(t_world *e);
void					ft_keys_event(t_world *world, SDL_Event event, int down);
void					ft_process(t_world *world);
void					ft_mouse_motion(t_world *world, SDL_Event event);

/*
** world
*/
int						new_world(char* file, t_world **world);
t_canvas				*new_canvas(void);
void					set_defaults(t_world *world);
int						ft_init_all(t_canvas *canvas);
void					ft_init_keys(t_world *world);
int						read_world(t_world *world, char *file);
void					populate_world(t_world *world, unsigned char scene);
t_object				create_sphere(t_point3d pos, double red, t_color color);
void					add_obj(t_objlist **lst, t_object *object);
void					add_cobj(t_cobjlist **lst, t_cobject *cobject);
void					del_clst(t_cobjlist **lst);
void					del_lst(t_objlist **lst);
t_object				*ft_new_object(t_cobject cobject);
t_cobject				*ft_new_cobject(void);
void					ft_init_light(t_light *light);
/*
** parser
*/
int						parse_sphere(char *line, t_object *rsphere);
int						parse_plane(char *line, t_object *rplane);
int						parse_cone(char *line, t_object *rcone);
int						parse_cylinder(char *line, t_object *rcylinder);
int						parse_light(char *line, t_light *rlight);
int						read_hex(char **line, int *to);
int						read_double(char **line, double *to);
int						parse_ambient(char *line, t_illum *rillum);
int						parse_fog(char *line, t_illum *rillum);
void					ft_process_parsing(t_parser *prsr, t_world *world,
						char *line);
void					ft_process_parsing_pos(t_parser *prsr,
						t_world *world, char *line);
void					ft_process_parsing_rot(t_parser *prsr, t_world *world,
						char *line);
int						parse_line_new(char *line, t_world *world,
						t_parser *parser);
void					ft_init_parser(t_parser *parser);
int						ft_parse_tag(char **line, char **tag, char **attribute);
//int						ft_parse_tag(t_parser *parser, char **line);
void					ft_process_tag_stack(t_parser *parser);
void					ft_parse_src(t_parser *parser, t_world *world, char *l);
void					ft_parse_color(t_parser *pr, t_world *wld, char *l);
void					ft_parse_transparency(t_parser *pr,
						t_world *wld, char *l);
void					ft_parse_shine(t_parser *p, t_world *w, char *l);
void					ft_parse_refraction(t_parser *p, t_world *w, char *l);
void					ft_parse_reflection(t_parser *p, t_world *w, char *l);
void					ft_parse_radius(t_parser *p, t_world *w, char *l);
void					ft_parse_angle(t_parser *p, t_world *w, char *l);
void					ft_parse_intensity(t_parser *p, t_world *w, char *l);
void					ft_process_parsing_object_start(t_parser *p,
						t_world *w);
void					ft_process_parsing_cobject_start(t_parser *p,
						t_world *w);
void					ft_process_parsing_scale(t_parser *p, t_world *w, 
						char *l);
void					ft_process_parsing_scale(t_parser *p, t_world *w, 
						char *l);
void					ft_process_parsing_stack(t_parser *p, t_world *w, 
						char *l);
void					ft_process_parsing_light_start(t_parser *p, t_world *w);
void					ft_process_parsing_ambient_start(t_parser *p,
						t_world *w);
void					ft_process_parsing_ambient_start(t_parser *p,
						t_world *w);
void					ft_process_parsing_object_attributes(t_parser *p,
						t_object *object);
void					ft_give_default_characteristics(t_object *object);
/*
**vectors
*/
t_point3d				newvector(t_point3d from, t_point3d to);
double					dotprod(t_point3d v1, t_point3d v2);
t_point3d				crossprod(t_point3d v1, t_point3d v2);
double					magnitude(t_point3d v);
t_point3d				reflection(t_point3d n, t_point3d v);
t_point3d				normalize(t_point3d v);
t_point3d				addvecs(t_point3d v1, t_point3d v2);
double					proj(t_point3d v1, t_point3d v2);
t_point3d				create_vec(double x, double y, double z);
t_point3d				reflection(t_point3d n, t_point3d v);

/*
**colors 
*/
t_color					interpole_color(double t, t_color c1, t_color c2);
t_color					get_color(int color);
t_color					add_colors(t_color c1, t_color c2);
t_color					scale_color(t_color c, double t);

/*
**render
*/
t_color					render_pixel(t_world *world, t_pixel pix, int fast);
void					paint_pixel(t_pixel p, t_color c, t_canvas *canvas);
t_hit					*trace(t_line line, t_cobjlist *cobjlist);
void					castshadows(t_world *w, t_hit *h, t_line **rays);
t_color					illuminate(t_world *world, t_hit *hit, t_line **srays, int fast);

/*
**paint window
*/
void					paint_threaded_fast(t_world *world);
void					fill_canvas(t_world *world);
void					join_threads(t_world *world);
void					paint_threaded(t_world *world);
void					paint_not_threaded(t_world *world);
void					update_progress_bar(t_world *world);

/*
** intersections
*/
int						intersect_sphere(t_line line, t_object obj,
		t_hit *hit);
int						intersect_cone(t_line line, t_object obj,
		t_hit *hit);
int						intersect_plane(t_line line, t_object obj,
		t_hit *hit);
int						intersect_cylinder(t_line line, t_object obj,
		t_hit *hit);
/*
**normals
*/
t_point3d				normal_sphere(t_object sphere, t_point3d hitpoint);
t_point3d				normal_cone(t_object sphere, t_point3d hitpoint);
t_point3d				normal_plane(t_object sphere, t_point3d hitpoint);
t_point3d				normal_cylinder(t_object sphere, t_point3d hitpoint);

/*
**translations
*/
t_point3d				translate_vec(t_point3d p, t_point3d v, double scale);
void					translate(t_object *obj, t_point3d v);
t_point3d				scale(t_point3d p, double scale);

/*
**rotations
*/
t_point3d				rotate_axis(t_point3d v, t_point3d axis, double angle);
t_point3d				rotate_vec(t_point3d v, t_point3d a);
void					rotate(t_object *obj, t_point3d a);

/*
**camera rotations
*/
void					rotate_hor(t_camera *cam, double angle);
void					rotate_ver(t_camera *cam, double angle);
void					camera_reset(t_camera *cam);
void					apply_rotation(t_camera *cam);

/*
** matrices
*/

void	ft_compute_matrix(t_object *object);
void	ft_compute_matrices_clist(t_cobjlist *cobjects);

/*
** export
*/

int					ft_export_rt(t_world *world, char *extension);

/*
** error
*/

void				ft_error(char *str);

//DEBUG OJU CUIDOA BORRAR OSTIEeeeeS
void print_cobject(t_cobject cobj);
void print_clist(t_cobjlist *lst);
void print_list(t_objlist *lst);
void print_object(t_object obj);
void print_lights(t_world *world);
void print_camera(t_camera *cam);

#endif
