/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:04:16 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 09:56:40 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void					noquartics(double complex qsols[MAX_DEGREE])
{
	int i;

	i = 0;
	while (i < MAX_DEGREE)
		qsols[i++] = -1;
}

t_cubic					ft_quartic_as_cubic(t_quartic quartic)
{
	t_cubic res;

	res.a = quartic.b;
	res.b = quartic.c;
	res.c = quartic.d;
	res.d = quartic.e;
	res.debug = quartic.debug;
	return (res);
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

t_affine				ft_quadratic_as_affine(t_quadratic quadratic)
{
	t_affine res;

	res.a = quadratic.b;
	res.b = quadratic.c;
	res.debug = quadratic.debug;
	return (res);
}
