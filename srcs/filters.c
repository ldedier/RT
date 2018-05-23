/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/22 07:14:15 by lcavalle         ###   ########.fr       */
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
