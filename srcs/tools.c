/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 19:27:30 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/10 00:37:55 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pixel	fast_div(const t_canvas *canvas)
{
	t_pixel	div;

	div.x = 7;
	div.y = 7;
	while (canvas->win_size.x % (div.x * FAST_RATIO * NTHREADS) != 0 && div.x < 121)
		div.x++;
	while (canvas->win_size.y % (div.y * FAST_RATIO * NTHREADS) != 0 && div.y < 121)
		div.y++;
	if (div.x >= 121 || div.y >= 121)
	{
		ft_putendl("incorrect resolution."
				"cannot find divisors for fast render.");
		exit(1);
	}
	return (div);
}

int	equal_double(double a, double b)
{
	return (a < b + EPSILON && a > b - EPSILON);
}

double	get_world_distance(t_object obj, t_point3d hitpoint, t_line world_line)
{
	return (magnitude(newvector(world_line.o,
					ft_point3d_mat4_mult(hitpoint, obj.transform_pos))));
}
