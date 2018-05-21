/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/20 03:07:50 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	apply_filter(t_convolution conv)
{
	t_pixel		fil;
	t_intcolor	auxcol;
	t_color		curr_col;

	fil.x = -1;
	auxcol = new_intcolor();
	while (++fil.x < conv.filter_size)
	{
		fil.y = -1;
		while (++fil.y < conv.filter_size)
		{
			curr_col = get_color(
					conv.img[(conv.pix.x + fil.x - conv.filter_size / 2) +
					((conv.pix.y + fil.y - conv.filter_size / 2) *
					 conv.canvas->win_size.x)]);
			auxcol = add_scale_intcolors(auxcol, get_intcolor(curr_col),
					conv.filter[fil.x + fil.y * conv.filter_size]);
		}
	}
	conv.aux[conv.pix.x + conv.pix.y * conv.canvas->win_size.x] =
		scale_convert_color(auxcol, (double)1 / conv.den).col;
}

static void	convolute(t_canvas *canvas, double *filter, int filter_size,
		int den)
{
	t_convolution	conv;

	conv.canvas = canvas;
	conv.filter_size = filter_size;
	conv.den = den;
	conv.filter = filter;
	conv.img = (int *)canvas->surface->pixels;
	conv.aux = ft_memalloc(sizeof(int) * canvas->win_size.x * canvas->win_size.y);
	conv.pix.x = -1 + filter_size / 2;
	while (++conv.pix.x < canvas->win_size.x - filter_size / 2)
	{
		conv.pix.y = -1 + filter_size / 2;
		while (++conv.pix.y < canvas->win_size.y - filter_size / 2)
		{
			apply_filter(conv);
		}
	}
	ft_memcpy(conv.img, conv.aux, sizeof(int) *
			canvas->win_size.x * canvas->win_size.y);
	free(conv.aux);
}

void		gauss_blur(t_canvas *canvas)
{
	double	*filter;

	filter = ft_memalloc(sizeof(double) * 9);
	filter[0] = 1;
	filter[1] = 2;
	filter[2] = 1;
	filter[3] = 2;
	filter[4] = 4;
	filter[5] = 2;
	filter[6] = 1;
	filter[7] = 2;
	filter[8] = 1;
	convolute(canvas, filter, 3, 16);
	free(filter);
}

void		sharpen(t_canvas *canvas)
{
	double	*filter;

	filter = ft_memalloc(sizeof(double) * 9);
	filter[0] = 0;
	filter[1] = -1;
	filter[2] = 0;
	filter[3] = -1;
	filter[4] = 5;
	filter[5] = -1;
	filter[6] = 0;
	filter[7] = -1;
	filter[8] = 0;
	convolute(canvas, filter, 3, 1);
	free(filter);
}

void		emboss(t_canvas *canvas)
{
	double	*filter;

	filter = ft_memalloc(sizeof(double) * 9);
	filter[0] = -2;
	filter[1] = -1;
	filter[2] = 0;
	filter[3] = -1;
	filter[4] = 1;
	filter[5] = 1;
	filter[6] = 0;
	filter[7] = 1;
	filter[8] = 2;
	convolute(canvas, filter, 3, 1);
	free(filter);
}

void		sobel(t_canvas *canvas)
{
	double	*filter;

	filter = ft_memalloc(sizeof(double) * 9);
	filter[0] = 0;
	filter[1] = 4;
	filter[2] = 0;
	filter[3] = 4;
	filter[4] = -16;
	filter[5] = 4;
	filter[6] = 0;
	filter[7] = 4;
	filter[8] = 0;
	convolute(canvas, filter, 3, 1);
	free(filter);
}
