/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 11:58:36 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/21 23:50:04 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	fill_canvas(t_world *world)
{
	/*
	int	*pix = world->canvas->surface->pixels;
	for (int y = 0; y < world->bmp_parser.height; y++)
	{
		for (int x = 0; x < world->bmp_parser.width; x++)
		{
			pix[y * HRES + x] = ft_get_pixel(x, y, world->bmp_parser.pixels, world->bmp_parser.width, world->bmp_parser.bpp);
		}
	}
	*/
	if (!(world->canvas->texture = SDL_CreateTextureFromSurface(world->
					canvas->renderer, world->canvas->surface)))
		exit(1);
	SDL_RenderCopy(world->canvas->renderer, world->canvas->texture, NULL,
			&(world->canvas->screen));
	SDL_DestroyTexture(world->canvas->texture);
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

