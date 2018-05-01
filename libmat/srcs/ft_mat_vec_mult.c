/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_vec_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:10:52 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/08 22:26:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

void	ft_load_vec(t_vec3 vec, float vec_as_arr[4])
{
	vec_as_arr[0] = vec.x;
	vec_as_arr[1] = vec.y;
	vec_as_arr[2] = vec.z;
	vec_as_arr[3] = 1.0;
}

void	ft_init_vec(float vec_as_arr[3])
{
	vec_as_arr[0] = 0;
	vec_as_arr[1] = 0;
	vec_as_arr[2] = 0;
}

t_vec3	ft_vec3_mat4_mult(t_vec3 vec, t_mat4 mat)
{
	float vec_as_arr[4];
	float res[3];
	int i;
	int j;
	int k;

	ft_load_vec(vec, vec_as_arr);
	ft_init_vec(res);
	i = 0;
	while (i < 3)
	{
		k = i;
		j = 0;
		while (j < 4)
		{
			res[i] += vec_as_arr[j] * mat.as_mat[k];
			k += 4;
			j++;
		}
		i++;
	}
	return (ft_new_vec3(res[0], res[1], res[2]));
}
