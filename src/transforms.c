/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:22:16 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/22 12:32:05 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	translate(t_object *obj, t_point3d v)
{
	t_point3d	p;
	p = (*obj).o;
	(*obj).o = (t_point3d){.x = p.x + v.x, .y = p.y + v.y, .z = p.z + v.z};
}

void	rotate(t_object *obj, t_point3d angles)
{
	(void)obj;
	(void)angles;
}
