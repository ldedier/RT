/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_tools_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 06:55:35 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 08:12:49 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_fill_menu_surface(t_world *world, t_bmp_parser bmp)
{
	int		*pix;
	int		x;
	int		y;

	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		x = 0;
		while (x < bmp.width)
		{
			pix[y * world->menu.rect.w + x] =
				ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
}

void	ft_fill_menu_surface_2(t_world *world, t_bmp_parser bmp, int color)
{
	int		*pix;
	int		x;
	int		y;

	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		x = 0;
		while (x < bmp.width)
		{
			if (y < 2)
				pix[y * world->menu.rect.w + x] = color;
			else
				pix[y * world->menu.rect.w + x] =
					ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
}

void	ft_fill_menu_surface_3(t_world *world, t_bmp_parser bmp, int color)
{
	int		*pix;
	int		x;
	int		y;

	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		x = 0;
		while (x < bmp.width)
		{
			if (x < 2 || x >= (bmp.width - 2) || y < 2 || y >= (bmp.height - 2))
				pix[y * world->menu.rect.w + x] = color;
			else
				pix[y * world->menu.rect.w + x] =
					ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
}
