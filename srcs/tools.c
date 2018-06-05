/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 19:27:30 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/05 12:13:20 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pixel	fast_div(const t_canvas *canvas)
{
	t_pixel	div;

	div.x = 7;
	div.y = 7;
	while (canvas->win_size.x % (div.x * FAST_RATIO * NTHREADS) != 0 && div.x < 100)
		div.x++;
	while (canvas->win_size.y % (div.y * FAST_RATIO * NTHREADS) != 0 && div.y < 100)
		div.y++;
	printf("div: %i, %i\n",div.x, div.y);fflush(stdout);
	if (div.x >= 100 || div.y >= 100)
	{
		printf("incorrect resolution. cannot find divisors for fast render.\n");
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
