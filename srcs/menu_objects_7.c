/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:56:24 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 05:29:15 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc1_scrollbar_5(t_world *world, t_cobject cobj,
		int y0)
{
	char	*str;
	char	*str2;

	if (cobj.descriptor)
		str = cobj.descriptor;
	else
	{
		str2 = ft_itoa(cobj.id);
		str = ft_strjoin("Cobj ", str2);
	}
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 128
		- world->menu.rect.w / 2;
	world->menu.rect.y = y0 + 15;
	world->menu.rect.h = 25;
	ft_add_text(world, 0, str, world->menu.black_color);
	if (cobj.descriptor == NULL)
	{
		free(str);
		free(str2);
	}
}

void	ft_menu_objects_bloc1_scrollbar_4(t_world *world, t_cobject cobj,
		int y0)
{
	char	*str;
	char	*str2;

	if (cobj.descriptor)
		str = cobj.descriptor;
	else
	{
		str2 = ft_itoa(cobj.id);
		str = ft_strjoin("Cobj ", str2);
	}
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 128
		- world->menu.rect.w / 2;
	world->menu.rect.y = y0 + 15;
	world->menu.rect.h = 25;
	ft_add_text(world, 0, str, world->menu.white_color);
	if (cobj.descriptor == NULL)
	{
		free(str);
		free(str2);
	}
}

void	ft_menu_objects_bloc1_scrollbar_3(t_world *world, t_cobject cobj,
		int y0)
{
	world->menu.rect.x = world->canvas->win.w + 55;
	world->menu.rect.y = y0;
	world->menu.rect.w = 360;
	world->menu.rect.h = 50;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	if (cobj.id == world->menu.active_object)
	{
		world->menu.rect.x = world->canvas->win.w + 55;
		world->menu.rect.y = y0;
		world->menu.rect.w = 150;
		world->menu.rect.h = 50;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x666666);
		ft_add_menu_surface(world);
		ft_menu_objects_bloc1_scrollbar_4(world, cobj, y0);
	}
	else
		ft_menu_objects_bloc1_scrollbar_5(world, cobj, y0);
}

void	ft_menu_objects_bloc1_scrollbar_2(t_world *world, t_cobject cobj,
		int y0, int *j)
{
	world->menu.objects[*j].x = cobj.id;
	world->menu.objects[*j].y = 0;
	*j += 1;
	(world->menu.nb_objects)++;
	ft_menu_objects_bloc1_scrollbar_3(world, cobj, y0);
	world->menu.rect.x = world->canvas->win.w + 275;
	world->menu.rect.y = y0 + 17;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 278;
	world->menu.rect.y = y0 + 20;
	world->menu.rect.w = 34;
	world->menu.rect.h = 14;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, cobj.c.col);
	ft_add_menu_surface(world);
	ft_menu_objects_bloc1_scrollbar_6(world, cobj, y0);
}

void	ft_menu_objects_bloc1_scrollbar(t_world *world)
{
	t_cobjlist	*lst;
	t_cobject	cobj;
	int			i;
	int			j;
	int			y0;

	i = 0;
	j = 0;
	world->menu.nb_objects = 0;
	world->menu.first_object = -1;
	lst = world->cobjlist;
	while (lst != NULL)
	{
		y0 = 145 + i * (50 + 15) - (world->menu.scroll_objects.pos
				* world->menu.fact_objects);
		if ((y0 >= 135 && y0 <= 400) || ((y0 + 50) >= 135 && (y0 + 50) <= 400))
		{
			cobj = *(lst->cobject);
			if (world->menu.first_object == -1)
				world->menu.first_object = y0;
			ft_menu_objects_bloc1_scrollbar_2(world, cobj, y0, &j);
		}
		ft_menu_objects_bloc1_scrollbar_7(world, lst, &i, &j);
		lst = lst->next;
	}
}
