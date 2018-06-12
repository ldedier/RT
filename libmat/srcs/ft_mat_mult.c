/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 21:03:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 11:01:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_mat4	ft_mat4_zeros(void)
{
	t_mat4	res;
	int		i;

	i = 0;
	while (i < 16)
	{
		res.as_mat[i] = 0;
		i++;
	}
	return (res);
}

t_mat4	ft_mat4_mult(t_mat4 mat1, t_mat4 mat2)
{
	t_mat4	res;
	int		i;
	int		j;
	int		k;
	int		l;

	res = ft_mat4_zeros();
	i = 0;
	while (i < 4)
	{
		k = i;
		j = 0;
		while (j < 4)
		{
			l = -1;
			while (++l < 4)
				res.as_mat[k] += mat1.as_mat[(k % 4) + 4 * l] *
					mat2.as_mat[l + ((k / 4) * 4)];
			k += 4;
			j++;
		}
		i++;
	}
	return (res);
}
