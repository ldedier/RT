/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_threaded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:19:18 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 22:54:23 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		*render_thr(void *thpar)
{
	t_pixel		p;
	t_thr_par	*tpar;

	tpar = (t_thr_par *)thpar;
	p.x = 0;
	while (tpar->world->cancel_render == 0 && p.x <
			tpar->world->canvas->win_size.x)
	{
		p.y = tpar->p_y;
		while (tpar->world->cancel_render == 0 &&
				p.y < tpar->p_y + tpar->world->canvas->win_size.y / NTHREADS)
		{
			paint_pixel(p, render_pixel(tpar->world, p, 0), tpar->pixels,
					tpar->world->canvas->win_size);
			tpar->world->progress++;
			p.y++;
		}
		p.x++;
	}
	tpar->world->thr_state[tpar->id] = 2;
	free(thpar);
	return (NULL);
}

void		start_thread(t_world *world, int p_y, int i, int *pixels)
{
	t_thr_par	*tpar;

	if (!(tpar = malloc(sizeof(t_thr_par))))
		exit(0);
	tpar->world = world;
	tpar->pixels = pixels;
	tpar->p_y = p_y;
	tpar->id = i;
	world->thr_state[i] = 1;
	if (pthread_create(&(world->threads[i]), NULL, render_thr, (void*)tpar))
		exit(0);
}

void		paint_threaded(t_world *world)
{
	int			p_y;
	int			i;

	ft_putendl("Render image");
	if (world->stereoscopic)
		ft_paint_stereoscopic(world);
	else
	{
		i = -1;
		p_y = 0;
		while (++i < NTHREADS)
		{
			start_thread(world, p_y, i, (int *)world->canvas->surface->pixels);
			p_y += world->canvas->win_size.y / NTHREADS;
		}
		if (!join_threads(world))
		{
			if (world->shader == 2)
				draw_borders(world->canvas);
			apply_convolution(world);
			fill_canvas(world);
		}
	}
}
