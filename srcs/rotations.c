/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:22:16 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/21 08:13:21 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	rotate_axis(t_point3d p, t_point3d v, double a)
{
	t_point3d	rot;
	double		t;
	double		s;
	double		c;

	t = 1 - cos(a);
	s = sin(a);
	c = cos(a);
	rot.x = t * v.x * v.x * p.x + c * p.x +
			t * v.x * v.y * p.y - s * v.z * p.y +
			t * v.x * v.z * p.z + s * v.y * p.z;
	rot.y = t * v.x * v.y * p.x + s * v.z * p.x +
			t * v.y * v.y * p.y + c * p.y +
			t * v.y * v.z * p.z - s * v.x * p.z;
	rot.z = t * v.x * v.z * p.x + t * v.y * p.x +
			t * v.y * v.y * p.y + s * v.x * p.y +
			t * v.z * v.z * p.z + c * p.z;
	return (rot);
}

t_point3d	rotate_vec(t_point3d vec, t_point3d a)
{
	t_point3d	rot;

	rot.x = vec.x * cos(a.x) * cos(a.y) +
		vec.y * (cos(a.x) * sin(a.y) * sin(a.z) - sin(a.x) * cos(a.z)) +
		vec.z * (cos(a.x) * sin(a.y) * cos(a.z) + sin(a.x) * sin(a.z));
	rot.y = vec.x * sin(a.x) * cos(a.y) +
		vec.y * (sin(a.x) * sin(a.y) * sin(a.z) + cos(a.x) * cos(a.z)) +
		vec.z * (sin(a.x) * sin(a.y) * cos(a.z) - sin(a.x) * sin(a.z));
	rot.z = vec.x * -sin(a.y) +
		vec.y * cos(a.y) * sin(a.z) +
		vec.z * cos(a.y) * cos(a.z);
	return (rot);
}

void		rotate(t_object *obj, t_point3d a)
{
	obj->r = normalize(rotate_vec(obj->r, a));
}
