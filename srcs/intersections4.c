/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:01:45 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 09:49:23 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					intersect_paraboloid(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	t_quadratic	equa;
	double		radic;

	(void)obj;
	equa = (t_quadratic){.a = line.v.y * line.v.y + line.v.z * line.v.z,
		.b = 2 * (line.o.y * line.v.y + line.v.z * line.o.z) - line.v.x,
			.c = line.o.y * line.o.y + line.o.z * line.o.z - line.o.x};
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols[0] = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols[1] = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	return (2);
}

int					intersect_hyperboloid(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	t_quadratic	equa;
	double		radic;
	double		rad;

	rad = obj.object_union.hyperboloid.radius;
	(void)obj;
	equa = (t_quadratic){.a = line.v.y * line.v.y + line.v.z * line.v.z -
		line.v.x * line.v.x,
			.b = 2 * (line.o.y * line.v.y + line.o.z * line.v.z -
				line.o.x * line.v.x),
			.c = line.o.y * line.o.y + line.o.z * line.o.z -
				line.o.x * line.o.x - rad * rad};
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols[0] = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols[1] = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	return (2);
}

static t_quadratic	get_quadratic_ellipsoid(t_line line, t_object obj)
{
	t_point3d	abc;
	t_quadratic res;

	abc = obj.object_union.ellipsoid.abc;
	res.a = ((line.v.x * line.v.x) / (abc.x * abc.x)) +
		((line.v.y * line.v.y) / (abc.y * abc.y)) +
		((line.v.z * line.v.z) / (abc.z * abc.z));
	res.b = 2 * (((line.v.x * line.o.x) / (abc.x * abc.x)) +
			((line.v.y * line.o.y) / (abc.y * abc.y)) +
			((line.v.z * line.o.z) / (abc.z * abc.z)));
	res.c = ((line.o.x * line.o.x) / (abc.x * abc.x)) +
		((line.o.y * line.o.y) / (abc.y * abc.y)) +
		((line.o.z * line.o.z) / (abc.z * abc.z)) -
		(obj.object_union.ellipsoid.radius *
		obj.object_union.ellipsoid.radius);
	return (res);
}

int					intersect_ellipsoid(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	t_quadratic	equa;
	double		radic;

	equa = get_quadratic_ellipsoid(line, obj);
	radic = (equa.b * equa.b) - (4 * equa.a * equa.c);
	if (radic < 0.0)
		return (0);
	sols[0] = (-equa.b + sqrt(radic)) / (2.0 * equa.a);
	sols[1] = (-equa.b - sqrt(radic)) / (2.0 * equa.a);
	return (2);
}

int					intersect_torus(t_line line, t_object obj,
		double sols[MAX_DEGREE])
{
	t_quartic		equa;
	double complex	qsols[4];
	int				nbqsols;

	equa = get_quartic_torus(line, obj);
	nbqsols = resolve_quartic(equa, qsols);
	return (ft_transfer_real_roots(qsols, nbqsols, sols));
}
