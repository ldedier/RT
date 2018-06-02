/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:29:20 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/02 07:14:29 by aherriau         ###   ########.fr       */
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

float Hue2RGB(float v1, float v2, float vH)
{
	if (vH < 0)
		vH += 1.f;
	if (vH > 1)
		vH -= 1.f;
	if (6.f * vH < 1)
		return v1 + (v2 - v1) * 6.f * vH;
	if (2.f * vH < 1)
		return v2;
	if (3.f * vH < 2)
		return v1 + (v2 - v1) * (0.666666f - vH) * 6.f;
	return v1;
}

void	ft_color_hue(t_world *world)
{
	int		x;
	float	x0;
	int		y;
	float	y0;
	int		*pix;
	t_color	color;

	pix = (int *)(world->menu.surface->pixels);
	y = 0;
	y0 = 0;
	while (y < world->menu.rect.h)
	{
		y0 = (float)y / 100;
		x = 0;
		while (x < world->menu.rect.w)
		{
			x0 = (float)x / 100;
			float h = x0;
			float s = 1.0f - y0;
			float l = 1.0f - y0;
			if (s == 0)
			{
				color.r = ft_clamp(0, l * 255, 255);
				color.g = ft_clamp(0, l * 255, 255);
				color.b = ft_clamp(0, l * 255, 255);
			}
			else
			{
				float var_1 = 0;
				float var_2 = 0;

				if (l < 0.5f)
					var_2 = l * (1.0f + s);
				else           
					var_2 = (l + s) - (s * l);
				var_1 = 2.0f * l - var_2;

				color.r = ft_clamp(0, Hue2RGB(var_1, var_2, h + 0.333333f) * 255, 255);
				color.g = ft_clamp(0, Hue2RGB(var_1, var_2, h) * 255, 255);
				color.b = ft_clamp(0, Hue2RGB(var_1, var_2, h - 0.333333f) * 255, 255);
			} 
			color.col = (color.r << 16) | (color.g << 8) | color.b;
			pix[y * world->menu.rect.w + x] = color.col;
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
	
	world->menu.color.r = 0;
	world->menu.color.g = 0;
	world->menu.color.b = 0;
	world->menu.color.a = 0;
	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 30;
	world->menu.rect.y = 120;
	world->menu.rect.w = 80;
	world->menu.rect.h = 20;
	ft_add_text(world, 1, "Ambient");
	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 30;
	world->menu.rect.y = 270;
	world->menu.rect.w = 40;
	world->menu.rect.h = 15;
	ft_add_text(world, 1, "Fog");

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

	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 30 + 82;
	world->menu.rect.y = 155;
	world->menu.rect.w = 40;
	world->menu.rect.h = 20;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0x222222);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 30 + 82 + 3;
	world->menu.rect.y = 155 + 3;
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
	world->menu.rect.x = world->menu.others_cp[0].pix.x + world->menu.others_cp[0].pos.x;
	world->menu.rect.y = world->menu.others_cp[0].pix.y + world->menu.others_cp[0].pos.y;
	world->menu.rect.w = 7;
	world->menu.rect.h = 7;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xFFFFFF);
	ft_add_menu_surface(world);

	world->menu.rect.x = world->menu.others_cp[1].pix.x;
	world->menu.rect.y = world->menu.others_cp[1].pix.y;
	world->menu.rect.w = 100;
	world->menu.rect.h = 100;
	ft_new_menu_surface(world);
	ft_color_hue(world);
	ft_add_menu_surface(world);
	world->menu.rect.x = world->menu.others_cp[1].pix.x + 30;
	world->menu.rect.y = world->menu.others_cp[1].pix.y + 30;
	world->menu.rect.w = 7;
	world->menu.rect.h = 7;
	ft_new_menu_surface(world);
	SDL_FillRect(world->menu.surface, NULL, 0xFFFFFF);
	ft_add_menu_surface(world);
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
