/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/27 18:45:37 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void		grey(t_canvas *canvas)
{
	int	i;
	int	j;

	i = -1;
	while (++i < canvas->win_size.x)
	{
		j = -1;
		while (++j < canvas->win_size.y)
			((int *)canvas->surface->pixels)[i + j * canvas->win_size.x] =
				scale_convert_color(greyscale(get_intcolor(get_color(
									((int *)canvas->surface->pixels)[i +
									j * canvas->win_size.x]))), 1).col;
	}
}

void		draw_borders(t_canvas *canvas)
{
	int		*tmp;
	t_color	col;
	int		i;
	int		j;
	
	tmp = ft_memalloc(sizeof(int) * canvas->win_size.x * canvas->win_size.y);
	tmp = ft_memcpy(tmp, (int *)canvas->surface->pixels,
			sizeof(int) * canvas->win_size.x * canvas->win_size.y);
//	grey(canvas);
	sobel(canvas);
	i = -1;
	while (++i < canvas->win_size.x)
	{
		j = -1;
		while (++j < canvas->win_size.y)
		{
			col = get_color(((int *)canvas->surface->pixels)[i +
					j * canvas->win_size.x]);
			if (col.r > 180 || col.g > 180 || col.b > 180)
				((int *)canvas->surface->pixels)[i + j * canvas->win_size.x] =
					0x0;
			else
				((int *)canvas->surface->pixels)[i + j * canvas->win_size.x] =
					tmp[i + j * canvas->win_size.x];
		}
	}
	free(tmp);
}
