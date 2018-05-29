/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quartics_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 07:00:13 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/26 07:05:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_quartic			get_quartic_piriform(t_line line)
{
	t_quartic res;
	t_auxquart_init g;

	ft_init_aux(&g, line);
	res.a = g.vy4;
	res.b = (4 * line.o.y * g.vy3) - g.vy3;
	res.c = (6 * (g.oy2 * g.vy2)) - (3 * line.o.y * g.vy2) + g.vz2 + g.vx2;
	res.d = (4 * (g.oy3 * line.v.y)) - (3 * g.oy2 * line.v.y) + 2 * (line.o.z * line.v.z + line.o.x * line.v.x);
	res.e = g.oy4 - g.oy3 + g.oz2 + g.ox2;
	return (res);
}

t_quartic			get_quartic_roman(t_line line)
{
	t_quartic res;
	t_auxquart_init g;

	ft_init_aux(&g, line);
	res.a = g.vx2 * g.vy2 + g.vy2 * g.vz2 + g.vx2 * g.vz2;
	res.b = 2 * (line.o.x * line.v.x * g.vy2 + line.o.y * line.v.y * g.vx2 +
			line.o.y * line.v.y * g.vz2 + line.o.z * line.v.z * g.vy2
			+ line.o.x * line.v.x * g.vz2 + line.o.z * line.v.z * g.vx2)
		+ line.v.x * line.v.y * line.v.z;
	res.c = g.ox2 * g.vy2 + g.oy2 * g.vx2 + g.oy2 * g.vz2 + g.oz2 * g.vy2
		+ g.ox2 * g.vz2 + g.oz2 * g.vx2
		+ 4 * (line.o.x * line.v.x * line.o.y * line.v.y +
				line.o.y * line.v.y * line.o.z * line.v.z +
				line.o.x * line.v.x * line.o.z * line.v.z)
		+ (line.o.x * line.v.y * line.v.z + line.o.y * line.v.x * line.v.z
				+ line.o.z * line.v.x * line.v.y);
	res.d = (line.v.x * line.o.y * line.o.z + line.v.y * line.o.x * line.o.z +
			line.v.z * line.o.x * line.o.y)
		+ 2 * (g.ox2 * line.o.y * line.v.y + g.oy2 * line.o.x * line.v.x +
				g.oy2 * line.o.z * line.v.z + g.oz2 * line.o.y * line.v.y +
				g.ox2 * line.o.z * line.v.z + g.oz2 * line.o.x * line.v.x);
	res.e = line.o.x * line.o.y * line.o.z + g.ox2 * g.oy2 + g.oy2 * g.oz2 +
		g.ox2 * g.oz2;
	return (res);
}

t_quartic			get_quartic_lemniscate(t_line line)
{
	t_quartic res;
	t_auxquart_init g;

	ft_init_aux(&g, line);
	res.a = g.vx4;
	res.b = 4 * line.o.x * g.vx3;
	res.c = (6 * (g.ox2 * g.vx2)) + g.vy2 + g.vz2 - g.vx2;
	res.d = (4 * (g.ox3 * line.v.x)) + 2 * (line.o.y * line.v.y + line.o.z * line.v.z - line.o.x * line.v.x);
	res.e = g.ox4 + g.oy2 + g.oz2 - g.ox2;
	return (res);
}

t_quartic			get_quartic_goursat(t_line line, t_object obj)
{
	t_auxquart_init g;
	t_quartic res;
	double a;
	double b;

	a = obj.object_union.goursat.a;
	b = obj.object_union.goursat.b;
	ft_init_aux(&g, line);
	res.a = g.vx4 + g.vy4 + g.vz4;
	res.b = 4 * (line.o.x * g.vx3 + line.o.y * g.vy3 + line.o.z * g.vz3);
	res.c = (6 *(g.ox2 * g.vx2 + g.oy2 * g.vy2 + g.oz2 * g.vz2)) - a *
		(g.vx2 + g.vy2 + g.vz2);
	res.d = (4 * (g.ox3 * line.v.x + g.oy3 * line.v.y + g.oz3 * line.v.z))
		- 2 * a * (ft_dot_product(line.o, line.v));
	res.e = g.ox4 + g.oy4 + g.oz4 - (a * (g.ox2 + g.oy2 + g.oz2)) + b;
	return (res);
}
t_quartic			get_quartic_torus(t_line line, t_object obj)
{
	t_auxtorus x;
	t_quartic res;
	double a;
	double b;

	a = obj.object_union.torus.big_rad;
	b = obj.object_union.torus.small_rad;
	x.g = 4 * a * a * (line.v.x * line.v.x + line.v.y * line.v.y);
	x.h = 8 * a * a * (line.o.x * line.v.x + line.o.y * line.v.y);
	x.i = 4 * a * a * (line.o.x * line.o.x + line.o.y * line.o.y);
	x.j = ft_dot_product(line.v, line.v);
	x.k = 2 * ft_dot_product(line.o, line.v);
	x.l = ft_dot_product(line.o, line.o) + (a * a) - (b * b);
	res.a = x.j * x.j;
	res.b = 2 * x.j * x.k;
	res.c = (2 * x.j * x.l) + (x.k * x.k) - x.g;
	res.d = (2 * x.k * x.l) - x.h;
	res.e = (x.l * x.l) - x.i;
	return (res);
}
