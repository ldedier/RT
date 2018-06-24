/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transpose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 21:01:12 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 11:04:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_mat4	ft_mat4_transpose(t_mat4 mat)
{
	t_mat4	res;
	int		i;

	i = 0;
	while (i < 16)
	{
		res.as_mat[i] = mat.as_mat[(i / 4) + (4 * (i % 4))];
		i++;
	}
	return (res);
}
