/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 01:01:52 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/13 16:11:31 by ldedier          ###   ########.fr       */
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
