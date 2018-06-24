/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 01:30:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 11:10:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_point3d	ft_point3d_add(t_point3d vec1, t_point3d vec2)
{
	t_point3d	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

t_point3d	ft_point3d_cmp(t_point3d vec1, t_point3d vec2)
{
	t_point3d	res;

	res.x = vec1.x - vec2.x;
	res.y = vec1.y - vec2.y;
	res.z = vec1.z - vec2.z;
	return (res);
}

double		ft_dot_product(t_point3d vec1, t_point3d vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_point3d	ft_point3d_cross_product(t_point3d vec1, t_point3d vec2)
{
	return (ft_new_vec3((vec1.y * vec2.z) - (vec1.z * vec2.y),
				(vec1.z * vec2.x) - (vec1.x * vec2.z),
				(vec1.x * vec2.y) - (vec1.y * vec2.x)));
}

t_point3d	ft_point3d_scalar(t_point3d vec, double k)
{
	return (ft_new_vec3(vec.x * k, vec.y * k, vec.z * k));
}
