/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 05:22:55 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 05:27:46 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc1_scrollbar_10(t_world *world, t_object obj, int y0)
{
	char	*str;
	char	*str2;

	if (obj.descriptor)
		str = obj.descriptor;
	else
	{
		str2 = ft_itoa(obj.id);
		str = ft_strjoin("Obj ", str2);
	}
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 168 - world->menu.rect.w / 2;
	world->menu.rect.y = y0 + 15;
	world->menu.rect.h = 25;
	ft_add_text(world, 0, str, world->menu.white_color);
	if (obj.descriptor == NULL)
	{
		free(str);
		free(str2);
	}
}

void	ft_menu_objects_bloc1_scrollbar_9(t_world *world, t_object obj, int y0)
{
	if (obj.id == world->menu.active_object)
	{
		world->menu.rect.x = world->canvas->win.w + 95;
		world->menu.rect.y = y0;
		world->menu.rect.w = 150;
		world->menu.rect.h = 50;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x666666);
		ft_add_menu_surface(world);
		ft_menu_objects_bloc1_scrollbar_10(world, obj, y0);
	}
	else
		ft_menu_objects_bloc1_scrollbar_11(world, obj, y0);
	ft_menu_objects_bloc1_scrollbar_12(world, obj, y0);
	ft_menu_objects_bloc1_scrollbar_13(world, obj, y0);
}

void	ft_menu_objects_bloc1_scrollbar_8(t_world *world, t_objlist *lst2,
		int *i, int *j)
{
	t_object	obj;
	int			y0;

	y0 = 145 + *i * (50 + 15) - (world->menu.scroll_objects.pos
			* world->menu.fact_objects);
	if ((y0 >= 135 && y0 <= 400) || ((y0 + 50) >= 135 &&
				(y0 + 50) <= 400))
	{
		obj = *(lst2->object);
		if (world->menu.first_object == -1)
			world->menu.first_object = y0;
		world->menu.objects[*j].x = obj.id;
		world->menu.objects[*j].y = 1;
		*j += 1;
		(world->menu.nb_objects)++;
		world->menu.rect.x = world->canvas->win.w + 95;
		world->menu.rect.y = y0;
		world->menu.rect.w = 320;
		world->menu.rect.h = 50;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
		ft_menu_objects_bloc1_scrollbar_9(world, obj, y0);
	}
}

void	ft_menu_objects_bloc1_scrollbar_7(t_world *world, t_cobjlist *lst,
		int *i, int *j)
{
	t_objlist	*lst2;
	t_cobject	cobj;

	cobj = *(lst->cobject);
	lst2 = cobj.objlist;
	*i += 1;
	if (cobj.descriptor && (ft_strcmp(cobj.descriptor, "obj") == 0 ||
				ft_strcmp(cobj.descriptor, "adn") == 0 ||
				ft_strcmp(cobj.descriptor, "sphere_torus") == 0))
	{
		while (lst2 != NULL)
			lst2 = lst2->next;
	}
	else
	{
		while (lst2 != NULL)
		{
			ft_menu_objects_bloc1_scrollbar_8(world, lst2, i, j);
			lst2 = lst2->next;
			*i += 1;
		}
	}
}

void	ft_menu_objects_bloc1_scrollbar_6(t_world *world, t_cobject cobj,
		int y0)
{
	t_bmp_parser	bmp;

	if (cobj.pert == e_none)
		bmp = world->menu.none;
	else if (cobj.pert == e_ripple)
		bmp = world->menu.ripple;
	else if (cobj.pert == e_waves)
		bmp = world->menu.waves;
	else if (cobj.pert == e_noise)
		bmp = world->menu.noise;
	else if (cobj.pert == e_chess)
		bmp = world->menu.chess;
	else if (cobj.pert == e_perlin)
		bmp = world->menu.perlin;
	else
		bmp = world->menu.marble;
	world->menu.rect.x = world->canvas->win.w + 350;
	world->menu.rect.y = y0 + 5;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	ft_fill_menu_surface_3(world, bmp, 0x222222);
	ft_add_menu_surface(world);
}
