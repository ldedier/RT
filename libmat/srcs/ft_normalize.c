/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 21:46:29 by ldedier           #+#    #+#             */
/*   Updated: 2018/04/24 19:17:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

float	ft_vec3_get_norm(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

void	ft_vec3_normalize(t_vec3 *vec)
{
	float norm;
	float invnorm;

	norm = ft_vec3_get_norm(*vec);
	if (norm != 0)
	{
		invnorm = 1 / norm;
		vec->x *= invnorm;
		vec->y *= invnorm;
		vec->z *= invnorm;
	}
}
