/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 19:27:30 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/02 21:35:09 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	equal_double(double a, double b)
{
	return (a < b + EPSILON && a > b - EPSILON);
}

double	get_world_distance(t_object obj, t_point3d hitpoint, t_line world_line)
{
	return (magnitude(newvector(world_line.o,
					ft_point3d_mat4_mult(hitpoint, obj.transform_pos))));
}
