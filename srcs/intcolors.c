/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intcolors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:50:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/18 02:23:36 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_intcolor	new_intcolor(void)
{
	t_intcolor	ret;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	return (ret);
}

t_intcolor	add_scale_intcolors(t_intcolor icol1, t_intcolor icol2, double scale)
{
	icol1.r += icol2.r * scale;
	icol1.g += icol2.g * scale;
	icol1.b += icol2.b * scale;
	return (icol1);
}

t_intcolor	get_intcolor(t_color color)
{
	t_intcolor	c;

	c.r = color.r;
	c.g = color.g;
	c.b = color.b;
	return (c);
}

t_color		scale_convert_color(t_intcolor icol, double t)
{
	t_color	col;
	int		r;
	int		g;
	int		b;
	
	icol.r = icol.r * t;
	icol.g = icol.g * t;
	icol.b = icol.b * t;
	r = (int)icol.r;
	g = (int)icol.g;
	b = (int)icol.b;
	r = r > 255 ? 255 : r;
	r = r < 0 ? 0 : r;
	g = g > 255 ? 255 : g;
	g = g < 0 ? 0 : g;
	b = b > 255 ? 255 : b;
	b = b < 0 ? 0 : b;
	col.r = r;
	col.g = g;
	col.b = b;
	col.col = col.r * 0x10000 + col.g * 0x100 + col.b;
	return (col);
}
