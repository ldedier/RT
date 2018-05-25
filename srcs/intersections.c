/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 01:01:52 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/25 21:10:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** quadratic equation. simpliefied a, b and c. also simplified formula
** (wikipedia line-sphere intersection)
*/

int					intersect_sphere(t_line line, t_object obj,
		t_hit *hit)
{
	t_quadratic	equa;
	t_quadsol	sols;
	double		radic;

	equa = (t_quadratic){.a = dotprod(line.v, line.v), .b = 2 *
		dotprod(line.o, line.v),
			.c = dotprod(line.o, line.o) - (obj.object_union.sphere.radius *
					obj.object_union.sphere.radius)};
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols.t1 = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols.t2 = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	hit->t = (sols.t1 < sols.t2 && sols.t1 > 0.0) ? sols.t1 : sols.t2;
	if (hit->t < 0)
		return 0;
	hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
	hit->normal = normal_sphere(obj, hit->point);
	return (1);
}

static t_quadratic get_quadratic_ellipsoid(t_line line, t_object obj)
{
	t_point3d	abc;
	t_quadratic res;

	abc = obj.object_union.ellipsoid.abc;
	res.a = ((line.v.x * line.v.x) / (abc.x * abc.x)) +
		((line.v.y * line.v.y) / (abc.y * abc.y)) +
		((line.v.z * line.v.z) / (abc.z * abc.z));
	res.b = 2 *(((line.v.x * line.o.x) / (abc.x * abc.x)) +
			((line.v.y * line.o.y) / (abc.y * abc.y)) +
			((line.v.z * line.o.z) / (abc.z * abc.z)));
	res.c = ((line.o.x * line.o.x) / (abc.x * abc.x)) +
		((line.o.y * line.o.y) / (abc.y * abc.y)) +
		((line.o.z * line.o.z) / (abc.z * abc.z)) -
		(obj.object_union.ellipsoid.radius *
		 obj.object_union.ellipsoid.radius);
	return res;
}

t_point3d		normal_ellipsoid(t_point3d point, t_object obj)
{
	t_point3d normal;
	t_point3d	abc;

	abc = obj.object_union.ellipsoid.abc;
	normal = ft_new_vec3(point.x / (abc.x * abc.x), point.y / (abc.y * abc.y),
			point.z / (abc.z * abc.z));
	return (normal);
}


int					intersect_ellipsoid(t_line line, t_object obj,
		t_hit *hit)
{
	t_quadratic	equa;
	t_quadsol	sols;
	double		radic;

	equa = get_quadratic_ellipsoid(line, obj);
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols.t1 = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols.t2 = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	hit->t = (sols.t1 < sols.t2 && sols.t1 > 0.0) ? sols.t1 : sols.t2;
	if (hit->t < 0)
		return 0;
	hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
	hit->normal = normalize(normal_ellipsoid(hit->point, obj));
	return (1);
}

t_point3d		normal_torus(t_point3d point, t_object obj)
{
	t_point3d normal;
	double a;

	a = 1.0 - (obj.object_union.torus.big_rad / sqrt(point.x * point.x + point.y * point.y));
	normal = normalize(ft_new_vec3(a * point.x, a * point.y, point.z));
	return (normal);
}

t_quartsol			noquartics()
{
	t_quartsol sol;

	sol.t1 = -1;
	sol.t2 = -1;
	sol.t3 = -1;
	sol.t4 = -1;
	return sol;
}

t_cubic				ft_quartic_as_cubic(t_quartic quartic)
{
	t_cubic res;

	res.a = quartic.b;
	res.b = quartic.c;
	res.c = quartic.d;
	res.d = quartic.e;
	res.debug = quartic.debug;
	return (res);
}

void	ft_print_complex(double complex z)
{
	printf("%f %c %fi\n", creal(z), cimag(z) >= 0 ? '+' : '-', fabs(cimag(z)));
}

void	ft_print_quartsol(t_quartsol sol)
{
	printf("\nt1: ");
	ft_print_complex(sol.t1);
	printf("t2: ");
	ft_print_complex(sol.t2);
	printf("t3: ");
	ft_print_complex(sol.t3);
	printf("t4: ");
	ft_print_complex(sol.t4);
	printf("\n");
}

void	ft_print_cubic(t_cubic cubic)
{
	printf("a: %.20Lf\n", cubic.a);
	printf("b: %.20Lf\n", cubic.b);
	printf("c: %.20Lf\n", cubic.c);
	printf("d: %.20Lf\n", cubic.d);
}

void	ft_print_quartic(t_quartic quartic)
{
	printf("a: %.20Lf\n", quartic.a);
	printf("b: %.20Lf\n", quartic.b);
	printf("c: %.20Lf\n", quartic.c);
	printf("d: %.20Lf\n", quartic.d);
	printf("e: %.20Lf\n", quartic.e);
}

long complex double		ft_cbrt(long complex double z, int i)
{
	return (cbrtl(cabsl(z)) * cexpl(I * (cargl(z) + 2 * i * M_PI) / 3.0));
}

t_quadratic			ft_cubic_as_quadratic(t_cubic cubic)
{
	t_quadratic res;

	res.a = cubic.b;
	res.b = cubic.c;
	res.c = cubic.d;
	res.debug = cubic.debug;
	return (res);
}

t_affine		ft_quadratic_as_affine(t_quadratic quadratic)
{
	t_affine res;

	res.a = quadratic.b;
	res.b = quadratic.c;
	res.debug = quadratic.debug;
	return (res);
}

int			resolve_affine(t_affine equa, t_quartsol *sols)
{
	*sols = noquartics();

	if (equa.a == 0)
		return (0);
	sols->t1 = -equa.b / equa.a;
	return (1);
}

int			resolve_quadratic(t_quadratic equa, t_quartsol *sol)
{
	if (equa.a == 0)
		return resolve_affine(ft_quadratic_as_affine(equa), sol);
	*sol = noquartics();
	equa.radic = equa.b * equa.b - 4 * equa.a * equa.c;
	if (equa.radic < 0)
		return (0);
	else
	{
		if (equa.radic == 0)
		{
			sol->t1 = - equa.b / (2 * equa.a);
			return (2);
		}
		else
		{
			sol->t1 = (-equa.b - sqrt(equa.radic)) / (2 * equa.a);
			sol->t2 = (-equa.b + sqrt(equa.radic)) / (2 * equa.a);
			return (2);
		}
	}
}

int					ft_is_zero(long double complex z)
{
	return (fabs(crealf(z)) < EPSILON4 && fabs(cimagf(z)) < EPSILON4);
}


int		resolve_cubic(t_cubic equa, t_quartsol *sol)
{
	t_auxcubic	x;
	if (fabsl(equa.a) <  0.001)
		return resolve_quadratic(ft_cubic_as_quadratic(equa), sol);
	*sol = noquartics();

//	ft_print_cubic(equa);
	equa.b /= equa.a;
	equa.c /= equa.a;
	equa.d /= equa.a;

	x.s = equa.b / 3.0;
	x.d = (equa.c / 3.0) - (x.s * x.s);
	x.e = (x.s * x.s * x.s) + ((equa.d - (x.s * equa.c)) / 2.0);
	x.sqrt = csqrt(x.e * x.e + x.d * x.d * x.d);
	x.f = -x.sqrt - x.e;
	if (ft_is_zero(x.f))
		x.f = x.sqrt - x.e;
	x.g = ft_cbrt(x.f, 0);
//	printf("cbrt 0	puiss 3: ");
//	ft_print_complex(cpow(x.g, 3));
	sol->t1 = x.g - (x.d / x.g) - x.s;
	x.g = ft_cbrt(x.f, 1);
//	printf("cbrt 1	puiss 3: ");
//	ft_print_complex(cpow(x.g, 3));
	sol->t2 = x.g - (x.d / x.g) - x.s;
	x.g = ft_cbrt(x.f, 2);
//	printf("cbrt 2	puiss 3: ");
//	ft_print_complex(cpow(x.g, 3));
	sol->t3 = x.g - (x.d / x.g) - x.s;
	//	if (sol.t1 != sol.t1)
//	{
//		printf("nan cubic\n");
		printf("f: ");
		ft_print_complex(x.f);
		printf("sqrt: ");
		ft_print_complex(x.sqrt);
		printf("s: ");
		ft_print_complex(x.s);
		printf("d: ");
		ft_print_complex(x.d);
		printf("e: ");
		ft_print_complex(x.e);
		printf("g: ");
		ft_print_complex(x.g);
//		ft_print_quartsol(sol);
//		exit(1);
//	}
	return (3);
}


/*
int			resolve_cubic(t_cubic equa, t_quartsol *sol)
{
	t_auxcubic	x;
	if (fabsl(equa.a) < 0.01)
		return resolve_quadratic(ft_cubic_as_quadratic(equa), sol);
	*sol = noquartics();

//	equa.b /= equa.a;
//	equa.c /= equa.a;
//	equa.d /= equa.a;

	x.f = (((3 * equa.c) / equa.a) - ((equa.b * equa.b) / (equa.a * equa.a))) / 3.0;
	x.g = (((2 * equa.b * equa.b * equa.b) / (equa.a * equa.a * equa.a)) - ((9 * equa.b * equa.c) / (equa.a * equa.a)) +  ((27 * equa.d) / equa.a)) / 27.0;
	x.h = ((x.g * x.g) / 4.0) + (x.f * x.f * x.f) / 27.0;

//	printf("H:%Lf\n", x.h);
	if (creal(x.h) < 0)
	{
		x.i = sqrt(((x.g * x.g) / (4.0)) - x.h);
		x.j = cbrt(x.i);
		x.k = acos(-(x.g / (2 * x.i)));
		x.l = x.j * (-1);
		x.m = cos(x.k / 3);
		x.n = sqrt(3) * sin(x.k / 3);
		x.p = -(equa.b) / (3 * equa.a);
		sol->t1 = 2 * x.j * cos(x.k / 3.0) + x.p;
		sol->t2 = x.l * (x.m + x.n) + x.p;
		sol->t3 = x.l * (x.m - x.n) + x.p;
		return (3);
	}
	else if (x.h == 0)
	{
		sol->t1 = -cbrt(equa.d / equa.a);
		sol->t2 = sol->t1;
		sol->t3 = sol->t1;
		return (3);
	}
	else
	{
		x.r = - (x.g / 2.0) + sqrt(x.h);
		x.s = cbrt(x.r);
		x.t = - (x.g / 2.0) - sqrt(x.h);
		x.u = cbrt(x.r);
		sol->t1 = x.s + x.u - ((equa.b) / (3 * equa.a));
		sol->t2 = (-(x.s + x.u) / 2.0) - (equa.b / (3 * equa.a)) + I *
		   ((x.s - x.u) * sqrt(3) / 2);
		sol->t3 = (-(x.s + x.u) / 2.0) - (equa.b / (3 * equa.a)) - I *
		   ((x.s - x.u) * sqrt(3) / 2);
		return (3);
	}
}
*/
int				resolve_quartic(t_quartic equa, t_quartsol *sols) //DOWNLOAD
{
	t_quartsol sol;
	t_auxquartic x;

//	x.b2 = equa.b * equa.b;
//	x.b3 = equa.b * equa.b * equa.b;
//	x.b4 = equa.b * equa.b * equa.b * equa.b;

	if (fabsl(equa.a) < EPSILON2 )
		return resolve_cubic(ft_quartic_as_cubic(equa), sols);

	equa.b /= equa.a;
	equa.c /= equa.a;
	equa.d /= equa.a;
	equa.e /= equa.a;

	x.alpha = - ((3.0 * equa.b * equa.b) / (8.0)) + (equa.c);
	x.beta = ((equa.b * equa.b * equa.b) / (8.0)) - ((equa.b * equa.c) / (2.0)) + (equa.d);
	x.gamma = - ((3.0 * equa.b * equa.b * equa.b * equa.b) / (256.0)) + ((equa.c * equa.b * equa.b) / (16.0)) -
		((equa.b * equa.d) / (4.0)) + (equa.e);
	x.t = -(equa.b / (4.0));
	if (ft_is_zero(x.beta))
	{
		x.rad = csqrt((x.alpha * x.alpha) - 4 * x.gamma);
		x.r1 = csqrt((-x.alpha + x.rad) / 2.0);
		x.r2 = csqrt((-x.alpha - x.rad) / 2.0);
		sol.t1 = x.t + x.r1;
		sol.t2 = x.t - x.r1;
		sol.t3 = x.t + x.r2;
		sol.t4 = x.t - x.r2;
	}
	x.p = - ((x.alpha * x.alpha) / 12.0 ) - x.gamma;
	x.q = - ((x.alpha * x.alpha * x.alpha) / 108.0) +
		((x.alpha * x.gamma) / 3.0) - ((x.beta * x.beta) / 8.0);

	x.r = - (x.q / 2.0) + csqrt(((x.q * x.q) / 4.0) + ((x.p * x.p * x.p) / 27.0));

	x.u = cpowl(x.r, 1.0 / 3.0);
	x.y = -((5.0 * x.alpha) / 6.0) + x.u;
	if (ft_is_zero(x.u))
		x.y -= cpowl(x.q, 1.0 / 3.0);
	else
		x.y -= (x.p / (3.0 * x.u));

	x.w = csqrtl(x.alpha + 2 * x.y);
	x.r1 = csqrtl(-((3.0 * x.alpha) + (2.0 * x.y) + ((2.0 * x.beta) / x.w)));
	x.r2 = csqrtl(-((3.0 * x.alpha) + (2.0 * x.y) - ((2.0 * x.beta) / x.w)));
	sols->t1 = x.t + ((x.w - x.r1) / 2.0);
	sols->t2 = x.t + ((x.w + x.r1) / 2.0);
	sols->t3 = x.t + ((-x.w - x.r2) / 2.0);
	sols->t4 = x.t + ((-x.w + x.r2) / 2.0);
	if (equa.debug)
	{
		printf("alpha: ");
		ft_print_complex(x.alpha);
		printf("beta: ");
		ft_print_complex(x.beta);
		printf("gamma: ");
		ft_print_complex(x.gamma);
		printf("y: ");
		ft_print_complex(x.y);
		printf("u: ");
		ft_print_complex(x.u);
		printf("r1: ");
		ft_print_complex(x.r1);
		printf("r2: ");
		ft_print_complex(x.r2);
		printf("w: ");
		ft_print_complex(x.w);
	}
	return (4);
}

double				get_closer_intersection_quartic(t_quartsol sol)
{
	double res;

	res = -1;
	if (fabsl(cimagl(sol.t1)) < EPSILON3 && creall(sol.t1) > 0 && (creall(sol.t1) < res || res == -1))
		res = creall(sol.t1);
	if (fabsl(cimagl(sol.t2)) < EPSILON3 && creall(sol.t2) > 0 && (creall(sol.t2) < res || res == -1))
		res = creall(sol.t2);
	if (fabsl(cimagl(sol.t3)) < EPSILON3 && creall(sol.t3) > 0 && (creall(sol.t3) < res || res == -1))
		res = creall(sol.t3);
	if (fabsl(cimagl(sol.t4)) < EPSILON3 && creall(sol.t4) > 0 && (creall(sol.t4) < res || res == -1))
		res = creall(sol.t4);
	return (res);
}

double				nb_quartic_sols(t_quartsol sol)
{
	double res;

	res = 0;
	if (fabsl(cimagl(sol.t1)) < EPSILON3 && creall(sol.t1) > 0)
		res++;
	if (fabsl(cimagl(sol.t2)) < EPSILON3 && creall(sol.t2) > 0)
		res++;
	if (fabsl(cimagl(sol.t3)) < EPSILON3 && creall(sol.t3) > 0)
		res++;
	if (fabsl(cimagl(sol.t4)) < EPSILON3 && creall(sol.t4) > 0)
		res++;
	return (res);
}

t_quartic			get_quartic_torus(t_line line, t_object obj)
{
	t_auxtorus x;
	t_quartic res;
	double a;
	double b;

	a = obj.object_union.torus.big_rad;
	b = obj.object_union.torus.small_rad;
	x.g = 4 * a * a * (line.v.x * line.v.x + line.v.y * line.v.y);
	x.h = 8 * a * a * (line.o.x * line.v.x + line.o.y * line.v.y);
	x.i = 4 * a * a * (line.o.x * line.o.x + line.o.y * line.o.y);
	x.j = ft_dot_product(line.v, line.v);
	x.k = 2 * ft_dot_product(line.o, line.v);
	x.l = ft_dot_product(line.o, line.o) + (a * a) - (b * b);
	res.a = x.j * x.j;
	res.b = 2 * x.j * x.k;
	res.c = (2 * x.j * x.l) + (x.k * x.k) - x.g;
	res.d = (2 * x.k * x.l) - x.h;
	res.e = (x.l * x.l) - x.i;
	return (res);
}

void			ft_init_aux(t_auxquart_init *g, t_line line)
{
	g->ox2 = line.o.x * line.o.x;
	g->ox3 = g->ox2 * line.o.x;
	g->ox4 = g->ox2 * g->ox2;
	g->vx2 = line.v.x * line.v.x;
	g->vx3 = g->vx2 * line.v.x;
	g->vx4 = g->vx2 * g->vx2;
	g->oy2 = line.o.y * line.o.y;
	g->oy3 = g->oy2 * line.o.y;
	g->oy4 = g->oy2 * g->oy2;
	g->vy2 = line.v.y * line.v.y;
	g->vy3 = g->vy2 * line.v.y;
	g->vy4 = g->vy2 * g->vy2;
	g->oz2 = line.o.z * line.o.z;
	g->oz3 = g->oz2 * line.o.z;
	g->oz4 = g->oz2 * g->oz2;
	g->vz2 = line.v.z * line.v.z;
	g->vz3 = g->vz2 * line.v.z;
	g->vz4 = g->vz2 * g->vz2;
}

t_quartic			get_quartic_goursat(t_line line, t_object obj)
{
	t_auxquart_init g;
	t_quartic res;
	double a;
	double b;

	a = obj.object_union.goursat.a;
	b = obj.object_union.goursat.b;
	ft_init_aux(&g, line);
	res.a = g.vx4 + g.vy4 + g.vz4;
	res.b = 4 * (line.o.x * g.vx3 + line.o.y * g.vy3 + line.o.z * g.vz3);
	res.c = (6 *(g.ox2 * g.vx2 + g.oy2 * g.vy2 + g.oz2 * g.vz2)) - a *
		(g.vx2 + g.vy2 + g.vz2);
	res.d = (4 * (g.ox3 * line.v.x + g.oy3 * line.v.y + g.oz3 * line.v.z))
		- 2 * a * (ft_dot_product(line.o, line.v));
	res.e = g.ox4 + g.oy4 + g.oz4 - (a * (g.ox2 + g.oy2 + g.oz2)) + b;
	return (res);
}

int					intersect_torus(t_line line, t_object obj,
		t_hit *hit)
{
	t_quartic equa;
	t_quartsol sols;

	equa = get_quartic_torus(line, obj);
	equa.debug = 0;
	if (line.x == 0 && line.y == VRES / 2)
	{
		equa.debug = 1;
		resolve_quartic(equa, &sols);
	hit->t = get_closer_intersection_quartic(sols);
		if (hit->t > 0)
		{
			ft_printf(RED"on intersect\n");
			ft_print_quartic(equa);
			ft_print_quartsol(sols);
			ft_printf(EOC);
		}
		else
		{
			ft_printf("on intersect AP\n");
			ft_print_quartic(equa);
			ft_print_quartsol(sols);
		}
	}
	else
	{
		resolve_quartic(equa, &sols);
	hit->t = get_closer_intersection_quartic(sols);
	}
	/*
	if (line.oldv.x == 0 && line.oldv.y == 0)
	{
		if (hit->t > 0)
		{
			printf("on a trouve une sol");
			ft_print_quartic(equa);
			ft_print_quartsol(sols);
		}
		else
		{
			printf(RED"on a pas trouve de sol");
			ft_print_quartic(equa);
			ft_print_quartsol(sols);
			printf(EOC);
		}
	}
	*/
	if (hit->t < 0)
		return 0;
	else
	{
		hit->point = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
		hit->normal = normal_torus(hit->point, obj);
		return (1);
	}
}

t_point3d		normal_goursat(t_point3d point, t_object obj)
{
	t_point3d normal;
	double a;

	a = obj.object_union.goursat.a;
	normal = normalize(ft_new_vec3(4 * (point.x * point.x * point.x) - (2 * a * point.x),
		   		4 * (point.y * point.y * point.y) - (2 * a * point.y),
					4 * (point.z * point.z * point.z) - (2 * a * point.z)));

	return (normal);
}


int					intersect_goursat(t_line line, t_object obj,
		t_hit *hit)
{
	t_quartic equa;
	t_quartsol sols;

	equa = get_quartic_goursat(line, obj);
	resolve_quartic(equa, &sols);
	hit->t = get_closer_intersection_quartic(sols);
	if (hit->t < 0)
		return 0;
	else
	{
		hit->point = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
		hit->normal = normal_goursat(hit->point, obj);
		return (1);
	}
}

t_quartic			get_quartic_lemniscate(t_line line, t_object obj)
{
	t_quartic res;
	t_auxquart_init g;

	(void)obj;
	ft_init_aux(&g, line);
	res.a = g.vx4;
	res.b = 4 * line.o.x * g.vx3;
	res.c = (6 * (g.ox2 * g.vx2)) + g.vy2 + g.vz2 - g.vx2;
	res.d = (4 * (g.ox3 * line.v.x)) + 2 * (line.o.y * line.v.y + line.o.z * line.v.z - line.o.x * line.v.x);
	res.e = g.ox4 + g.oy2 + g.oz2 - g.ox2;
	return (res);
}
/*
void				test()
{
	t_quadratic quad;
	t_quartsol sol;

	quad.a = 1;
	quad.b = 3;
	quad.c = -4;
	sol = resolve_quadratic(quad);
	ft_print_quartsol(sol);
	exit(1);
}

void			test2()
{
	t_quartic quartic;
	t_quartsol sol;
	quartic.a = 0;
	quartic.b = 1;
	quartic.c = -6;
	quartic.d = 11;
	quartic.e = -6;
	sol = resolve_quartic(quartic);
	double res = get_closer_intersection_quartic(sol);
	(void) res;
	ft_print_quartsol(sol);
	exit(1);
}

void			test3()
{
	t_cubic cub;
	t_quartsol sol;

	cub.a = 1;
	cub.b = -6;
	cub.c = 11;
	cub.d = -6;
	sol = resolve_cubic(cub);
	ft_print_quartsol(sol);
	exit(1);
}

void			test5()
{
	t_cubic cub;
	t_quartsol sol;

	cub.a = 0.0000000000012;
	cub.b = 1.0000000339550;
	cub.c = -5.0063991732061;
	cub.d = 8.6915127712281;

	ft_print_cubic(cub);
	sol = resolve_cubic(cub);
	ft_print_quartsol(sol);
	exit(1);
}

void		test4()
{
	t_quartic quartic;
	t_quartsol sol;
	quartic.a = 0.0000000000001;
	quartic.b = 0.0000000004919;
	quartic.c = 1.0000001225418;
	quartic.d = 1.0626067575294;
	quartic.e = 0.2207295970682;
	ft_print_quartic(quartic);
	sol = resolve_quartic(quartic);
	double res = get_closer_intersection_quartic(sol);
	(void) res;
	ft_print_quartsol(sol);
	exit(1);
}

void			ultimate_test_cubic()
{
	t_cubic cub;
	t_quartsol sol;

	cub.a = -0.00000049765903675543;
	cub.b = 1.07065052337394761572;
	cub.c = -4490.96082606171603401890;
	cub.d = 105479467.61827105283737182617;

	ft_print_cubic(cub);
	sol = resolve_cubic(cub);
	ft_print_quartsol(sol);
	exit(1);
}
*/
t_point3d	normal_lemniscate(t_point3d point)
{
	t_point3d normal;

	normal = normalize(ft_new_vec3(
		4 * point.x * point.x * point.x - 2 * point.x * point.x,
			2 * point.y,
				2 * point.z));

	return (normal);
}

int					intersect_lemniscate(t_line line, t_object obj,
		t_hit *hit)
{
	t_quartic equa;
	t_quartsol sols;

//	ultimate_test_cubic();
	equa = get_quartic_lemniscate(line, obj);
	resolve_quartic(equa, &sols);
	hit->t = get_closer_intersection_quartic(sols);
	if (line.x == 0 && line.y == VRES / 2)
	{
		if (hit->t > 0)
		{
			ft_printf(RED"on intersect\n");
			ft_print_quartic(equa);
			ft_print_quartsol(sols);
			ft_printf(EOC);
		}
		else
		{
			ft_printf("on intersect AP\n");
			ft_print_quartic(equa);
			ft_print_quartsol(sols);
		}
	}
	if (hit->t < 0)
		return 0;
	else
	{
		hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
	//	hit->normal  = ft_new_vec3(0,1,0);
		hit->normal  = normal_lemniscate(hit->point);
		return (1);
	}
}

t_quartic			get_quartic_roman(t_line line)
{
	t_quartic res;
	t_auxquart_init g;

	ft_init_aux(&g, line);
	res.a = g.vx2 * g.vy2 + g.vy2 * g.vz2 + g.vx2 * g.vz2;
	res.b = 2 * (line.o.x * line.v.x * g.vy2 + line.o.y * line.v.y * g.vx2 +
			line.o.y * line.v.y * g.vz2 + line.o.z * line.v.z * g.vy2
				+ line.o.x * line.v.x * g.vz2 + line.o.z * line.v.z * g.vx2)
					+ line.v.x * line.v.y * line.v.z;
	res.c = g.ox2 * g.vy2 + g.oy2 * g.vx2 + g.oy2 * g.vz2 + g.oz2 * g.vy2
			+ g.ox2 * g.vz2 + g.oz2 * g.vx2
			+ 4 * (line.o.x * line.v.x * line.o.y * line.v.y +
					line.o.y * line.v.y * line.o.z * line.v.z +
					line.o.x * line.v.x * line.o.z * line.v.z)
			+ (line.o.x * line.v.y * line.v.z + line.o.y * line.v.x * line.v.z
			+ line.o.z * line.v.x * line.v.y);
	res.d = (line.v.x * line.o.y * line.o.z + line.v.y * line.o.x * line.o.z +
				line.v.z * line.o.x * line.o.y)
		+ 2 * (g.ox2 * line.o.y * line.v.y + g.oy2 * line.o.x * line.v.x +
				g.oy2 * line.o.z * line.v.z + g.oz2 * line.o.y * line.v.y +
				 g.ox2 * line.o.z * line.v.z + g.oz2 * line.o.x * line.v.x);
	res.e = line.o.x * line.o.y * line.o.z + g.ox2 * g.oy2 + g.oy2 * g.oz2 +
		g.ox2 * g.oz2;
	return (res);
}

t_point3d	normal_roman(t_point3d point)
{
	t_point3d normal;

	normal = normalize(ft_new_vec3(
		2 * point.x * point.y * point.y +
	   	2 * point.x * point.z * point.z +
	   	point.y * point.z,

		2 * point.y * point.x * point.x +
		2 * point.y * point.z * point.z +
		point.x * point.z,

		2 * point.z * point.y * point.y +
		2 * point.z * point.x * point.x +
		point.x * point.y));

	return (normal);
}

void				transform_sol(t_quartsol *sols)
{
	sols->t1 = I * cimagl(sols->t1) + sin(creall(sols->t1));
	sols->t2 = I * cimagl(sols->t2) + sin(creall(sols->t2));
	sols->t3 = I * cimagl(sols->t3) + sin(creall(sols->t3));
	sols->t4 = I * cimagl(sols->t4) + sin(creall(sols->t4));
}

int					intersect_roman(t_line line, t_object obj,
		t_hit *hit)
{
	t_quartic equa;
	t_quartsol sols;
	(void)obj;
	equa = get_quartic_roman(line);
	equa.debug = 0;
	resolve_quartic(equa, &sols);
	hit->t = get_closer_intersection_quartic(sols);
	if (hit->t < 0)
		return 0;
	else
	{
		hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
		hit->normal = normal_roman(hit->point);
		//	hit->normal = ft_new_vec3( 0, 0 ,1);

		if (line.x == 0 && line.y == VRES / 2)
		{
			printf("point:\n");
			ft_print_point3d(hit->point);
			printf("normal:\n");
			ft_print_point3d(hit->normal);
		}
		return (1);
	}
}

t_quartic			get_quartic_piriform(t_line line, t_object obj)
{
	t_quartic res;
	t_auxquart_init g;

	(void)obj;
	ft_init_aux(&g, line);
	res.a = g.vy4;
	res.b = (4 * line.o.y * g.vy3) - g.vy3;
	res.c = (6 * (g.oy2 * g.vy2)) - (3 * line.o.y * g.vy2) + g.vz2 + g.vx2;
	res.d = (4 * (g.oy3 * line.v.y)) - (3 * g.oy2 * line.v.y) + 2 * (line.o.z * line.v.z + line.o.x * line.v.x);
	res.e = g.oy4 - g.oy3 + g.oz2 + g.ox2;
	return (res);
}

t_point3d		normal_piriform(t_point3d point, t_object obj)
{
	t_point3d normal;
	(void)obj;
	normal = normalize(ft_new_vec3(2 * point.x,
		   		4 * (point.y * point.y * point.y) - (3 * point.y * point.y),
					 (2 * point.z)));

	return (normal);
}

int					intersect_piriform(t_line line, t_object obj,
		t_hit *hit)
{
	t_quartic equa;
	t_quartsol sols;

	int gotin = 0;
	int nb_potential_sols;
	int quartic_degree;
	equa = get_quartic_piriform(line, obj);
	equa.debug = 0;
		quartic_degree = resolve_quartic(equa, &sols);
	nb_potential_sols = nb_quartic_sols(sols);
	hit->t = get_closer_intersection_quartic(sols);

	if (line.x == 0 && line.y == VRES / 2)
	{
		if (hit->t > 0)
		{
			gotin = 1;
			if (nb_potential_sols == 1)
			{
				ft_printf(RED"on intersect 1 fois!!\n");
				ft_print_quartic(equa);
				ft_print_quartsol(sols);
				ft_printf(EOC);
			}
			else
			{
				ft_printf(CYAN"on intersect %d fois!!\n", nb_potential_sols);
				ft_print_quartic(equa);
				ft_print_quartsol(sols);
				ft_printf(EOC);
			}
			ft_printf("quartic degree: %d!\n", quartic_degree);
			printf("premiere intersection a t = %f\n", hit->t);
		}
		else
		{
			ft_printf("on intersect AP\n");
			ft_print_quartic(equa);
			ft_print_quartsol(sols);
		}
	}
	if (hit->t < 0)
		return 0;
	else
	{
		hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
		hit->normal = normal_piriform(hit->point, obj);
	//	hit->normal = ft_new_vec3(0, 0, 1);
		if (gotin)
		{
			printf("point:\n");
			ft_print_point3d(hit->point);
			printf("normal:\n");
			ft_print_point3d(hit->normal);
		}
		return (1);
	}
}

static t_auxcone	getauxcone(t_line line, t_object obj)
{
	t_auxcone	aux;

	(void) line;
	aux.sqcos = cos(obj.object_union.cone.angle) *
		cos(obj.object_union.cone.angle);
	aux.sqsin = sin(obj.object_union.cone.angle) *
		sin(obj.object_union.cone.angle);
	return (aux);
}

int					intersect_cone(t_line line, t_object obj,
		t_hit *hit)
{
	t_auxcone	aux;
	t_quadratic	equa;
	t_quadsol	sols;
	double		radic;

	aux = getauxcone(line, obj);
	equa.a = aux.sqcos * ((line.v.y * line.v.y) + (line.v.z * line.v.z))
		- aux.sqsin * (line.v.x * line.v.x);
	equa.b = 2 * (aux.sqcos * ((line.o.y * line.v.y) + (line.o.z * line.v.z))
			- aux.sqsin * (line.o.x * line.v.x));
	equa.c = aux.sqcos * ((line.o.y * line.o.y) + (line.o.z * line.o.z))
		- aux.sqsin * (line.o.x * line.o.x);
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols.t1 = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols.t2 = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	hit->t = (sols.t1 < sols.t2 && sols.t1 > 0.0) ? sols.t1 : sols.t2;
	if (hit->t < 0)
		return 0;
	hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
//	hit->normal.x = (hit->point.x > 0 ? -1 : 1) *
//		sqrt(hit->point.z * hit->point.z + hit->point.y * hit->point.y) *
//			tan(obj.object_union.cone.angle);
//	hit->normal.y = hit->point.y;
//	hit->normal.z = hit->point.z;
	hit->normal = normal_cone(obj, hit->point);
	return (1);
}

int					intersect_plane(t_line line, t_object obj,
		t_hit *hit)
{
	(void)obj;
	if (line.v.y < EPSILON && line.v.y > -EPSILON)
		return (0);
	hit->t = -line.o.y / line.v.y;
	hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
//	hit->normal = ft_new_vec3(0, (line.v.y > 0 ) ? 1 : -1, 0);
	hit->normal = normal_plane(obj, hit->point, line);
	return (1);
}

int					intersect_cylinder(t_line line, t_object obj,
		t_hit *hit)
{
	t_quadratic	equa;
	t_quadsol	sols;
	double		radic;

	equa = (t_quadratic){.a = (line.v.z * line.v.z) + (line.v.y * line.v.y),
		.b = 2 * ((line.o.z * line.v.z) + (line.o.y * line.v.y)),
		.c = (line.o.z * line.o.z) + (line.o.y * line.o.y) -
			(obj.object_union.cylinder.radius * obj.object_union.cylinder.radius)};
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols.t1 = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols.t2 = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	hit->t = (sols.t1 < sols.t2 && sols.t1 > 0.0) ? sols.t1 : sols.t2;
	if (hit->t < 0)
		return 0;
	hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
//	hit->normal = normalize(ft_new_vec3(0, hit->point.y, hit->point.z));
	hit->normal = normal_cylinder(obj, hit->point);
	return (1);
}
