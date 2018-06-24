/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 04:57:29 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 04:59:42 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

TTF_Font		*ft_load_font(char *str, int quality)
{
	TTF_Font	*font;

	font = TTF_OpenFont(str, quality);
	if (font == NULL)
		exit(1);
	return (font);
}

t_pixel			ft_new_pixel(int x, int y)
{
	t_pixel		pix;

	pix.x = x;
	pix.y = y;
	return (pix);
}

t_rangebar		ft_new_rangebar(double min, double max, t_pixel pix, double *v)
{
	t_rangebar	rb;

	rb.min = min;
	rb.max = max;
	rb.pix = pix;
	rb.value = v;
	return (rb);
}

t_grangebar		ft_new_grangebar(double min, double max, t_pixel pix, int *v)
{
	t_grangebar	grb;

	grb.min = min;
	grb.max = max;
	grb.pix = pix;
	grb.value = v;
	return (grb);
}

t_colorpicker	ft_new_colorpicker(t_pixel pix, t_pixel pos, t_color *color)
{
	t_colorpicker	cp;

	cp.pix = pix;
	cp.pos = pos;
	cp.color = color;
	return (cp);
}
