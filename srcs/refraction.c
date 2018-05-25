/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 02:55:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/17 05:30:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	refraction(t_point3d normal, t_point3d in, double n1, double n2)
{
	double c1;
	double c2;
	double n;

	c1 = -ft_dot_product(normal, in);
	n = n1 / n2;
	c2 = sqrt(1 - (n * n) * (1 - (c1 * c1)));
	if (c1 > 0)
		return (ft_point3d_add(ft_point3d_scalar(in, n),
				ft_point3d_scalar(normal, n * c1 -	c2)));
	else
		return (ft_point3d_add(ft_point3d_scalar(in, n),
				ft_point3d_scalar(normal, n * c1 + c2)));

//	return (in);
}
