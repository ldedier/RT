/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:22:16 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/24 00:12:07 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	move(t_point3d p, t_point3d v, double scale)
{
	return ((t_point3d){.x = p.x + v.x * scale,
			.y = p.y + v.y * scale,
			.z = p.z + v.z * scale});
}

void	translate(t_object *obj, t_point3d v)
{
	t_point3d	p;
	p = (*obj).o;
	(*obj).o = move(p, v, 1.0);
}

void	rotate(t_object *obj, t_point3d angles)
{
	(void)obj;
	(void)angles;
}
