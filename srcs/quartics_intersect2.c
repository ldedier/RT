/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quartics_intersect2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:20:27 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/07 06:58:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_quartic			get_quartic_mobius(t_line line, t_object obj)
{
	t_quartic		res;
	t_auxquart_init	g;

	(void)obj;
	ft_init_aux(&g, line);
	res.a = 0;
	res.b = g.vx2 * line.v.y + g.vz2 * line.v.y + g.vy3 - 2 *
		(g.vx2 * line.v.z + g.vy2 * line.v.z);
	res.c = 2 * line.o.x * line.v.x * line.v.y + line.o.y * g.vx2 +
		2 * line.o.z * line.v.z * line.v.y + line.o.y * g.vz2 +
		3 * line.o.y * g.vy2
		- 2 * (line.v.x * line.v.z + 2 * line.o.x * line.v.x * line.v.z +
	line.o.z * g.vx2 + 2 * line.o.y * line.v.y * line.v.z + line.o.z * g.vy2);
	res.d = g.ox2 * line.v.y + 2 * line.o.x * line.o.y * line.v.x +
		g.oz2 * line.v.y + 2 * line.o.z * line.o.y * line.v.z +
		3 * g.oy2 * line.v.y - line.v.y
		- 2 * (line.o.x * line.v.z + line.o.z * line.v.x +
				g.ox2 * line.v.z + 2 * line.o.x * line.o.z * line.v.x
				+ g.oy2 * line.v.z + 2 * line.o.y * line.o.z * line.v.y);
	res.e = g.ox2 * line.o.y + g.oz2 * line.o.y + g.oy3 - line.o.y -
		2 * (line.o.x * line.o.z + g.ox2 * line.o.z + g.oy2 * line.o.z);
	return (res);
}
