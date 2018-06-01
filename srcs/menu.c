/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:29:20 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/01 06:03:49 by aherriau         ###   ########.fr       */
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

void	ft_add_text(t_world *world, char *text)
{
	world->menu.surface = TTF_RenderText_Solid(world->menu.fonts[0], text, world->menu.color);
	world->menu.texture = SDL_CreateTextureFromSurface(world->canvas->renderer, world->menu.surface);
	SDL_RenderCopy(world->canvas->renderer, world->menu.texture, NULL, &(world->menu.rect));
	SDL_DestroyTexture(world->menu.texture);
	world->menu.texture = NULL;
	SDL_FreeSurface(world->menu.surface);
	world->menu.surface = NULL;
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

	world->menu.rect.x = world->canvas->win_size.x + 20 + 10 + 5;
	world->menu.rect.y = 20 + 10 + 5;
	world->menu.rect.w = 140;
	world->menu.rect.h = 40;
	world->menu.color.r = 255;
	world->menu.color.g = 255;
	world->menu.color.b = 255;
	world->menu.color.a = 255;
	ft_add_text(world, "Objects");
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
