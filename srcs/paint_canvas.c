/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 11:58:36 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/30 02:58:57 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	fill_canvas(t_world *world)
{
	if (!(world->canvas->texture = SDL_CreateTextureFromSurface(world->
					canvas->renderer, world->canvas->surface)))
		exit(1);
	SDL_RenderCopy(world->canvas->renderer, world->canvas->texture, NULL,
			&(world->canvas->screen));
	SDL_DestroyTexture(world->canvas->texture);

	SDL_FillRect(world->canvas->menu_surface, NULL, 0xF8F8FF);
	if (!(world->canvas->menu_texture = SDL_CreateTextureFromSurface(world->
					canvas->renderer, world->canvas->menu_surface)))
		exit(1);
	SDL_RenderCopy(world->canvas->renderer, world->canvas->menu_texture, NULL,
			&(world->canvas->menu_rect));
	SDL_DestroyTexture(world->canvas->menu_texture);
	
	SDL_RenderPresent(world->canvas->renderer);
}

void	update_progress_bar(t_world *world)
{
	SDL_FillRect(world->canvas->surface, &(world->canvas->pb_rect), 0x0);
	world->canvas->pb_rect.w = (int)((float)world->progress /
			world->canvas->npixels * world->canvas->win_size.x);
	SDL_FillRect(world->canvas->surface, &(world->canvas->pb_rect), 0x33DD33);
	fill_canvas(world);
}

