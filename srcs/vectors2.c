/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:01:19 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 04:12:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	addvec(t_point3d v1, t_point3d v2)
{
	t_point3d res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_point3d	create_vec(double x, double y, double z)
{
	t_point3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double		proj(t_point3d v1, t_point3d v2)
{
	return (dotprod(v1, normalize(v2)));
}
