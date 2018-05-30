/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:02:45 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/30 06:37:06 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DONE	fix <perturbation>asdf</perturbation> segfault
//DONE	reflexion
//DONE	directional light
//DONE	nimin valors atribut (si reflection es 0 no cal calcular...)
//DONE	perturbation (wave, random, spikes...)
//TODO	negative object
//done	antialiasing / other filters
//DONE	fix sometimes cancel the render and go into antialiasing. cause is calling join_threads 2 times in a row and 2nd one returns 0 so assumes it rendered.
//TODO	controls chachis -> select object
//TODO	antialiasing multiple rays per pixel (then get the mean)
//DONE	cartoon shading.
//TODO	gooch shading -> borders bons pel cartoon?
//DONE	low resolution when moving camera
//DONE	paint_threaded only when a key is pressed, and not always
//DONE	paint threaded on enter press.
//DONE	fix enter detection (only push start threading)
//TODO	fps counter
//DONE	progress bar
//TODO	better distribution of pixels in threads, to avoid very expensive zones
//DONE	mr bean
//TODO	(?)start rendering detailed scene when not moving, cancel if move again
//DONE separate normals and intersections calculating

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
# include "obj.h"
# include "export.h"
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <complex.h>
# include <sys/mman.h>
# include <sys/stat.h>

# define NTHREADS 4
# define STACK 0
# define POP 1
# define MAX_DEGREE 4

# define FAST_HRES 160
# define FAST_VRES 120
# define HRES 1600
# define VRES 1200
# define PROGRESS_BAR_HEIGHT 20
# define PERSPECTIVE 2
# define ZOOM 1.5
# define CAMERA_FD 1

# define AXIS_X (t_point3d){.x=1.0,.y=0.0,.z=0.0}
# define AXIS_Y (t_point3d){.x=0.0,.y=1.0,.z=0.0}
# define AXIS_Z (t_point3d){.x=0.0,.y=0.0,.z=1.0}

# define CAMERA_POS (t_point3d){.x=0.0,.y=-0.0,.z=-2.0}
# define CAMERA_LOOK (t_point3d){.x=-0.0,.y=0.0,.z=1.0}
# define CAMERA_UP (t_point3d){.x=-0.0,.y=-1.0,.z=0.0}

# define MAX_LIGHTS 10
# define AMBIENT_LIGHT 0.17
# define AMBIENT_LIGHT_COL get_color(0xFFFFFF)
# define PHONG 30.0
# define EPSILON 0.01
# define EPSILON2 0.000000001 //plus petit = plus de quartic plutot que de cubic
# define EPSILON3 0.000001 //plus petit = moins de solution
# define EPSILON4 0.00000001 // on considere ca comme zero complexe (surtout used dans quartic)
# define SPEED 0.1
# define MAX_BOUNCE 20

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
	t_pixel				fast_win_size;
	t_pixel				halved_win_size;
	int					npixels;
	double				ratio;
}						t_canvas;

typedef struct			s_affine
{
	long double			a;
	long double			b;
	double				debug;
}						t_affine;

typedef struct			s_quadratic
{
	double				a;
	double				b;
	double				c;
	double				radic;
	double				debug;
}						t_quadratic;

typedef struct			s_quadsol
{
	double				t1;
	double				t2;
}						t_quadsol;

typedef struct			s_auxquart_init
{
	long double				vx2;
	long double				vx3;
	long double				vx4;
	long double				ox2;
	long double				ox3;
	long double				ox4;
	long double				vy2;
	long double				vy3;
	long double				vy4;
	long double				oy2;
	long double				oy3;
	long double				oy4;
	long double				vz2;
	long double				vz3;
	long double				vz4;
	long double				oz2;
	long double				oz3;
	long double				oz4;
}						t_auxquart_init;

typedef struct			s_auxcubic
{
	long double complex		s;
	long double complex		d;
	long double complex		e;
	long double complex		sqrt;
	long double	complex			f;
	long double	complex		g;
	long double	complex		h;
	long double	complex		i;
	long double	complex		j;
	long double		complex		k;
	long double	complex	l;
	long double	complex		m;
	long double	complex		n;
	long double complex		p;
	long double complex		r;
	//	long double  			s;
	long double complex			t;
	long double complex		u;

}						t_auxcubic;


typedef struct			s_auxquartic
{
	long double complex		alpha;
	long double complex		beta;
	long double complex		gamma;
	long double complex		rad;
	long double complex		p;
	long double complex		q;
	long double complex		r;
	long double complex		u;
	long double complex		y;
	long double complex		w;
	long double complex		t;
	long double complex		r1;
	long double complex		r2;
}						t_auxquartic;

typedef struct			s_quartic
{
	long double				a;
	long double				b;
	long double				c;
	long double				d;
	long double				e;
	double				debug;
}						t_quartic;

typedef struct			s_cubic
{
	long double				a;
	long double				b;
	long double				c;
	long double				d;
	double				debug;
}						t_cubic;

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
	int x;
	int y;
	double n;
	t_point3d oldo;
	t_point3d oldv;
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

typedef struct			s_intcolor
{
	float				r;
	float				g;
	float				b;
}						t_intcolor;

/*
 ** the scanhit function is what determines what the object is, as we
 ** only need the object to calculate the intersection with the ray
 */

typedef enum			e_perturbations
{
	e_none,
	e_ripple,
	e_waves,
	e_noise,
	e_chess,
	e_spiral
}						t_perturbations;

typedef struct			s_cut
{
	double				value;
	t_point3d			cut_xyz;
	int					(*inequality)(double, double);
	int					relative;
	int					circular;
}						t_cut;

typedef union			s_object_union
{
	t_sphere			sphere;
	t_cone				cone;
	t_plane				plane;
	t_cylinder			cylinder;
	t_ellipsoid			ellipsoid;
	t_torus				torus;
	t_goursat			goursat;
	t_hyperboloid		hyperboloid;
	t_paraboloid		paraboloid;
	t_triangle			triangle;
	t_box				box;
}						t_object_union;

typedef struct			s_object
{
	t_mat4				transform_pos;
	t_mat4				transform_dir;
	t_mat4				transform_dir_inv;
	t_mat4				transform_pos_inv;
	t_object_union		object_union;
	int					(*intersect_func)(t_line, struct s_object, double sols[MAX_DEGREE]);
	int					(*inside_func)(t_hit h, struct s_object);
	t_point3d			(*normal_func)(struct s_object, t_point3d, t_line line);
	t_point3d			o;
	t_point3d			s;
	t_point3d			r;
	t_color				c;
	t_perturbations		pert;
	t_list				*cuts;
	double				shine;
	double				reflect;
	double				refract;
	double				transp;
	int					negative;
}						t_object;

struct			s_hit
{
	t_object			obj;
	t_point3d			point;
	t_point3d			normal;
	t_point3d			pert;
	t_point3d			bounce;
	t_point3d			pertbounce;
	int					enter;
//	t_color				col;
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

typedef struct			s_objlist
{
	t_object			*object;
	struct s_objlist	*next;
}						t_objlist;

typedef union			u_cobject_union
{
	t_sphere_torus		sphere_torus;
	t_adn				adn;
}						t_cobject_union;

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
	t_perturbations		pert;
	t_objlist			*objlist;
	t_cobject_union		cobject_union;
	int					negative;
	int					regular;
}						t_cobject;

typedef struct			s_cobjlist
{

	t_cobject			*cobject;
	struct s_cobjlist	*next;
}						t_cobjlist;

typedef struct			s_auxtorus
{
	double				g;
	double				h;
	double				i;
	double				j;
	double				k;
	double				l;
}						t_auxtorus;

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

typedef enum			e_filters
{
	e_gauss_blur,
	e_sharpen,
	e_sobel,
	e_emboss,
	e_grey,
	e_nfilters
}						t_filters;

typedef struct			s_world
{
	t_light				lights[MAX_LIGHTS];
	t_canvas			*canvas;
	t_camera			*cam;
	int					keys[nkeys];
	pthread_t			threads[NTHREADS];
	int					thr_state[NTHREADS];
	int					filters[e_nfilters];
	t_cobjlist			*cobjlist;
	t_cobject			*selected_cobject;
	t_illum				ambient;
	t_illum				fog;
	int					nlights;
	int					progress;
	int					cancel_render;
	int					can_export;
	int					shader;
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

typedef struct			s_convolution
{
	t_canvas			*canvas;
	int					*img;
	int					*aux;
	double				*filter;
	t_pixel				pix;
	int					filter_size;
	int					den;
}						t_convolution;

typedef struct			s_sols
{
	double				roots[MAX_DEGREE];
	int					nbsols;
}						t_sols;

typedef enum			e_parse_enum
{
	e_parse_camera,
	e_parse_object,
	e_parse_cobject,
	e_parse_light,
	e_parse_ambient,
	e_parse_fog,
	e_parse_cut,
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

typedef struct  s_mmap
{
	unsigned char   *ptr;
	size_t          size;
}				t_mmap;

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
void					add_obj_cpy(t_objlist **lst, t_object *object);
void					add_cobj(t_cobjlist **lst, t_cobject *cobject);
void					del_clst(t_cobjlist **lst);
void					del_lst(t_objlist **lst);
t_object				*ft_new_object(t_cobject cobject);
t_object				*ft_new_triangle(t_cobject cobject);
t_cobject				*ft_new_cobject(void);
t_cut					*ft_new_cut(void);
void					ft_init_light(t_light *light);
/*
 ** parser
 */
int						parse_sphere(char *line, t_object *rsphere);
int						parse_plane(char *line, t_object *rplane);
int						parse_cone(char *line, t_object *rcone);
int						parse_cylinder(char *line, t_object *rcylinder);
int						parse_light(char *line, t_light *rlight);
int						read_int(char **line, int *to);
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
void					ft_parse_negative(t_parser *par, t_world *w, char *l);
void					ft_parse_pert(t_parser *p, t_world *w, char *l);
void					read_pert_type(t_parser *par, t_perturbations *pert);
void					ft_parse_resolution(t_parser *p, t_world *w, char *l);
void					ft_parse_fast_resolution(t_parser *p, t_world *w,
		char *l);
void					ft_parse_filter(t_parser *p, t_world *w, char *l);
void					ft_parse_shader(t_parser *p, t_world *w, char *l);
void					ft_parse_ellipsoid_abc(t_parser *p, t_world *w,
		char *l);
void					ft_parse_goursat_ab(t_parser *p, t_world *w, char *l);
void					ft_parse_big_radius(t_parser *p, t_world *w, char *l);
void					ft_parse_small_radius(t_parser *p, t_world *w, char *l);
void					ft_process_parsing_object_start(t_parser *p,
		t_world *w);
void					ft_process_parsing_cobject_start(t_parser *p,
		t_world *w);
void					ft_process_parsing_scale(t_parser *p, t_world *w,
		char *l);
void					ft_process_parsing_stack(t_parser *p, t_world *w,
		char *l);
char					*ft_get_between_tag(char **line);
void					ft_process_parsing_light_start(t_parser *p, t_world *w);
void					ft_process_parsing_ambient_start(t_parser *p,
		t_world *w);
void					ft_process_parsing_ambient_start(t_parser *p,
		t_world *w);
void					ft_process_parsing_object_attributes(t_parser *p,
		t_object *object);
void					ft_process_parsing_cut_attributes(t_parser *p,
		t_cut *cut);
void					ft_give_default_characteristics(t_object *object);
void					ft_process_parsing_cut_start(t_parser *p, t_world *w);
void					ft_process_parsing_cut_xyz(t_parser *p, t_world *w,
		char *l);
void					ft_process_parsing_cut_inequality(t_parser *p,t_world *w,
		char *l);
void					ft_process_parsing_cut_value(t_parser *p,t_world *w,
		char *l);
void					ft_process_parsing_vertex_a(t_parser *p,t_world *w,
		char *l);
void					ft_process_parsing_vertex_b(t_parser *p,t_world *w,
		char *l);
void					ft_process_parsing_vertex_c(t_parser *p,t_world *w,
		char *l);
void					ft_parse_nb_spheres(t_parser *p, t_world *w, char *l);
void					ft_parse_spheres_radius(t_parser *p, t_world *w, char *l);
void					ft_parse_length(t_parser *p, t_world *w, char *l);

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
t_point3d				refraction(t_hit *hit, t_line *line);

/*
 **colors
 */
t_color					interpole_color(double t, t_color c1, t_color c2);
t_color					get_color(int color);
t_color					add_colors(t_color c1, t_color c2);
t_color					scale_color(t_color c, double t);

/*
 **int colors (for filter calculations)
 */
t_intcolor				new_intcolor(void);
t_intcolor				add_scale_intcolors(t_intcolor icol1, t_intcolor icol2,
		double scale);
t_intcolor				get_intcolor(t_color color);
t_intcolor				greyscale(t_intcolor ic);
t_color					scale_convert_color(t_intcolor icol, double t);

/*
 **filters
 */
void					apply_convolution(t_world *world);
void					convolute(t_canvas *canvas, double *filter,
		int filter_size, int den);
void					gauss_blur(t_canvas *canvas);
void					sharpen(t_canvas *canvas);
void					emboss(t_canvas *canvas);
void					sobel(t_canvas *canvas);
void					grey(t_canvas *canvas);
void					draw_borders(t_canvas *canvas);

/*
 **render
 */
t_color					render_pixel(t_world *world, t_pixel pix, int fast);
t_point3d				screen2world(t_pixel pix, t_world *world);
void					paint_pixel(t_pixel p, t_color c, t_canvas *canvas);
t_hit					*trace(t_line line, t_cobjlist *cobjlist);
void					castshadows(t_world *w, t_hit *h, t_line **rays);
t_color					illuminate(t_world *world, t_hit *hit,
		t_line **srays, int fast);
t_color					illuminate_toon(t_world *world, t_hit *hit,
		t_line **srays, int fast);

/*
 **paint window
 */
void					paint_threaded_fast(t_world *world);
void					fill_canvas(t_world *world);
int						join_threads(t_world *world);
void					paint_threaded(t_world *world);
void					paint_not_threaded(t_world *world);
void					update_progress_bar(t_world *world);

/*
 ** intersections
 */
int						intersect_sphere(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_cone(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_plane(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_cylinder(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_ellipsoid(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_torus(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_goursat(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_lemniscate(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_piriform(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_roman(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_triangle(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_hyperboloid(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_paraboloid(t_line line, t_object obj,
		double sols[MAX_DEGREE]);
int						intersect_mobius(t_line line, t_object obj,
		double sols[MAX_DEGREE]);

/*
 **normals
 */
t_point3d				normal_sphere(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_cone(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_plane(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_cylinder(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_ellipsoid(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_goursat(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_roman(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_piriform(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_lemniscate(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_torus(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_paraboloid(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_hyperboloid(t_object sphere, t_point3d t, t_line l);
t_point3d				normal_triangle(t_object object, t_point3d p, t_line l);
t_point3d				normal_mobius(t_object object, t_point3d p, t_line l);


/*
 **quartics
 */
t_quartic				get_quartic_piriform(t_line line);
t_quartic				get_quartic_roman(t_line line);
t_quartic				get_quartic_lemniscate(t_line line);
t_quartic				get_quartic_goursat(t_line line, t_object obj);
t_quartic				get_quartic_torus(t_line line, t_object obj);
t_quartic				get_quartic_mobius(t_line line, t_object obj);
void					ft_init_aux(t_auxquart_init *g, t_line line);

/*
 **cuts
 */
int						ft_evaluate_cut(t_cut cut, t_point3d pos);
double					get_smallest_legal_pos_val(t_hit newhit, t_sols sols,
		double min, t_line transformed, t_objlist *objlist, int neg, t_object *other);

/*
 **negatives
 */
int						is_inside_other(t_hit h, t_objlist *objlist, int neg,
		t_object *other);
void					intersect_positive(t_objlist *objlist, t_object obj,
		t_line line, t_hit *hit);
void					intersect_negative(t_objlist *objlist, t_object obj,
		t_line line, t_hit *hit);
int						inside_sphere(t_hit h, t_object obj);
int						inside_cone(t_hit h, t_object obj);
int						inside_cylinder(t_hit h, t_object obj);
int						inside_plane(t_hit h, t_object obj);
int						inside_ellipsoid(t_hit h, t_object obj);
int						inside_torus(t_hit h, t_object obj);
int						inside_goursat(t_hit h, t_object obj);
int						inside_paraboloid(t_hit h, t_object obj);
int						inside_hyperboloid(t_hit h, t_object obj);

/*
 **tools
 */
void    set_funcs(t_object *obj,
		int (*intersect_func)(t_line, t_object, double[MAX_DEGREE]),
		int (*inside_func)(t_hit, t_object),
		t_point3d (*normal_func)(t_object, t_point3d, t_line));


/*
 **inequalities
 */
int						less_than(double a, double b);
int						bigger_than(double a, double b);
int						less_than_or_equal(double a, double b);
int						bigger_than_or_equal(double a, double b);
int						equal(double a, double b);

/*
 **perturbations
 */
t_point3d				pert_normal(t_hit *hit);
t_color					pert_color(t_hit *hit);


/*
 ** automatics
 */

void					ft_process_automatic(t_parser *parser, t_world *world);

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

void					ft_compute_matrix(t_object *object);
void					ft_compute_matrices_clist(t_cobjlist *cobjects);
t_line					ft_transform_line(t_object object, t_line t);
void					ft_transform_hit_back(t_hit *hit);

/*
 ** export
 */

int					ft_export_rt(t_world *world, char *extension);

/*
 ** error
 */

t_mmap			ft_map_file(char *filename);

void				ft_error(char *str);

//DEBUG OJU CUIDOA BORRAR OSTIEeeeeS
void print_cobject(t_cobject cobj);
void print_clist(t_cobjlist *lst);
void print_list(t_objlist *lst);
void print_object(t_object obj);
void print_lights(t_world *world);
void print_camera(t_camera *cam);

#endif
