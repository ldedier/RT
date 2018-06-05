/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 02:21:28 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/05 03:39:22 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			scale_color(t_color c, double t)
{
	t_color	ret;

	ret.r = c.r * t;
	ret.g = c.g * t;
	ret.b = c.b * t;
	ret.col = ret.r * 0x10000 + ret.g * 0x100 + ret.b;
	return (ret);
}

t_color			add_colors(t_color c1, t_color c2)
{
	t_color	ret;

	ret.r = c1.r + c2.r > 0xFF ? 0xFF : c1.r + c2.r;
	ret.g = c1.g + c2.g > 0xFF ? 0xFF : c1.g + c2.g;
	ret.b = c1.b + c2.b > 0xFF ? 0xFF : c1.b + c2.b;
	ret.col = ret.r * 0x10000 + ret.g * 0x100 + ret.b;
	return (ret);
}

t_color			interpole_color(double t, t_color c1, t_color c2)
{
	t_color	ip;

	ip.r = c1.r + (c2.r - c1.r) * t;
	ip.g = c1.g + (c2.g - c1.g) * t;
	ip.b = c1.b + (c2.b - c1.b) * t;
	ip.col = ip.r * 0x10000 + ip.g * 0x100 + ip.b;
	return (ip);
}

t_color			get_color(int color)
{
	t_color c;

	c.col = color;
	c.r = color / 0x10000;
	c.g = color / 0x100;
	c.b = color % 0x100;
	return (c);
}

void			paint_pixel(t_pixel p, t_color c, t_canvas *canvas)
{
	int *pix;

	pix = (int *)canvas->surface->pixels;
	pix[p.x + p.y * canvas->win_size.x] = c.col;
}
