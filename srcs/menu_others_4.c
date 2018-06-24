/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_others_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 07:05:31 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 00:26:12 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_others_bloc2_photo(t_world *world)
{
	t_bmp_parser	bmp;

	bmp = world->menu.photo;
	world->menu.rect.x = world->canvas->win.w + 95;
	world->menu.rect.y = 750;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface_2(world, bmp, 0xF8F8FF);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_cartoon(t_world *world)
{
	t_bmp_parser	bmp;

	if (world->shader == 2)
		bmp = world->menu.cartoon2;
	else
		bmp = world->menu.cartoon;
	world->menu.rect.x = world->canvas->win.w + 75;
	world->menu.rect.y = 565;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface_2(world, bmp, 0x222222);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_grangebars_3(t_world *world, int i, int pos)
{
	world->menu.rect.x = pos;
	world->menu.rect.y = world->menu.others_grb[i].pix.y - 3;
	world->menu.rect.w = 8;
	world->menu.rect.h = 12;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
}

void	ft_menu_others_bloc1_grangebars_2(t_world *world, int i, int nb_val,
		float step)
{
	int		j;
	int		pos;

	j = 0;
	while (j < nb_val)
	{
		world->menu.rect.x = world->menu.others_grb[i].pix.x + j * step;
		world->menu.rect.y = world->menu.others_grb[i].pix.y - 2;
		world->menu.rect.w = 2;
		world->menu.rect.h = 10;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x666666);
		ft_add_menu_surface(world);
		j++;
	}
	pos = world->menu.others_grb[i].pix.x
		+ (*(world->menu.others_grb[i].value)
				- world->menu.others_grb[i].min) * step - 2;
	if (pos >= (world->menu.others_grb[i].pix.x - 8) &&
			pos <= (world->menu.others_grb[i].pix.x + 108))
		ft_menu_others_bloc1_grangebars_3(world, i, pos);
}

void	ft_menu_others_bloc1_grangebars(t_world *world)
{
	int		i;
	int		nb_val;
	float	step;

	i = 0;
	while (i < world->menu.nb_others_grb)
	{
		world->menu.rect.x = world->menu.others_grb[i].pix.x;
		world->menu.rect.y = world->menu.others_grb[i].pix.y;
		world->menu.rect.w = 108;
		world->menu.rect.h = 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x888888);
		ft_add_menu_surface(world);
		nb_val = world->menu.others_grb[i].max
			- world->menu.others_grb[i].min + 1;
		step = 108 / (float)(nb_val - 1);
		ft_menu_others_bloc1_grangebars_2(world, i, nb_val, step);
		i++;
	}
}
