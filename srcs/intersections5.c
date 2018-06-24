/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:02:54 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 09:55:57 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			resolve_affine(t_affine equa, double complex qsols[MAX_DEGREE])
{
	noquartics(qsols);
	if (equa.a == 0)
		return (0);
	qsols[0] = -equa.b / equa.a;
	return (1);
}

int			resolve_quadratic(t_quadratic equa,
		double complex qsols[MAX_DEGREE])
{
	if (equa.a == 0)
		return (resolve_affine(ft_quadratic_as_affine(equa), qsols));
	noquartics(qsols);
	equa.radic = equa.b * equa.b - 4 * equa.a * equa.c;
	if (equa.radic < 0)
		return (0);
	else
	{
		if (equa.radic == 0)
		{
			qsols[0] = -equa.b / (2 * equa.a);
			return (1);
		}
		else
		{
			qsols[0] = (-equa.b - sqrt(equa.radic)) / (2 * equa.a);
			qsols[1] = (-equa.b + sqrt(equa.radic)) / (2 * equa.a);
			return (2);
		}
	}
}

int			ft_is_zero(long double complex z)
{
	return (fabs(crealf(z)) < EPSILON4 && fabs(cimagf(z)) < EPSILON4);
}

int			resolve_cubic(t_cubic equa, double complex qsols[MAX_DEGREE])
{
	t_auxcubic	x;

	if (fabsl(equa.a) < 0.001)
		return (resolve_quadratic(ft_cubic_as_quadratic(equa), qsols));
	noquartics(qsols);
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
	qsols[0] = x.g - (x.d / x.g) - x.s;
	x.g = ft_cbrt(x.f, 1);
	qsols[1] = x.g - (x.d / x.g) - x.s;
	x.g = ft_cbrt(x.f, 2);
	qsols[2] = x.g - (x.d / x.g) - x.s;
	return (3);
}

void		ft_init_aux(t_auxquart_init *g, t_line line)
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
