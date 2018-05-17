/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/17 05:48:05 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	apply_filter(t_canvas *canvas, int *filter, int filter_size)
{
	int			*img;
	int			*aux;
	t_pixel		pix;
	t_pixel		fil;
	t_intcolor	c;

	img = canvas->surface->pixels;
	aux = ft_memalloc(sizeof(int) * canvas->win_size.x * canvas->win_size.y);
	pix.x = 0;
	while (++pix.x < canvas->win_size.x - 1)
	{
		pix.y = 0;
		while (++pix.y < canvas->win_size.y - 1)
		{
			fil.x = -filter_size / 2 - 1;
			c = new_intcolor();
			while (++fil.x <= filter_size / 2)
			{
				fil.y = -filter_size / 2 - 1;
				while (++fil.y <= filter_size / 2)
				{
					c = add_scale_intcolors(c, get_intcolor(img[pix.x + fil.x +
							(pix.y + fil.y) * canvas->win_size.x]),
							filter[fil.x + fil.y * filter_size]);
				}
			}
			aux[pix.x + pix.y * canvas->win_size.x] = scale_convert_color(c,
				(double)1 / filter_size / filter_size).col;	
		}
	}
	free(img);
	canvas->surface->pixels = aux;
}

void		blur(t_canvas *canvas)
{
	int i;
	int j;
	int	*filter;

	filter = ft_memalloc(FILTER_SIZE * FILTER_SIZE);
	i = -1;
	while (++i < FILTER_SIZE)
	{
		j = -1;
		while (++j < FILTER_SIZE)
			filter[i + j * FILTER_SIZE] = 1;
	}
	apply_filter(canvas, filter, FILTER_SIZE);
	free(filter);
}
