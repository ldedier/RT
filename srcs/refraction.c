/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 02:55:19 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/04 20:51:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	refraction(t_hit *hit, t_line *line)
{
	double c1;
	double c2;
	double n;

	if (hit->enter)
		n = 1 / hit->obj.refract;
	else
		n = hit->obj.refract;
	c1 = -ft_dot_product(hit->normal, line->v);
	c2 = sqrt(1 - (n * n) * (1 - (c1 * c1)));
	if (c1 > 0)
		return (ft_point3d_add(ft_point3d_scalar(line->v, n),
				ft_point3d_scalar(hit->normal, n * c1 -	c2)));
	else
		return (ft_point3d_add(ft_point3d_scalar(line->v, n),
				ft_point3d_scalar(hit->normal, n * c1 + c2)));
}
