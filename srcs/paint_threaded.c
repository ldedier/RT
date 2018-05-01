/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_threaded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:19:18 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 03:25:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	*render_thr(void *thpar)
{
	t_world		*world;
	t_pixel		p;
	int			p_y;

	world = ((t_thr_par *)thpar)->world;
	p.x = 0;
	p_y = ((t_thr_par*)thpar)->p_y;
	while (p.x < world->canvas->win_size.x)
	{
		p.y = p_y;
		while (p.y < p_y + world->canvas->win_size.y / NTHREADS)
		{
			paint_pixel(p, render_pixel(world, p), world->canvas);
			p.y++;
		}
		p.x++;
	}
	free(thpar);
	return (NULL);
}

void		paint_threaded(t_world *world)
{
	pthread_t	ids[NTHREADS];
	t_thr_par	*tpar;
	int			p_y;
	int			i;

	i = -1;
	p_y = 0;
	while (++i < NTHREADS)
	{
		if (!(tpar = malloc(sizeof(t_thr_par))))
			exit(0);
		tpar->world = world;
		tpar->p_y = p_y;
		if (pthread_create(&(ids[i]), NULL, render_thr, (void*)tpar))
			exit(0);
		p_y += world->canvas->win_size.y / NTHREADS;
	}
	while (--i >= 0)
		if (pthread_join(ids[i], NULL))
			exit(0);
		if (!(world->canvas->texture = SDL_CreateTextureFromSurface(world->
				canvas->renderer, world->canvas->surface)))
			exit(1);
	SDL_FillRect(world->canvas->surface, NULL, 0x00FF00);
	SDL_RenderCopy(world->canvas->renderer, world->canvas->texture, NULL,
			&(world->canvas->screen));
	SDL_RenderPresent(world->canvas->renderer);
}
