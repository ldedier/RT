/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 20:02:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/27 03:16:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** return 0 if the point should be cut, 1 if not
*/

int			ft_evaluate_cut(t_cut cut, t_point3d point)
{
	if (!cut.circular)
		return (cut.inequality(point.x * cut.cut_xyz.x + point.y * cut.cut_xyz.y + 
				point.z * cut.cut_xyz.z, cut.value));
	else
		return (cut.inequality(point.x *  point.x * cut.cut_xyz.x + 
					point.y * point.y * cut.cut_xyz.y + 
						point.z * point.z * cut.cut_xyz.z, cut.value));
}
