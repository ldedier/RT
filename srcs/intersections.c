/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 01:01:52 by lcavalle          #+#    #+#             */
/*   Updated: 2018/04/29 05:38:21 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** quadratic equation. simpliefied a, b and c. also simplified formula
** (wikipedia line-sphere intersection)
*/

int					intersect_sphere(t_line line, t_object obj,
		t_point3d *hitpoint)
{
	t_point3d	tmpvec;
	t_quadratic	equa;
	t_quadsol	sols;
	double		t;
	double		radic;

	(*hitpoint) = translate_vec(line.o, line.v, -EPSILON);
	tmpvec = newvector(obj.o, line.o);
	equa = (t_quadratic){.a = 1, .b = dotprod(tmpvec, line.v),
		.c = dotprod(tmpvec, tmpvec) - obj.s.x * obj.s.x};
	radic = equa.b * equa.b - equa.c;
	if (radic < 0.0)
		return (0);
	sols.t1 = -equa.b + sqrt(radic);
	sols.t2 = -equa.b - sqrt(radic);
	t = (sols.t1 < sols.t2 && sols.t1 > 0.0) ? sols.t1 : sols.t2;
	(*hitpoint).x = line.o.x + line.v.x * t;
	(*hitpoint).y = line.o.y + line.v.y * t;
	(*hitpoint).z = line.o.z + line.v.z * t;
	return (1);
}

static t_auxcone	getauxcone(t_line line, t_object obj)
{
	t_auxcone	aux;

	aux.dv = dotprod(line.v, obj.r);
	aux.colo = newvector(obj.o, line.o);
	aux.slvdv = scale(obj.r, aux.dv);
	aux.slvdvv = newvector(aux.slvdv, line.v);
	aux.colod = dotprod(aux.colo, obj.r);
	aux.sdcolod = scale(obj.r, aux.colod);
	aux.sdcolo2d = newvector(aux.sdcolod, aux.colo);
	aux.sqcos = cos(obj.s.x) * cos(obj.s.x);
	aux.sqsin = sin(obj.s.x) * sin(obj.s.x);
	return (aux);
}

int					intersect_cone(t_line line, t_object obj,
		t_point3d *hitpoint)
{
	t_auxcone	aux;
	t_quadratic	equa;
	t_quadsol	sols;
	double		t;
	double		radic;

	(*hitpoint) = translate_vec(line.o, line.v, -EPSILON);
	aux = getauxcone(line, obj);
	equa.a = dotprod(aux.slvdvv, aux.slvdvv) * aux.sqcos -
		aux.dv * aux.dv * aux.sqsin;
	equa.b = dotprod(aux.slvdvv, aux.sdcolo2d) * aux.sqcos * 2 -
		aux.sqsin * 2 * aux.dv * aux.colod;
	equa.c = dotprod(aux.sdcolo2d, aux.sdcolo2d) * aux.sqcos -
		aux.sqsin * aux.colod * aux.colod;
	radic = equa.b * equa.b - 4 * equa.a * equa.c;
	if (radic < 0.0)
		return (0);
	sols.t1 = (-equa.b + sqrt(radic)) / (2 * equa.a);
	sols.t2 = (-equa.b - sqrt(radic)) / (2 * equa.a);
	t = (sols.t1 < sols.t2 && sols.t1 > 0.0) ? sols.t1 : sols.t2;
	(*hitpoint).x = line.o.x + line.v.x * t;
	(*hitpoint).y = line.o.y + line.v.y * t;
	(*hitpoint).z = line.o.z + line.v.z * t;
	return (1);
}

int					intersect_plane(t_line line, t_object obj,
		t_point3d *hitpoint)
{
	double	den;
	double	sol;

	den = dotprod(line.v, obj.r);
	if (den < EPSILON && den > -EPSILON)
		return (0);
	sol = dotprod(newvector(line.o, obj.o), obj.r) / den;
	(*hitpoint).x = line.o.x + line.v.x * sol;
	(*hitpoint).y = line.o.y + line.v.y * sol;
	(*hitpoint).z = line.o.z + line.v.z * sol;
	return (1);
}

int					intersect_cylinder(t_line line, t_object obj,
		t_point3d *hitpoint)
{
	t_auxcyl	aux;
	t_quadratic	equa;
	t_quadsol	sols;
	double		t;
	double		radic;

	(*hitpoint) = translate_vec(line.o, line.v, -EPSILON);
	aux.colo = newvector(obj.o, line.o);
	aux.ddv = newvector(scale(obj.r, dotprod(line.v, obj.r)), line.v);
	aux.scolol = scale(obj.r, dotprod(aux.colo, obj.r));
	aux.scolol2 = newvector(aux.scolol, aux.colo);
	equa = (t_quadratic){.a = dotprod(aux.ddv, aux.ddv),
		.b = 2 * dotprod(aux.ddv, aux.scolol2),
		.c = dotprod(aux.scolol2, aux.scolol2) - obj.s.x * obj.s.x};
	radic = equa.b * equa.b - 4 * equa.a * equa.c;
	if (radic < 0.0)
		return (0);
	sols.t1 = (-equa.b + sqrt(radic)) / (2 * equa.a);
	sols.t2 = (-equa.b - sqrt(radic)) / (2 * equa.a);
	t = (sols.t1 < sols.t2 && sols.t1 > 0.0) ? sols.t1 : sols.t2;
	(*hitpoint).x = line.o.x + line.v.x * t;
	(*hitpoint).y = line.o.y + line.v.y * t;
	(*hitpoint).z = line.o.z + line.v.z * t;
	return (1);
}
