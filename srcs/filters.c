/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 03:02:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 18:03:12 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	motion_blur_12(double *filter)
{
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
}

void		motion_blur(t_canvas *canvas)
{
	double	*filter;

	if (!(filter = ft_memalloc(sizeof(double) * 25)))
		ft_error("error malloc");
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
	motion_blur_12(filter);
	convolute(canvas, filter, 5, 7);
	free(filter);
}

void		gauss_blur(t_canvas *canvas)
{
	double	*filter;

	if (!(filter = ft_memalloc(sizeof(double) * 9)))
		ft_error("error malloc");
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

	if (!(filter = ft_memalloc(sizeof(double) * 9)))
		ft_error("error malloc");
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

	if (!(filter = ft_memalloc(sizeof(double) * 9)))
		ft_error("error malloc");
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
