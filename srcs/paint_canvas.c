/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 11:58:36 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/09 06:55:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	merge_canvas(t_world *world)
{
	int i;
	int *pix;
	int *pixred;

	i = 0;
	pix = (int *)world->canvas->surface->pixels;
	pixred = world->canvas->red_pixels;
	while (i < world->canvas->win_size.x * world->canvas->win_size.y)
	{
		pix[i] = add_colors(get_color(pix[i]),
					get_color(pixred[i])).col;


		i++;
	}
}

void	fill_canvas(t_world *world)
{
	if (!(world->canvas->texture = SDL_CreateTextureFromSurface(world->
					canvas->renderer, world->canvas->surface)))
		ft_error("could not create texture");
	SDL_RenderCopy(world->canvas->renderer, world->canvas->texture, NULL,
			&(world->canvas->screen));
	SDL_DestroyTexture(world->canvas->texture);
	SDL_RenderPresent(world->canvas->renderer);
}

void	update_progress_bar(t_world *world)
{
	SDL_FillRect(world->canvas->win_surface, &(world->canvas->pb_rect), 0x0);
	world->canvas->pb_rect.w = (int)((float)world->progress /
			world->canvas->npixels * world->canvas->win.w);
	SDL_FillRect(world->canvas->win_surface, &(world->canvas->pb_rect), 0x33DD33);
	if (!(world->canvas->win_texture = SDL_CreateTextureFromSurface(world->
					canvas->renderer, world->canvas->win_surface)))
		ft_error("could not create texture");
	SDL_RenderCopy(world->canvas->renderer, world->canvas->win_texture, NULL,
			&(world->canvas->win));
	SDL_DestroyTexture(world->canvas->win_texture);
	ft_display_menu(world);
	fill_canvas(world);
}
