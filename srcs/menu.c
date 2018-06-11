/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:29:20 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 00:22:38 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_new_menu_surface(t_world *world)
{
	if (!(world->menu.surface = SDL_CreateRGBSurface(0,
					world->menu.rect.w, world->menu.rect.h, 32, 0, 0, 0, 0)))
		exit(1);
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

void	ft_add_text(t_world *world, int font, char *text, SDL_Color color)
{
	world->menu.surface = TTF_RenderText_Solid(world->menu.fonts[font], text,
			color);
	world->menu.texture = SDL_CreateTextureFromSurface(world->canvas->renderer,
			world->menu.surface);
	SDL_RenderCopy(world->canvas->renderer, world->menu.texture, NULL,
			&(world->menu.rect));
	SDL_DestroyTexture(world->menu.texture);
	world->menu.texture = NULL;
	SDL_FreeSurface(world->menu.surface);
	world->menu.surface = NULL;
}

void	ft_add_header_text(t_world *world)
{
	world->menu.rect.x = world->canvas->win.w + 37;
	world->menu.rect.y = 34;
	world->menu.rect.w = 125;
	world->menu.rect.h = 35;
	ft_add_text(world, 0, "Objects", world->menu.white_color);
	world->menu.rect.x = world->canvas->win.w + 192;
	world->menu.rect.y = 35;
	world->menu.rect.w = 115;
	world->menu.rect.h = 32;
	ft_add_text(world, 0, "Lights", world->menu.white_color);
	world->menu.rect.x = world->canvas->win.w + 341;
	world->menu.rect.y = 35;
	world->menu.rect.w = 120;
	world->menu.rect.h = 33;
	ft_add_text(world, 0, "Others", world->menu.white_color);
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
