/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 01:01:52 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/18 04:08:55 by ldedier          ###   ########.fr       */
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
	hit->normal = normalize(hit->point);
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

t_quartsol			noquartics(void)
{
	t_quartsol sols;

	sols.t1 = -1;
	sols.t2 = -1;
	sols.t3 = -1;
	sols.t4 = -1;

	return (sols);
}

t_quartsol			resolve_quartic(t_quartic equa)
{
	t_quartsol sol;
	t_auxquartic x;

	sol = noquartics();
	equa.b /= equa.a;
	equa.c /= equa.a;
	equa.d /= equa.a;
	equa.e /= equa.a;

	x.b2 = equa.b * equa.b;
	x.b3 = x.b2 * equa.b;
	x.b4 = x.b2 * x.b2;
	x.alpha = - ((3.0 * x.b2) / 8.0) + equa.c;
	x.beta = (x.b3 / 8.0) - (equa.b * equa.c / 2.0) + equa.d;
	x.gamma = - (3.0 * equa.b4 / 256.0) + (equa.c * x.b2 / 16.0) - 
		(equa.b * equa.d / 4.0) + equa.e;
	
	x.t = -(equa.b / 4.0); 
	x.alpha2 = x.alpha * x.alpha;
	if (x.beta == 0)
	{
		if (x.alpha2 - 4 * x.gamma < 0)
			return noquartics();
		x.rad = sqrt(x.alpha2 - 4 * x.gamma);
		x.r1 = sqrt((-x.alpha + x.rad) / 2.0);
		x.r2 = sqrt((-x.alpha - x.rad) / 2.0);

		if (x.rad - x.alpha > 0)
		{
			sol.t1 = x.t + x.r1;
			sol.t2 = x.t - x.r1;
		}
		if (-x.rad - x.alpha > 0)
		{
			sol.t3 = x.t + x.r2;
			sol.t4 = x.t - x.r2;
		}
		return sol;
	}
	x.p = - ((x.alpha * x.alpha) / 12.0 ) - x.gamma;
	x.q = - ((x.alpha * x.alpha * x.alpha) / 108.0) +
		((x.alpha * x.gamma) / 3.0) - ((x.beta * x.beta) / 8.0);

	if (((x.q * x.q) / 4.0) + ((x.p * x.p *x.p) / 27.0) < 0)
		return noquartics();

	x.r = - (x.q / 2.0) + sqrt(((x.q * x.q) / 4.0) + ((x.p * x.p *x.p) / 27.0));
	x.u = cbrt(x.r);

	x.y = -((5.0 * x.alpha) / 6.0);
	if (x.u == 0)
		x.y -= cbrt(x.q);
	else
		x.y -= (x.p / (3.0 * x.u));

	if (x.alpha + 2 * x.y < 0)
		return noquartics();

	x.w = sqrt(x.alpha + 2 * x.y);
	x.r1 = sqrt(-(3.0 * x.alpha + 2.0 * x.y + ((2.0 * x.beta) / x.w)));
	x.r2 = sqrt(-(3.0 * x.alpha + 2.0 * x.y - ((2.0 * x.beta) / x.w)));

//	if (-(3.0 * x.alpha + 2.0 * x.y + ((2.0 * x.beta) / x.w)) > 0)
//	{
		sol.t1 = x.t + ((x.w - x.r1) / 2.0);
		sol.t2 = x.t + ((x.w + x.r1) / 2.0);
//	}
//	if(-(3.0 * x.alpha + 2.0 * x.y - ((2.0 * x.beta) / x.w)) > 0)
//	{
		sol.t3 = x.t + ((-x.w - x.r2) / 2.0);
		sol.t4 = x.t + ((-x.w + x.r2) / 2.0);
//	}
	return (sol);
}

double				get_closer_intersection_quartic(t_quartsol sol)
{
	double res;

	res = -1;
	if (sol.t1 > 0 && (sol.t1 < res || res == -1))
		res = sol.t1;
	if (sol.t2 > 0 && (sol.t2 < res || res == -1))
		res = sol.t2;
	if (sol.t3 > 0 && (sol.t3 < res || res == -1))
		res = sol.t2;
	if (sol.t4 > 0 && (sol.t4 < res || res == -1))
		res = sol.t2;
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

int					intersect_torus(t_line line, t_object obj,
		t_hit *hit)
{
	t_quartic equa;
	t_quartsol sols;

	equa = get_quartic_torus(line, obj);
	sols = resolve_quartic(equa);
	hit->t = get_closer_intersection_quartic(sols);
	if (hit->t < 0)
		return 0;
	else
	{
		hit->point  = ft_point3d_add(ft_point3d_scalar(line.v, hit->t), line.o);
		hit->normal  = normal_torus(hit->point, obj);
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
	hit->normal.x = (hit->point.x > 0 ? -1 : 1) *
		sqrt(hit->point.z * hit->point.z + hit->point.y * hit->point.y) *
		tan(obj.object_union.cone.angle);
	hit->normal.y = hit->point.y;
	hit->normal.z = hit->point.z;
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
	hit->normal = ft_new_vec3(0, (line.v.y > 0 ) ? 1 : -1, 0);

	/*
	   double	den;
	   double	sol;

	   den = dotprod(line.v, obj.r);
	   if (den < EPSILON && den > -EPSILON)
	   return (0);
	   sol = dotprod(newvector(line.o, obj.o), obj.r) / den;
	   (*hitpoint).x = line.o.x + line.v.x * sol;
	   (*hitpoint).y = line.o.y + line.v.y * sol;
	   (*hitpoint).z = line.o.z + line.v.z * sol;
	   */
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
	hit->normal = normalize(ft_new_vec3(0, hit->point.y, hit->point.z));
	return (1);
}
