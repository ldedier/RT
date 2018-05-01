/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 01:30:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/15 17:29:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_vec3	ft_vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

t_vec3	ft_vec3_cmp(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.x - vec2.x;
	res.y = vec1.y - vec2.y;
	res.z = vec1.z - vec2.z;
	return (res);
}

float	ft_dot_product(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	ft_vec3_cross_product(t_vec3 vec1, t_vec3 vec2)
{
	return (ft_new_vec3((vec1.y * vec2.z) - (vec1.z * vec2.y),
		   (vec1.z * vec2.x) - (vec1.x * vec2.z),
		  	(vec1.x * vec2.y) - (vec1.y * vec2.x)));
}

t_vec3	ft_vec3_scalar(t_vec3 vec, float k)
{
		return (ft_new_vec3(vec.x * k,
		  	 vec.y * k,
		 	 vec.z * k));
}
