/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/18 10:28:03 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	apply_filter(t_canvas *canvas, double *filter, int filter_size,
		int den)
{
	int			*img;
	int			*aux;
	t_pixel		pix;
	t_pixel		fil;
	t_color		curr_col;
	t_intcolor	auxcol;

	img = (int *)canvas->surface->pixels;
	aux = ft_memalloc(sizeof(int) * canvas->win_size.x * canvas->win_size.y);
	pix.x = -1 + filter_size / 2;
	while (++pix.x < canvas->win_size.x - filter_size / 2)
	{
		pix.y = -1 + filter_size / 2;
		while (++pix.y < canvas->win_size.y - filter_size / 2)
		{
			fil.x = -1;
			auxcol = new_intcolor();
			while (++fil.x < filter_size)
			{
				fil.y = -1;
				while (++fil.y < filter_size)
				{
					curr_col = get_color(
							img[(pix.x + fil.x - filter_size / 2) +
							((pix.y + fil.y - filter_size / 2) *
							 canvas->win_size.x)]);
					auxcol = add_scale_intcolors(auxcol, get_intcolor(curr_col),
							filter[fil.x + fil.y * filter_size]);
				}
			}
			aux[pix.x + pix.y * canvas->win_size.x] = scale_convert_color(
					auxcol, (double)1 / den).col;
		}
	}
	ft_memcpy(img, aux, sizeof(int) * canvas->win_size.x * canvas->win_size.y);
	free(aux);
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
	apply_filter(canvas, filter, 3, 16);
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
	apply_filter(canvas, filter, 3, 1);
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
	apply_filter(canvas, filter, 3, 1);
	free(filter);
}

void		sobel(t_canvas *canvas)
{
	double	*filter;

	filter = ft_memalloc(sizeof(double) * 9);
	filter[0] = 0;
	filter[1] = 1;
	filter[2] = 0;
	filter[3] = 1;
	filter[4] = -4;
	filter[5] = 1;
	filter[6] = 0;
	filter[7] = 1;
	filter[8] = 0;
	apply_filter(canvas, filter, 3, 1);
	free(filter);
}
