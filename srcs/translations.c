/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 06:36:32 by lcavalle          #+#    #+#             */
/*   Updated: 2018/03/20 06:36:58 by lcavalle         ###   ########.fr       */
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
