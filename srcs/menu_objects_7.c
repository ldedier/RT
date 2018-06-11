/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_objects_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:56:24 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 09:01:34 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_objects_bloc1_scrollbar(t_world *world)
{
	t_cobjlist	*lst;
	t_objlist	*lst2;
	t_cobject	cobj;
	t_object	obj;
	char		*str;
	char		*str2;
	int			i;
	int			j;
	int			y0;
	int			y1;
	
	i = 0;
	j = 0;
	world->menu.nb_objects = 0;
	world->menu.first_object = -1;
	lst = world->cobjlist;
	while (lst != NULL)
	{
		y0 = 145 + i * (50 + 15) - (world->menu.scroll_objects.pos
				* world->menu.fact_objects);
		y1 = y0 + 50;
		if ((y0 >= 135 && y0 <= 400) || (y1 >= 135 && y1 <= 400))
		{
			cobj = *(lst->cobject);

			if (world->menu.first_object == -1)
				world->menu.first_object = y0;
			world->menu.objects[j].x = cobj.id;
			world->menu.objects[j].y = 0;
			j++;
			(world->menu.nb_objects)++;
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
				str2 = ft_itoa(cobj.id);
				str = ft_strjoin("Cobj ", str2);
				world->menu.rect.w = 10 * (1 + ft_strlen(str));
				world->menu.rect.x = world->canvas->win.w + 128 - world->menu.rect.w / 2;
				world->menu.rect.y = y0 + 15;
				world->menu.rect.h = 25;
				ft_add_text(world, 0, str, world->menu.white_color);
				free(str);
				free(str2);
			}
			else
			{
				str2 = ft_itoa(cobj.id);
				str = ft_strjoin("Cobj ", str2);
				world->menu.rect.w = 10 * (1 + ft_strlen(str));
				world->menu.rect.x = world->canvas->win.w + 128 - world->menu.rect.w / 2;
				world->menu.rect.y = y0 + 15;
				world->menu.rect.h = 25;
				ft_add_text(world, 0, str, world->menu.black_color);
				free(str);
				free(str2);
			}
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
			t_bmp_parser bmp;
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
		lst2 = lst->cobject->objlist;
		i++;
		//printf("%s\n", cobj.name);
		if (0)
		{
			lst2 = lst2->next;
			i++;
		}
		else
		{
			while (lst2 != NULL)
			{
				y0 = 145 + i * (50 + 15) - (world->menu.scroll_objects.pos * world->menu.fact_objects);
				y1 = y0 + 50;
				if ((y0 >= 135 && y0 <= 400) || (y1 >= 135 && y1 <= 400))
				{
					obj = *(lst2->object);

					if (world->menu.first_object == -1)
						world->menu.first_object = y0;
					world->menu.objects[j].x = obj.id;
					world->menu.objects[j].y = 1;
					j++;
					(world->menu.nb_objects)++;

					world->menu.rect.x = world->canvas->win.w + 95;
					world->menu.rect.y = y0;
					world->menu.rect.w = 320;
					world->menu.rect.h = 50;
					ft_new_menu_surface(world);
					SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
					ft_add_menu_surface(world);
					if (obj.id == world->menu.active_object)
					{
						world->menu.rect.x = world->canvas->win.w + 95;
						world->menu.rect.y = y0;
						world->menu.rect.w = 150;
						world->menu.rect.h = 50;
						ft_new_menu_surface(world);
						SDL_FillRect(world->menu.surface, NULL, 0x666666);
						ft_add_menu_surface(world);
						str2 = ft_itoa(obj.id);
						str = ft_strjoin("Obj ", str2);
						world->menu.rect.w = 10 * (1 + ft_strlen(str));
						world->menu.rect.x = world->canvas->win.w + 168 - world->menu.rect.w / 2;
						world->menu.rect.y = y0 + 15;
						world->menu.rect.h = 25;
						ft_add_text(world, 0, str, world->menu.white_color);
						free(str);
						free(str2);
					}
					else
					{
						str2 = ft_itoa(obj.id);
						str = ft_strjoin("Obj ", str2);
						world->menu.rect.w = 10 * (1 + ft_strlen(str));
						world->menu.rect.x = world->canvas->win.w + 168 - world->menu.rect.w / 2;
						world->menu.rect.y = y0 + 15;
						world->menu.rect.h = 25;
						ft_add_text(world, 0, str, world->menu.black_color);
						free(str);
						free(str2);
					}
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
					SDL_FillRect(world->menu.surface, NULL, obj.c.col);
					ft_add_menu_surface(world);
					t_bmp_parser bmp;
					if (obj.pert == e_none)
						bmp = world->menu.none;
					else if (obj.pert == e_ripple)
						bmp = world->menu.ripple;
					else if (obj.pert == e_waves)
						bmp = world->menu.waves;
					else if (obj.pert == e_noise)
						bmp = world->menu.noise;
					else if (obj.pert == e_chess)
						bmp = world->menu.chess;
					else if (obj.pert == e_perlin)
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
				lst2 = lst2->next;
				i++;
			}
		}
		lst = lst->next;
	}
}
