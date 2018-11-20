/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:06:39 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 18:06:37 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sobel(t_canvas *canvas)
{
	double	*filter;

	if (!(filter = ft_memalloc(sizeof(double) * 9)))
		ft_error("error malloc");
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

static void	draw_border_pixl(t_canvas *canvas, int i, int j, int *tmp)
{
	t_color	col;

	col = get_color(((int *)canvas->surface->pixels)[i +
			j * canvas->win_size.x]);
	if (col.r > 180 || col.g > 180 || col.b > 180)
		((int *)canvas->surface->pixels)[i + j * canvas->win_size.x] =
			0x0;
	else
		((int *)canvas->surface->pixels)[i + j * canvas->win_size.x] =
			tmp[i + j * canvas->win_size.x];
}

void		draw_borders(t_canvas *canvas)
{
	int		*tmp;
	int		i;
	int		j;

	if (!(tmp = ft_memalloc(sizeof(int) * canvas->win_size.x\
					* canvas->win_size.y)))
		ft_error("error malloc");
	tmp = ft_memcpy(tmp, (int *)canvas->surface->pixels,
			sizeof(int) * canvas->win_size.x * canvas->win_size.y);
	sobel(canvas);
	i = -1;
	while (++i < canvas->win_size.x)
	{
		j = -1;
		while (++j < canvas->win_size.y)
			draw_border_pixl(canvas, i, j, tmp);
	}
	free(tmp);
}
