/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:22:16 by lcavalle          #+#    #+#             */
/*   Updated: 2018/03/02 19:55:15 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	scale(t_point3d p, double scale)
{
	t_point3d	res;

	res.x = p.x * scale;
	res.y = p.y * scale;
	res.z = p.z * scale;
	return (res);
}

t_point3d	translate_vec(t_point3d p, t_point3d v, double scale)
{
	return ((t_point3d){.x = p.x + v.x * scale,
			.y = p.y + v.y * scale,
			.z = p.z + v.z * scale});
}

void		translate(t_object *obj, t_point3d v)
{
	obj->o = translate_vec(obj->o, v, 1.0);
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
