/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convolute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/10 01:22:11 by lcavalle         ###   ########.fr       */
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

void	convolute(t_canvas *canvas, double *filter, int filter_size,
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

void	apply_convolution(t_world *world)
{
	ft_printf("Applying filters...\n");
	if (world->filters[e_grey])
		grey(world->canvas);
	if (world->filters[e_emboss])
		emboss(world->canvas);
	if (world->filters[e_sharpen])
		sharpen(world->canvas);
	if (world->filters[e_sobel])
		sobel(world->canvas);
	if (world->filters[e_gauss_blur])
		gauss_blur(world->canvas);
	if (world->filters[e_motion_blur])
		motion_blur(world->canvas);
	ft_printf("Filters applied.\n");
}
