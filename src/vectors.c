/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 07:11:54 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/23 19:40:20 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	newvector(t_point3d from, t_point3d to)
{
	t_point3d	vector;

	vector.x = to.x - from.x;
	vector.y = to.y - from.y;
	vector.z = to.z - from.z;
	return (vector);
}

double		dotprod(t_point3d v1, t_point3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_point3d	crossprod(t_point3d v1, t_point3d v2)
{
	t_point3d	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

double		magnitude(t_point3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_point3d	normalize(t_point3d v)
{
	t_point3d	res;
	double		mag;
	mag = magnitude(v);
	res.x = v.x / mag;
	res.y = v.y / mag;
	res.z = v.z / mag;
	return (res);
}
