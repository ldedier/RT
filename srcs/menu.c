/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:29:20 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/09 01:58:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_new_menu_surface(t_world *world)
{
	if (!(world->menu.surface = SDL_CreateRGBSurface(0,
					world->menu.rect.w, world->menu.rect.h, 32, 0, 0, 0, 0)))
		ft_error("could not create surface");
}

void	ft_add_menu_surface(t_world *world)
{
	if (!(world->menu.texture = SDL_CreateTextureFromSurface(world->
					canvas->renderer, world->menu.surface)))
		ft_error("could not create menu texture");
	SDL_RenderCopy(world->canvas->renderer, world->menu.texture, NULL,
			&(world->menu.rect));
	SDL_DestroyTexture(world->menu.texture);
	world->menu.texture = NULL;
	SDL_FreeSurface(world->menu.surface);
	world->menu.surface = NULL;
}

void	ft_add_text(t_world *world, int font, char *text)
{
	world->menu.surface = TTF_RenderText_Solid(world->menu.fonts[font], text, world->menu.color);
	world->menu.texture = SDL_CreateTextureFromSurface(world->canvas->renderer, world->menu.surface);
	SDL_RenderCopy(world->canvas->renderer, world->menu.texture, NULL, &(world->menu.rect));
	SDL_DestroyTexture(world->menu.texture);
	world->menu.texture = NULL;
	SDL_FreeSurface(world->menu.surface);
	world->menu.surface = NULL;
}

void	ft_add_header_text(t_world *world)
{
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;

	world->menu.rect.x = world->canvas->win.w + 20 + 10 + 7;
	world->menu.rect.y = 20 + 10 + 4;
	world->menu.rect.w = 125;
	world->menu.rect.h = 35;
	ft_add_text(world, 0, "Objects");

	world->menu.rect.x = world->canvas->win.w + 20 + 10 + 140 + 10 + 12;
	world->menu.rect.y = 20 + 10 + 5;
	world->menu.rect.w = 115;
	world->menu.rect.h = 32;
	ft_add_text(world, 0, "Lights");

	world->menu.rect.x = world->canvas->win.w + 20 + 10 + 140 + 10 + 140 + 10 + 11;
	world->menu.rect.y = 20 + 10 + 5;
	world->menu.rect.w = 120;
	world->menu.rect.h = 33;
	ft_add_text(world, 0, "Others");
}

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
			pix[y * world->menu.rect.w + x] = world->menu.color_map[y * world->menu.rect.w + x].col;
			x++;
		}
		y++;
	}
}

void	ft_menu_objects(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 20 + 10;
	world->menu.rect.y = 20 + 10;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);

	//<-- BLOC_1 -->
	world->menu.rect.x = world->canvas->win.w + 20 + 20;
	world->menu.rect.y = 135;
	world->menu.rect.w = MENU_WIDTH - 40 - 40;
	world->menu.rect.h = world->menu.scroll_lights.len;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);

	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_lights.len - 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);

	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140 + world->menu.scroll_objects.pos;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_objects.height;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);

	t_cobjlist	*lst;
	t_objlist	*lst2;
	t_cobject	cobj;
	t_object	obj;
	world->menu.nb_objects = 0;
	int i = 0;
	lst = world->cobjlist;
	while (lst != NULL)
	{
		int y0 = 145 + i * (50 + 15) - (world->menu.scroll_objects.pos * world->menu.fact_objects);
		int y1 = y0 + 50;
		if ((y0 >= 135 && y0 <= 400) || (y1 >= 135 && y1 <= 400))
		{
			(world->menu.nb_objects)++;
			world->menu.rect.x = world->canvas->win.w + 55;
			world->menu.rect.y = y0;
			world->menu.rect.w = 360;
			world->menu.rect.h = 50;
			ft_new_menu_surface(world);
			SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
			ft_add_menu_surface(world);
		}
		cobj = *(lst->cobject);
		printf("COBJ %d\n", cobj.id);
		lst2 = lst->cobject->objlist;
		i++;
		while(lst2 != NULL)
		{
			y0 = 145 + i * (50 + 15) - (world->menu.scroll_objects.pos * world->menu.fact_objects);
			y1 = y0 + 50;
			if ((y0 >= 135 && y0 <= 400) || (y1 >= 135 && y1 <= 400))
			{
				(world->menu.nb_objects)++;
				world->menu.rect.x = world->canvas->win.w + 55 + 20;
				world->menu.rect.y = y0;
				world->menu.rect.w = 360 - 20;
				world->menu.rect.h = 50;
				ft_new_menu_surface(world);
				SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
				ft_add_menu_surface(world);
			}
			obj = *(lst2->object);
			printf("\tOBJ %d\n", obj.id);
			lst2 = lst2->next;
			i++;
		}
		lst = lst->next;
	}
	//<-- /BLOC_1 -->
}

void	ft_menu_lights(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 20 + 10 + 140 + 10;
	world->menu.rect.y = 20 + 10;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);

	//<-- BLOC_1 -->
	world->menu.rect.x = world->canvas->win.w + 20 + 20;
	world->menu.rect.y = 135;
	world->menu.rect.w = MENU_WIDTH - 40 - 40;
	world->menu.rect.h = world->menu.scroll_lights.len;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);

	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_lights.len - 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);

	world->menu.rect.x = world->canvas->win.w + 443;
	world->menu.rect.y = 140 + world->menu.scroll_lights.pos;
	world->menu.rect.w = 10;
	world->menu.rect.h = world->menu.scroll_lights.height;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);

	int i = 0;
	int j = 0;
	char *str;
	world->menu.nb_lights = 0;
	world->menu.first_light.x = -1;
	while (i < world->nlights)
	{
		int y0 = 145 + i * (50 + 15) - (world->menu.scroll_lights.pos * world->menu.fact_lights);
		int y1 = y0 + 50;
		if ((y0 >= 135 && y0 <= 400) || (y1 >= 135 && y1 <= 400))
		{
			if (world->menu.first_light.x == -1)
			{
				world->menu.first_light.x = i;
				world->menu.first_light.y = y0;
			}
			world->menu.lights[j++] = i;
			(world->menu.nb_lights)++;
			world->menu.rect.x = world->canvas->win.w + 55;
			world->menu.rect.y = y0;
			world->menu.rect.w = 360;
			world->menu.rect.h = 50;
			ft_new_menu_surface(world);
			SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
			ft_add_menu_surface(world);
			if (i == world->menu.active_light)
			{
				world->menu.rect.x = world->canvas->win.w + 55;
				world->menu.rect.y = y0;
				world->menu.rect.w = 140;
				world->menu.rect.h = 50;
				ft_new_menu_surface(world);
				SDL_FillRect(world->menu.surface, NULL, 0x666666);
				ft_add_menu_surface(world);
				world->menu.color.r = 255;
				world->menu.color.g = 255;
				world->menu.color.b = 255;
				world->menu.color.a = 255;
				world->menu.rect.x = world->canvas->win.w + 50 + 30;
				world->menu.rect.y = y0 + 15;
				world->menu.rect.w = 85;
				world->menu.rect.h = 25;
				str = ft_strjoin("Light ", ft_itoa(i));
				ft_add_text(world, 0, str);
				free(str);
			}
			else
			{
				world->menu.color.r = 0;
				world->menu.color.g = 0;
				world->menu.color.b = 0;
				world->menu.color.a = 0;
				world->menu.rect.x = world->canvas->win.w + 50 + 30;
				world->menu.rect.y = y0 + 15;
				world->menu.rect.w = 85;
				world->menu.rect.h = 25;
				str = ft_strjoin("Light ", ft_itoa(i));
				ft_add_text(world, 0, str);
				free(str);
			}
			world->menu.rect.x = world->canvas->win.w + 50 + 205;
			world->menu.rect.y = y0 + 17;
			world->menu.rect.w = 40;
			world->menu.rect.h = 20;
			ft_new_menu_surface(world);
			SDL_FillRect(world->menu.surface, NULL, 0x222222);
			ft_add_menu_surface(world);
			world->menu.rect.x = world->canvas->win.w + 50 + 205 + 3;
			world->menu.rect.y = y0 + 17 + 3;
			world->menu.rect.w = 34;
			world->menu.rect.h = 14;
			ft_new_menu_surface(world);
			SDL_FillRect(world->menu.surface, NULL, world->lights[i].c.col);
			ft_add_menu_surface(world);
			t_bmp_parser bmp;
			if (world->lights[i].type == 'p')
				bmp = world->menu.light_point_t;
			else if (world->lights[i].type == 's')
				bmp = world->menu.light_spotlight_t;
			else
				bmp = world->menu.light_directional_t;
			world->menu.rect.x = world->canvas->win.w + 50 + 300;
			world->menu.rect.y = y0 + 5;
			world->menu.rect.w = bmp.width;
			world->menu.rect.h = bmp.height;
			ft_new_menu_surface(world);
			int *pix = (int *)(world->menu.surface->pixels);
			int y = 0;
			while (y < bmp.height)
			{
				int x = 0;
				while (x < bmp.width)
				{
					if (x < 2 || x >= (bmp.width - 2) || y < 2 || y >= (bmp.height - 2))
						pix[y * world->menu.rect.w + x] = 0x222222;
					else
						pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
					x++;
				}
				y++;
			}
			ft_add_menu_surface(world);
		}
		i++;
	}
	world->menu.rect.x = world->canvas->win.w + 55;
	world->menu.rect.y = 80;
	world->menu.rect.w = 360;
	world->menu.rect.h = 55;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 55;
	world->menu.rect.y = 400;
	world->menu.rect.w = 360;
	world->menu.rect.h = 65;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	//<--/ BLOC_1 -->

	if (world->nlights > 0)
	{
	//<-- BLOC_2 -->
	world->menu.rect.x = world->canvas->win.w + 20 + 20;
	world->menu.rect.y = 135 + 265 + 20;
	world->menu.rect.w = MENU_WIDTH - 40 - 40;
	world->menu.rect.h = 440;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	//<-- POSITION -->
	world->menu.rect.x = world->canvas->win.w + 40 + 25;
	world->menu.rect.y = 135 + 265 + 20 + 20;
	world->menu.rect.w = 280;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 40 + 25;
	world->menu.rect.y = 135 + 265 + 20 + 20;
	world->menu.rect.w = 120;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 17;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 10;
	world->menu.rect.w = 85;
	world->menu.rect.h = 22;
	ft_add_text(world, 1, "Position");
	world->menu.color.r = 0;
	world->menu.color.g = 0;
	world->menu.color.b = 0;
	world->menu.color.a = 0;
	char *str = ft_itoa((int)(world->lights[world->menu.active_light].o.x));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 30 + 120 - world->menu.rect.w / 2;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 10;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str);
	free(str);
	str = ft_itoa((int)(world->lights[world->menu.active_light].o.y));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 30 + 120 + 47 - world->menu.rect.w / 2;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 10;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str);
	free(str);
	str = ft_itoa((int)(world->lights[world->menu.active_light].o.z));
	world->menu.rect.w = 10 * (1 + ft_strlen(str));
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 30 + 120 + 94 - world->menu.rect.w / 2;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 10;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, str);
	free(str);
	//<-- /POSITION -->
	//<-- ANGLE -->
	world->menu.rect.x = world->canvas->win.w + 40 + 25;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60;
	world->menu.rect.w = 280;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 40 + 25;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60;
	world->menu.rect.w = 120;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 27;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 10;
	world->menu.rect.w = 65;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Angle");
	//<-- /AMGLE -->
	//<-- EBLOUI -->
	t_bmp_parser bmp = world->menu.ebloui;
	if (1)
	{
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 280 + 20 - 3;
		world->menu.rect.y = 135 + 265 + 20 + 15 - 3;
		world->menu.rect.w = bmp.width + 6;
		world->menu.rect.h = bmp.height + 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
	}
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 280 + 20;
	world->menu.rect.y = 135 + 265 + 20 + 15;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	int *pix = (int *)(world->menu.surface->pixels);
	int y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	//<-- /EBLOUI -->
	//<-- STEREOSCOPE -->
	bmp = world->menu.stereoscope;
	if (1)
	{
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 280 + 20 - 3;
		world->menu.rect.y = 135 + 265 + 20 + 15 + 60 - 3;
		world->menu.rect.w = bmp.width + 6;
		world->menu.rect.h = bmp.height + 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
	}
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 280 + 20;
	world->menu.rect.y = 135 + 265 + 20 + 15 + 60;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	//<-- /STEREOSCOPE -->
	//<-- INTENSITY_COLOR -->
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 20;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60;
	world->menu.rect.w = 150;
	world->menu.rect.h = 170;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.lights_cp[0].pix.x;
	world->menu.rect.y = world->menu.lights_cp[0].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
	t_color	color;
	color.r = 255 - world->menu.lights_cp[0].color->r;
	color.g = 255 - world->menu.lights_cp[0].color->g;
	color.b = 255 - world->menu.lights_cp[0].color->b;
	color.col = (color.r << 16) | (color.g << 8) | color.b;
	world->menu.rect.x = world->menu.lights_cp[0].pix.x + world->menu.lights_cp[0].pos.x - 5;
	world->menu.rect.y = world->menu.lights_cp[0].pix.y + world->menu.lights_cp[0].pos.y - 1;
	world->menu.rect.w = 10;
	world->menu.rect.h = 2;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.lights_cp[0].pix.x + world->menu.lights_cp[0].pos.x - 1;
	world->menu.rect.y = world->menu.lights_cp[0].pix.y + world->menu.lights_cp[0].pos.y - 5;
	world->menu.rect.w = 2;
	world->menu.rect.h = 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);

	//<-- /INTENSITY_COLOR -->
	//<-- ROTATION -->
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 20 + 150 + 30;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60;
	world->menu.rect.w = 150;
	world->menu.rect.h = 170;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 20 + 150 + 30;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60;
	world->menu.rect.w = 150;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 20 + 150 + 30 + 34;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60 + 9;
	world->menu.rect.w = 85;
	world->menu.rect.h = 24;
	ft_add_text(world, 1, "Rotation");
	//<-- /ROTATION -->
	//<-- TYPE -->
	world->menu.rect.x = world->canvas->win.w + 40 + 25;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60 + 170 + 20;
	world->menu.rect.w = 370;
	world->menu.rect.h = 90;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	if (world->lights[world->menu.active_light].type == 'p')
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 - 10;
	else if (world->lights[world->menu.active_light].type == 's')
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 + 115 - 10;
	else
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 + 230 - 10;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60 + 170 + 20 + 15 - 10;
	world->menu.rect.w = 80;
	world->menu.rect.h = 80;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	if (world->lights[world->menu.active_light].type == 'p')
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 - 2;
	else if (world->lights[world->menu.active_light].type == 's')
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 + 115 - 2;
	else
		world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 + 230 - 2;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60 + 170 + 20 + 15 - 2;
	world->menu.rect.w = 64;
	world->menu.rect.h = 64;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);

	bmp = world->menu.light_point;
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60 + 170 + 20 + 15;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	bmp = world->menu.light_spotlight;
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 + 115;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60 + 170 + 20 + 15;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	bmp = world->menu.light_directional;
	world->menu.rect.x = world->canvas->win.w + 40 + 25 + 40 + 230;
	world->menu.rect.y = 135 + 265 + 20 + 20 + 60 + 60 + 170 + 20 + 15;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	//<-- /TYPE -->
	//<-- RANGEBARS -->
	i = 0;
	while (i < world->menu.nb_lights_rb)
	{
		world->menu.rect.x = world->menu.lights_rb[i].pix.x;
		world->menu.rect.y = world->menu.lights_rb[i].pix.y;
		world->menu.rect.w = 108;
		world->menu.rect.h = 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x888888);
		ft_add_menu_surface(world);
		if (i <= 1)
			world->menu.rect.x = world->menu.lights_rb[i].pix.x + ((*(world->menu.lights_rb[i].value) * 100) / world->menu.lights_rb[i].max);
		else
			world->menu.rect.x = world->menu.lights_rb[i].pix.x + (((*(world->menu.lights_rb[i].value) + 1) * 100) / world->menu.lights_rb[i].max);
		world->menu.rect.y = world->menu.lights_rb[i].pix.y - 3;
		world->menu.rect.w = 8;
		world->menu.rect.h = 12;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x222222);
		ft_add_menu_surface(world);
		i++;
	}
	//<-- /RANGEBARS -->
	//<-- /BLOC_2 -->
	}
}

void	ft_switch_filter(t_world *world, int filter, int pos)
{
	world->menu.rect.y = world->menu.filters.pos.y + pos * (world->menu.filters.size.y + 2) + 9;
	if (filter == 0)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 58;
		world->menu.rect.w = 80;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Gauss Blur");
	}
	else if (filter == 1)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 68;
		world->menu.rect.w = 60;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Sharpen");
	}
	else if (filter == 2)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 72;
		world->menu.rect.w = 48;
		world->menu.rect.h = 18;
		ft_add_text(world, 1, "Sobel");
	}
	else if (filter == 3)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 70;
		world->menu.rect.w = 56;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Emboss");
	}
	else if (filter == 4)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 75;
		world->menu.rect.w = 42;
		world->menu.rect.h = 18;
		ft_add_text(world, 1, "Grey");
	}
	else if (filter == 5)
	{
		world->menu.rect.x = world->menu.filters.pos.x + 57;
		world->menu.rect.w = 85;
		world->menu.rect.h = 20;
		ft_add_text(world, 1, "Motion Blur");
	}
	else
	{
		world->menu.rect.x = world->menu.filters.pos.x + 72;
		world->menu.rect.w = 47;
		world->menu.rect.h = 18;
		ft_add_text(world, 1, "None");
	}
}

void	ft_add_filter(t_world *world)
{
	world->menu.color.r = 0;
	world->menu.color.g = 0;
	world->menu.color.b = 0;
	world->menu.color.a = 0;
	ft_switch_filter(world, world->menu.filters_list[0], 0);
}

void	ft_show_filters(t_world *world)
{
	int		i;

	world->menu.rect.x = world->menu.filters.pos.x;
	world->menu.rect.y = world->menu.filters.pos.y + world->menu.filters.size.y + 2;
	world->menu.rect.w = world->menu.filters.size.x;
	world->menu.rect.h = (e_nfilters - 1) * (world->menu.filters.size.y + 2);
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	i = 1;
	while (i < (e_nfilters + 1))
	{
		world->menu.rect.x = world->menu.filters.pos.x;
		world->menu.rect.y = world->menu.filters.pos.y + i * (world->menu.filters.size.y + 2);
		world->menu.rect.w = world->menu.filters.size.x;
		world->menu.rect.h = world->menu.filters.size.y;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
		ft_add_menu_surface(world);
		ft_switch_filter(world, world->menu.filters_list[i], i);
		i++;
	}
}

void	ft_menu_others(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 20 + 10 + 140 + 10 + 140 + 10;
	world->menu.rect.y = 20 + 10;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);

	//<-- BLOC_1 -->
	world->menu.rect.x = world->canvas->win.w + 20 + 20;
	world->menu.rect.y = 20 + 60 + 30;
	world->menu.rect.w = MENU_WIDTH - 40 - 40;
	world->menu.rect.h = 530;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	//<-- AMBIENT -->
	world->menu.rect.x = world->canvas->win.w + 20 + 45;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 350 - 130 + 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 44;
	world->menu.rect.y = 140;
	world->menu.rect.w = 80;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Ambient");
	//<-- /AMBIENT -->
	//<-- FOG -->
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 200;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 350 - 130 + 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 200;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 44 + 220;
	world->menu.rect.y = 140;
	world->menu.rect.w = 40;
	world->menu.rect.h = 18;
	ft_add_text(world, 1, "Fog");
	//<-- /FOG -->
	//<-- AMBIENT_COLOR -->
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 64;
	world->menu.rect.y = 180;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 64 + 3;
	world->menu.rect.y = 180 + 3;
	world->menu.rect.w = 34;
	world->menu.rect.h = 14;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, world->menu.others_cp[0].color->col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[0].pix.x;
	world->menu.rect.y = world->menu.others_cp[0].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
	t_color	color;
	color.r = 255 - world->menu.others_cp[0].color->r;
	color.g = 255 - world->menu.others_cp[0].color->g;
	color.b = 255 - world->menu.others_cp[0].color->b;
	color.col = (color.r << 16) | (color.g << 8) | color.b;
	world->menu.rect.x = world->menu.others_cp[0].pix.x + world->menu.others_cp[0].pos.x - 5;
	world->menu.rect.y = world->menu.others_cp[0].pix.y + world->menu.others_cp[0].pos.y - 1;
	world->menu.rect.w = 10;
	world->menu.rect.h = 2;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[0].pix.x + world->menu.others_cp[0].pos.x - 1;
	world->menu.rect.y = world->menu.others_cp[0].pix.y + world->menu.others_cp[0].pos.y - 5;
	world->menu.rect.w = 2;
	world->menu.rect.h = 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	//<-- /AMBIENT_COLOR -->
	//<-- FOG_COLOR -->
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 64 + 200;
	world->menu.rect.y = 180;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 64 + 200 + 3;
	world->menu.rect.y = 180 + 3;
	world->menu.rect.w = 34;
	world->menu.rect.h = 14;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, world->menu.others_cp[1].color->col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[1].pix.x;
	world->menu.rect.y = world->menu.others_cp[1].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
	color.r = 255 - world->menu.others_cp[1].color->r;
	color.g = 255 - world->menu.others_cp[1].color->g;
	color.b = 255 - world->menu.others_cp[1].color->b;
	color.col = (color.r << 16) | (color.g << 8) | color.b;
	world->menu.rect.x = world->menu.others_cp[1].pix.x + world->menu.others_cp[1].pos.x - 5;
	world->menu.rect.y = world->menu.others_cp[1].pix.y + world->menu.others_cp[1].pos.y - 1;
	world->menu.rect.w = 10;
	world->menu.rect.h = 2;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[1].pix.x + world->menu.others_cp[1].pos.x - 1;
	world->menu.rect.y = world->menu.others_cp[1].pix.y + world->menu.others_cp[1].pos.y - 5;
	world->menu.rect.w = 2;
	world->menu.rect.h = 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, color.col);
	ft_add_menu_surface(world);
	//<-- /FOG_COLOR -->
	//<-- FILTER -->
	world->menu.rect.x = world->canvas->win.w + 20 + 45;
	world->menu.rect.y = 380;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 57;
	world->menu.rect.y = 390;
	world->menu.rect.w = 55;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Filter");
	world->menu.rect.x = world->menu.filters.pos.x;
	world->menu.rect.y = world->menu.filters.pos.y;
	world->menu.rect.w = world->menu.filters.size.x;
	world->menu.rect.h = world->menu.filters.size.y;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	ft_add_filter(world);
	//<-- /FILTER -->
	//<-- BOUNCE -->
	world->menu.rect.x = world->canvas->win.w + 20 + 45;
	world->menu.rect.y = 400 + 40;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45;
	world->menu.rect.y = 400 + 40;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 46;
	world->menu.rect.y = 400 + 40 + 10;
	world->menu.rect.w = 80;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Bounces");
	//<-- /BOUNCE -->
	//<-- ANTI_ALIASING -->
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 200;
	world->menu.rect.y = 400 + 40;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 200;
	world->menu.rect.y = 400 + 40;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 200 + 24;
	world->menu.rect.y = 400 + 40 + 10;
	world->menu.rect.w = 125;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Anti-Aliasing");
	//<-- /ANTI_ALIASING -->
	//<-- RANGEBARS -->
	int i;
	i = 0;
	while (i < world->menu.nb_others_rb)
	{
		world->menu.rect.x = world->menu.others_rb[i].pix.x;
		world->menu.rect.y = world->menu.others_rb[i].pix.y;
		world->menu.rect.w = 108;
		world->menu.rect.h = 6;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x888888);
		ft_add_menu_surface(world);
		world->menu.rect.x = world->menu.others_rb[i].pix.x + ((*(world->menu.others_rb[i].value) * 100) / world->menu.others_rb[i].max);
		world->menu.rect.y = world->menu.others_rb[i].pix.y - 3;
		world->menu.rect.w = 8;
		world->menu.rect.h = 12;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x222222);
		ft_add_menu_surface(world);
		i++;
	}
	//<-- /RANGEBARS -->
	//<-- GRANGEBARS -->
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
		int nb_val = world->menu.others_grb[i].max - world->menu.others_grb[i].min + 1;
		float step = 108 / (float)(nb_val - 1);
		int j = 0;
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
		world->menu.rect.x = world->menu.others_grb[i].pix.x + (*(world->menu.others_grb[i].value) - world->menu.others_grb[i].min) * step - 2;
		world->menu.rect.y = world->menu.others_grb[i].pix.y - 3;
		world->menu.rect.w = 8;
		world->menu.rect.h = 12;
		ft_new_menu_surface(world);
		SDL_FillRect(world->menu.surface, NULL, 0x222222);
		ft_add_menu_surface(world);
		i++;
	}
	//<-- /GRANGEBARS -->
	//<-- CARTOON -->
	t_bmp_parser bmp;
	if (world->shader == 2)
		bmp = world->menu.cartoon2;
	else
		bmp = world->menu.cartoon;
	world->menu.rect.x = world->canvas->win.w + 20 + 55;
	world->menu.rect.y = 565;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	int *pix = (int *)(world->menu.surface->pixels);
	int y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	//<-- /CARTOON -->
	//<-- FILTERS -->
	world->menu.color.r = 0;
	world->menu.color.g = 0;
	world->menu.color.b = 0;
	world->menu.color.a = 0;
	if (world->menu.filter_active == 1)
		ft_show_filters(world);
	//<-- /FILTERS -->
	//<-- /BLOC_1 -->


	//<-- BLOC_2 -->
	world->menu.rect.x = world->canvas->win.w + 20 + 20;
	world->menu.rect.y = 20 + 60 + 30 + 530 + 20;
	world->menu.rect.w = MENU_WIDTH - 40 - 40;
	world->menu.rect.h = 200;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 20 + 25;
	world->menu.rect.y = 20 + 60 + 30 + 530 + 20 + 20;
	world->menu.rect.w = MENU_WIDTH - 40 - 40 - 50;
	world->menu.rect.h = 200 - 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win.w + 20 + 20 + 25;
	world->menu.rect.y = 20 + 60 + 30 + 530 + 20 + 20;
	world->menu.rect.w = MENU_WIDTH - 40 - 40 - 50;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;
	world->menu.rect.x = world->canvas->win.w + 20 + 45 + 145;
	world->menu.rect.y = 680 + 10;
	world->menu.rect.w = 70;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Export");
	//<-- PHOTO -->
	bmp = world->menu.photo;
	world->menu.rect.x = world->canvas->win.w + 20 + 75;
	world->menu.rect.y = 750;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			if (y < 2)
				pix[y * world->menu.rect.w + x] = 0xF8F8FF;
			else
				pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	//<-- /PHOTO -->
	//<-- VIDEO -->
	if (world->exporting_video == 1)
	{
		bmp = world->menu.stop;
		world->menu.rect.x = world->canvas->win.w + 20 + 75 + 130;
		world->menu.rect.y = 751;
	}
	else
	{
		bmp = world->menu.video;
		world->menu.rect.x = world->canvas->win.w + 20 + 75 + 125;
		world->menu.rect.y = 760;
	}
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			if (y < 2)
				pix[y * world->menu.rect.w + x] = 0xF8F8FF;
			else
				pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	//<-- /VIDEO -->
	//<-- SAVE -->
	bmp = world->menu.save;
	world->menu.rect.x = world->canvas->win.w + 20 + 75 + 250;
	world->menu.rect.y = 752;
	world->menu.rect.w = bmp.width;
	world->menu.rect.h = bmp.height;
	ft_new_menu_surface(world);
	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	while (y < bmp.height)
	{
		int x = 0;
		while (x < bmp.width)
		{
			if (y < 2)
				pix[y * world->menu.rect.w + x] = 0xF8F8FF;
			else
				pix[y * world->menu.rect.w + x] = ft_get_pixel(x, bmp.height - y, bmp);
			x++;
		}
		y++;
	}
	ft_add_menu_surface(world);
	//<-- /SAVE -->
	//<-- /BLOC_2 -->
}

void	ft_display_menu(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w;
	world->menu.rect.y = 0;
	world->menu.rect.w = MENU_WIDTH;
	world->menu.rect.h = world->canvas->win.h;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);

	world->menu.rect.x = world->canvas->win.w + 20;
	world->menu.rect.y = 20;
	world->menu.rect.w = MENU_WIDTH - 40;
	world->menu.rect.h = 60;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);

	if (world->menu.type == MENU_OBJECTS)
		ft_menu_objects(world);
	else if (world->menu.type == MENU_LIGHTS)
		ft_menu_lights(world);
	else if (world->menu.type == MENU_OTHERS)
		ft_menu_others(world);
}
