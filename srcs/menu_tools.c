/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:29:57 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 00:30:00 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_color_hue(t_world *world)
{
	int		x;
	int		y;
	int		*pix;

	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < world->menu.rect.h)
	{
		x = 0;
		while (x < world->menu.rect.w)
		{
			pix[y * world->menu.rect.w + x] =
				world->menu.color_map[y * world->menu.rect.w + x].col;
			x++;
		}
		y++;
	}
}

void	ft_switch_filter_1(t_world *world, int filter)
{
	if (filter == 0)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 58;
		world->menu.rect.w = 80;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Gauss Blur", world->menu.black_color);
	}
	else if (filter == 1)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 68;
		world->menu.rect.w = 60;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Sharpen", world->menu.black_color);
	}
	else
	{
		world->menu.rect.x = world->menu.filters.pos.x + 72;
		world->menu.rect.w = 48;
		world->menu.rect.h = 18;
		ft_add_text(world, 1, "Sobel", world->menu.black_color);
	}
}

void	ft_switch_filter_2(t_world *world, int filter)
{
	if (filter == 3)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 70;
		world->menu.rect.w = 56;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Emboss", world->menu.black_color);
	}
	else if (filter == 4)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 75;
		world->menu.rect.w = 42;
		world->menu.rect.h = 18;
		ft_add_text(world, 1, "Grey", world->menu.black_color);
	}
	else
	{
		world->menu.rect.x = world->menu.filters.pos.x + 57;
		world->menu.rect.w = 85;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Motion Blur", world->menu.black_color);
	}
}

void	ft_switch_filter(t_world *world, int filter, int pos)
{
	world->menu.rect.y = world->menu.filters.pos.y +
		pos * (world->menu.filters.size.y + 2) + 9;
	if (filter <= 2)
		ft_switch_filter_1(world, filter);
	else if (filter <= 5)
		ft_switch_filter_2(world, filter);
	else
	{
		world->menu.rect.x = world->menu.filters.pos.x + 72;
		world->menu.rect.w = 47;
		world->menu.rect.h = 18;
		ft_add_text(world, 1, "None", world->menu.black_color);
	}
}

void	ft_show_filters(t_world *world)
{
	int		i;

	world->menu.rect.x = world->menu.filters.pos.x;
	world->menu.rect.y = world->menu.filters.pos.y +
		world->menu.filters.size.y + 2;
	world->menu.rect.w = world->menu.filters.size.x;
	world->menu.rect.h = (e_nfilters - 1) * (world->menu.filters.size.y + 2);
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	i = 1;
	while (i < (e_nfilters + 1))
	{
		world->menu.rect.x = world->menu.filters.pos.x;
		world->menu.rect.y = world->menu.filters.pos.y +
			i * (world->menu.filters.size.y + 2);
		world->menu.rect.w = world->menu.filters.size.x;
		world->menu.rect.h = world->menu.filters.size.y;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
		ft_switch_filter(world, world->menu.filters_list[i], i);
		i++;
	}
}
