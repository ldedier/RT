/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 21:52:02 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/08 19:51:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libmat.h"

void	ft_print_mat4(t_mat4 mat)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < 4)
	{
		k = i;
		j = 0;
		while (j < 4)
		{
			printf("%.1f ", mat.as_mat[k]);
			k += 4;
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	ft_print_point3d(t_point3d vec)
{
		printf("x:%.6f\ny:%.6f\nz:%.6f\n\n", vec.x, vec.y, vec.z);
}

void	ft_print_ivec3(t_ivec3	vec)
{
		printf("x:%d\ny:%d\nz:%d\n\n", vec.x, vec.y, vec.z);
}
