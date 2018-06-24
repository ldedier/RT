/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:38:29 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 09:31:36 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		resolve_quartic_1(t_auxquartic *x, t_quartic equa)
{
	equa.b /= equa.a;
	equa.c /= equa.a;
	equa.d /= equa.a;
	equa.e /= equa.a;
	x->alpha = -((3.0 * equa.b * equa.b) / (8.0)) + (equa.c);
	x->beta = ((equa.b * equa.b * equa.b) / (8.0)) -
		((equa.b * equa.c) / (2.0)) + (equa.d);
	x->gamma = -((3.0 * equa.b * equa.b * equa.b * equa.b) /
			(256.0)) + ((equa.c * equa.b * equa.b) / (16.0)) -
		((equa.b * equa.d) / (4.0)) + (equa.e);
	x->t = -(equa.b / (4.0));
}

static void		resolve_quartic_2(t_auxquartic *x)
{
	x->p = -((x->alpha * x->alpha) / 12.0) - x->gamma;
	x->q = -((x->alpha * x->alpha * x->alpha) / 108.0) +
		((x->alpha * x->gamma) / 3.0) - ((x->beta * x->beta) / 8.0);
	x->r = -(x->q / 2.0) + csqrt(((x->q * x->q) / 4.0) +
			((x->p * x->p * x->p) / 27.0));
	x->u = cpowl(x->r, 1.0 / 3.0);
	x->y = -((5.0 * x->alpha) / 6.0) + x->u;
	if (ft_is_zero(x->u))
		x->y -= cpowl(x->q, 1.0 / 3.0);
	else
		x->y -= (x->p / (3.0 * x->u));
	x->w = csqrtl(x->alpha + 2 * x->y);
	x->r1 = csqrtl(-((3.0 * x->alpha) + (2.0 * x->y) + ((2.0 * x->beta) /
					x->w)));
	x->r2 = csqrtl(-((3.0 * x->alpha) + (2.0 * x->y) - ((2.0 * x->beta) /
					x->w)));
}

int				resolve_quartic(t_quartic equa,
		double complex qsols[MAX_DEGREE])
{
	t_auxquartic x;

	resolve_quartic_1(&x, equa);
	if (fabsl(equa.a) < EPSILON2)
		return (resolve_cubic(ft_quartic_as_cubic(equa), qsols));
	if (ft_is_zero(x.beta))
	{
		x.rad = csqrt((x.alpha * x.alpha) - 4 * x.gamma);
		x.r1 = csqrt((-x.alpha + x.rad) / 2.0);
		x.r2 = csqrt((-x.alpha - x.rad) / 2.0);
		qsols[0] = x.t + x.r1;
		qsols[1] = x.t - x.r1;
		qsols[2] = x.t + x.r2;
		qsols[3] = x.t - x.r2;
	}
	resolve_quartic_2(&x);
	qsols[0] = x.t + ((x.w - x.r1) / 2.0);
	qsols[1] = x.t + ((x.w + x.r1) / 2.0);
	qsols[2] = x.t + ((-x.w - x.r2) / 2.0);
	qsols[3] = x.t + ((-x.w + x.r2) / 2.0);
	return (4);
}
