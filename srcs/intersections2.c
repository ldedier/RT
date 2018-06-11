/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:37:20 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 09:30:00 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_cut_as_strip(double sols[MAX_DEGREE], int nbsols, t_line line)
{
	int 			i;
	t_point3d		point;

	i = 0;
	while (i < nbsols)
	{
		point = ft_point3d_add(line.o, ft_point3d_scalar(line.v, sols[i]));
		if (point.x * point.x + point.y * point.y + point.z * point.z > 0.65 ||
				point.x * point.x + point.y * point.y +
				point.z * point.z < 0.25)
			sols[i] = -1;
		i++;
	}
}

int		intersect_mobius(t_line line, t_object obj, double sols[MAX_DEGREE])
{
	t_quartic		equa;
	int				nbqsols;
	double complex	qsols[4];
	int				ret;

	equa = get_quartic_mobius(line, obj);
	nbqsols = resolve_quartic(equa, qsols);
	ret = ft_transfer_real_roots(qsols, nbqsols, sols);
	ft_cut_as_strip(sols, ret, line);
	return (ret);
}

int		intersect_lemniscate(t_line line, t_object obj, double sols[MAX_DEGREE])
{
	t_quartic		equa;
	int				nbqsols;
	double complex	qsols[4];

	(void)obj;
	equa = get_quartic_lemniscate(line);
	nbqsols = resolve_quartic(equa, qsols);
	return (ft_transfer_real_roots(qsols, nbqsols, sols));
}

int		intersect_roman(t_line line, t_object obj, double sols[MAX_DEGREE])
{
	t_quartic		equa;
	double complex	qsols[4];
	int				nbqsols;

	(void)obj;
	equa = get_quartic_roman(line);
	nbqsols = resolve_quartic(equa, qsols);
	return (ft_transfer_real_roots(qsols, nbqsols, sols));
}

int		intersect_piriform(t_line line, t_object obj, double sols[MAX_DEGREE])
{
	t_quartic 		equa;
	double complex	qsols[4];
	int				nbqsols;

	(void)obj;
	equa = get_quartic_piriform(line);
	nbqsols = resolve_quartic(equa, qsols);
	return (ft_transfer_real_roots(qsols, nbqsols, sols));
}
