/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intcolors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:50:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/17 05:52:12 by lcavalle         ###   ########.fr       */
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

t_intcolor	get_intcolor(int color)
{
	t_intcolor	c;

	c.r = color / 0x10000;
	c.g = color / 0x100;
	c.b = color % 100;
	return (c);
}

t_color		scale_convert_color(t_intcolor icol, double t)
{
	t_color	col;
	
	icol.r = icol.r * t;
	icol.g = icol.g * t;
	icol.b = icol.b * t;
	icol.r = icol.r > 255 ? 255 : icol.r;
	icol.r = icol.r < 0 ? 0 : icol.r;
	icol.g = icol.g > 255 ? 255 : icol.g;
	icol.g = icol.g < 0 ? 0 : icol.g;
	icol.b = icol.b > 255 ? 255 : icol.b;
	icol.b = icol.b < 0 ? 0 : icol.b;
	col.r = icol.r;
	col.g = icol.g;
	col.b = icol.b;
	col.col = col.r * 0x10000 + col.g * 0x100 + col.b;
	return (col);
}
