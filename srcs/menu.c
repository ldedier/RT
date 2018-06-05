/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:29:20 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/04 23:38:36 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_new_menu_surface(t_world *world)
{
	if (!(world->menu.surface = SDL_CreateRGBSurface(0,
					world->menu.rect.w, world->menu.rect.h, 32, 0, 0, 0, 0)))
		exit (1);
}

void	ft_add_menu_surface(t_world *world)
{
	if (!(world->menu.texture = SDL_CreateTextureFromSurface(world->
					canvas->renderer, world->menu.surface)))
		exit(1);
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

	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 7;
	world->menu.rect.y = 20 + 10 + 4;
	world->menu.rect.w = 125;
	world->menu.rect.h = 35;
	ft_add_text(world, 0, "Objects");

	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 140 + 10 + 12;
	world->menu.rect.y = 20 + 10 + 5;
	world->menu.rect.w = 115;
	world->menu.rect.h = 32;
	ft_add_text(world, 0, "Lights");

	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 140 + 10 + 140 + 10 + 11;
	world->menu.rect.y = 20 + 10 + 5;
	world->menu.rect.w = 120;
	world->menu.rect.h = 33;
	ft_add_text(world, 0, "Others");
}

void	ft_menu_objects(t_world *world)
{
	world->menu.rect.x = world->canvas->win_size.x + 20 + 10;
	world->menu.rect.y = 20 + 10;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);

}

void	ft_menu_lights(t_world *world)
{
	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 140 + 10;
	world->menu.rect.y = 20 + 10;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);

}

void	ft_switch_filter(t_world *world, int filter, int pos)
{
	world->menu.rect.y = world->menu.filters.pos.y + pos * (world->menu.filters.size.y + 2) + 10;
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

void	ft_menu_others(t_world *world)
{
	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 140 + 10 + 140 + 10;
	world->menu.rect.y = 20 + 10;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	ft_add_header_text(world);

	//<-- BLOC_1 -->
	world->menu.rect.x = world->canvas->win_size.x + 20 + 20;
	world->menu.rect.y = 20 + 60 + 30;
	world->menu.rect.w = MENU_WIDTH - 40 - 40;
	world->menu.rect.h = 530;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	//<-- AMBIENT -->
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 350 - 130 + 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 44;
	world->menu.rect.y = 140;
	world->menu.rect.w = 80;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Ambient");
	//<-- /AMBIENT -->
	//<-- FOG -->
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 200;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 350 - 130 + 10;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 200;
	world->menu.rect.y = 20 + 60 + 30 + 20;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 44 + 220;
	world->menu.rect.y = 140;
	world->menu.rect.w = 40;
	world->menu.rect.h = 18;
	ft_add_text(world, 1, "Fog");
	//<-- /FOG -->
	//<-- AMBIENT_COLOR -->
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 64;
	world->menu.rect.y = 180;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 64 + 3;
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
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 64 + 200;
	world->menu.rect.y = 180;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 64 + 200 + 3;
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
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45;
	world->menu.rect.y = 400;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 57;
	world->menu.rect.y = 410;
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
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45;
	world->menu.rect.y = 480;
	world->menu.rect.w = (MENU_WIDTH - 40 - 120) / 2;
	world->menu.rect.h = 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x666666);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 45;
	world->menu.rect.y = 490;
	world->menu.rect.w = 80;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Bounces");
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 174;
	world->menu.rect.y = 402 + 80;
	world->menu.rect.w = 195;
	world->menu.rect.h = 36;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	//<-- /BOUNCE -->
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
	//<-- CARTOON -->
	t_bmp_parser bmp;
	if (world->shader == 2)
		bmp = world->menu.cartoon2;
	else
		bmp = world->menu.cartoon;
	world->menu.rect.x = world->canvas->win_size.x + 20 + 54;
	world->menu.rect.y = 556;
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
	world->menu.rect.x = world->canvas->win_size.x + 20 + 20;
	world->menu.rect.y = 20 + 60 + 30 + 530 + 20;
	world->menu.rect.w = MENU_WIDTH - 40 - 40;
	world->menu.rect.h = 200;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 20 + 25;
	world->menu.rect.y = 20 + 60 + 30 + 530 + 20 + 20;
	world->menu.rect.w = MENU_WIDTH - 40 - 40 - 50;
	world->menu.rect.h = 200 - 40;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 20 + 25;
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
	world->menu.rect.x = world->canvas->win_size.x + 20 + 45 + 145;
	world->menu.rect.y = 680 + 10;
	world->menu.rect.w = 70;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Export");
	//<-- PHOTO -->
	bmp = world->menu.photo;
	world->menu.rect.x = world->canvas->win_size.x + 20 + 75;
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
	bmp = world->menu.video;
	world->menu.rect.x = world->canvas->win_size.x + 20 + 75 + 125;
	world->menu.rect.y = 760;
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
	world->menu.rect.x = world->canvas->win_size.x + 20 + 75 + 250;
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
	world->menu.rect.x = world->canvas->win_size.x;
	world->menu.rect.y = 0;
	world->menu.rect.w = MENU_WIDTH;
	world->menu.rect.h = world->canvas->win_size.y + PROGRESS_BAR_HEIGHT;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xF8F8FF);
	ft_add_menu_surface(world);

	world->menu.rect.x = world->canvas->win_size.x + 20;
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
