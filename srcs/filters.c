/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/08 01:29:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		motion_blur(t_canvas *canvas)
{
	double	*filter;

	filter = ft_memalloc(sizeof(double) * 25);
	filter[0] = 0.222222;
	filter[1] = 0.277778;
	filter[2] = 0.222222;
	filter[3] = 0.055556;
	filter[4] = 0;
	filter[5] = 0.277778;
	filter[6] = 0.444444;
	filter[7] = 0.444444;
	filter[8] = 0.222222;
	filter[9] = 0.055556;
	filter[10] = 0.222222;
	filter[11] = 0.444444;
	filter[12] = 0.555556;
	filter[13] = 0.444444;
	filter[14] = 0.222222;
	filter[15] = 0.055556;
	filter[16] = 0.222222;
	filter[17] = 0.444444;
	filter[18] = 0.444444;
	filter[19] = 0.277778;
	filter[20] = 0;
	filter[21] = 0.055556;
	filter[22] = 0.222222;
	filter[23] = 0.277778;
	filter[24] = 0.222222;
	convolute(canvas, filter, 5, 7);
	free(filter);
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

void		cyan(t_canvas *canvas)
{
	int	i;
	int	j;

	i = -1;
	while (++i < canvas->win_size.x)
	{
		j = -1;
		while (++j < canvas->win_size.y)
			((int *)canvas->surface->pixels)[i + j * canvas->win_size.x] =
				scale_convert_color(cyanscale(get_intcolor(get_color(
									((int *)canvas->surface->pixels)[i +
									j * canvas->win_size.x]))), 1).col;
	}
}
void		red(t_canvas *canvas)
{
	int	i;
	int	j;

	i = -1;
	while (++i < canvas->win_size.x)
	{
		j = -1;
		while (++j < canvas->win_size.y)
			((int *)canvas->surface->pixels)[i + j * canvas->win_size.x] =
				scale_convert_color(redscale(get_intcolor(get_color(
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
