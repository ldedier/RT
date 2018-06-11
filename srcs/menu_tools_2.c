/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:39:49 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 01:02:27 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_sort_menu_filters(t_world *world)
{
	int			changed;
	int			i;
	int			tmp;

	changed = 1;
	while (changed == 1)
	{
		changed = 0;
		i = 1;
		while ((i + 1) < (e_nfilters + 1))
		{
			if (world->menu.filters_list[i] > world->menu.filters_list[i + 1])
			{
				tmp = world->menu.filters_list[i];
				world->menu.filters_list[i] = world->menu.filters_list[i + 1];
				world->menu.filters_list[i + 1] = tmp;
				changed = 1;
			}
			i++;
		}
	}
}

int		ft_set_selected_object(t_world *world, int id)
{
	t_cobjlist	*lst;
	t_objlist	*lst2;

	lst = world->cobjlist;
	while (lst != NULL)
	{
		if (lst->cobject->id == id)
		{
			world->selected_cobject = lst->cobject;
			return (1);
		}
		lst2 = lst->cobject->objlist;
		while (lst2 != NULL)
		{
			if (lst2->object->id == id)
			{
				world->selected_object = lst2->object;
				return (1);
			}
			lst2 = lst2->next;
		}
		lst = lst->next;
	}
	return (0);
}

int		ft_color_pos_3(t_color color, t_color c, float *dist)
{
	float		tmp;

	tmp = sqrt((c.r - color.r) * (c.r - color.r) + (c.g - color.g) *
			(c.g - color.g) + (c.b - color.b) * (c.b - color.b));
	if (tmp < *dist)
	{
		*dist = tmp;
		return (1);
	}
	return (0);
}

void	ft_color_pos_2(t_world *world, t_color color, t_pixel *pix, int y)
{
	t_color		c;
	float		dist;
	int			x;

	dist = 100;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			c.r = world->menu.color_map[y * 100 + x].r;
			c.g = world->menu.color_map[y * 100 + x].g;
			c.b = world->menu.color_map[y * 100 + x].b;
			if (ft_color_pos_3(color, c, &dist) == 1)
			{
				pix->x = x;
				pix->y = y;
			}
			x++;
		}
		y++;
	}
}

t_pixel	ft_color_pos(t_world *world, t_color color)
{
	int			x;
	int			y;
	t_pixel		pix;

	pix.x = 0;
	pix.y = 0;
	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			if (world->menu.color_map[y * 100 + x].col == color.col)
			{
				pix.x = x;
				pix.y = y;
				return (pix);
			}
			x++;
		}
		y++;
	}
	y = 0;
	ft_color_pos_2(world, color, &pix, y);
	return (pix);
}
