/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 01:01:52 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 09:16:52 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					intersect_sphere(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	t_quadratic	equa;
	double		radic;

	equa = (t_quadratic){.a = dotprod(line.v, line.v), .b = 2 *
		dotprod(line.o, line.v),
			.c = dotprod(line.o, line.o) - (obj.object_union.sphere.radius *
					obj.object_union.sphere.radius)};
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols[0] = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols[1] = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	return (2);
}

static t_auxcone	getauxcone(t_line line, t_object obj)
{
	t_auxcone	aux;

	(void)line;
	aux.sqcos = cos(obj.object_union.cone.angle) *
		cos(obj.object_union.cone.angle);
	aux.sqsin = sin(obj.object_union.cone.angle) *
		sin(obj.object_union.cone.angle);
	return (aux);
}

int					intersect_cone(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	t_auxcone	aux;
	t_quadratic	equa;
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
	sols[0] = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols[1] = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	return (2);
}

int					intersect_plane(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	(void)obj;
	if (line.v.y < EPSILON && line.v.y > -EPSILON)
		return (0);
	sols[0] = -line.o.y / line.v.y;
	return (1);
}

int					intersect_cylinder(t_line line, t_object obj,
			double sols[MAX_DEGREE])
{
	t_quadratic	equa;
	double		radic;

	equa = (t_quadratic){.a = (line.v.z * line.v.z) + (line.v.y * line.v.y),
		.b = 2 * ((line.o.z * line.v.z) + (line.o.y * line.v.y)),
		.c = (line.o.z * line.o.z) + (line.o.y * line.o.y) -
			(obj.object_union.cylinder.radius *
			obj.object_union.cylinder.radius)};
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols[0] = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols[1] = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	return (2);
}
