/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 21:52:02 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/07 21:45:15 by ldedier          ###   ########.fr       */
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

void	ft_print_vec3(t_vec3 vec)
{
		printf("x:%.2f\ny:%.2f\nz:%.2f\n\n", vec.x, vec.y, vec.z);
}
