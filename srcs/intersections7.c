/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 09:04:57 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 09:58:42 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_min_pos(double t1, double t2)
{
	if ((t1 < t2 || t2 < 0) && t1 > 0)
		return (t1);
	if ((t2 < t1 || t1 < 0) && t2 > 0)
		return (t2);
	else
		return (-1);
}

int		ft_transfer_real_roots(double complex qsols[MAX_DEGREE],
		int nbqsols, double sols[MAX_DEGREE])
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < nbqsols)
	{
		if (fabsl(cimagl(qsols[i])) < EPSILON3)
			sols[res++] = creal(qsols[i]);
		i++;
	}
	return (res);
}

int		intersect_goursat(t_line line, t_object obj, double sols[MAX_DEGREE])
{
	t_quartic		equa;
	double complex	qsols[MAX_DEGREE];
	int				nbqsols;

	equa = get_quartic_goursat(line, obj);
	nbqsols = resolve_quartic(equa, qsols);
	return (ft_transfer_real_roots(qsols, nbqsols, sols));
}
