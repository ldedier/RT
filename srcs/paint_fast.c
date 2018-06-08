/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_fast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 08:53:58 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/08 08:19:09 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	render_big_pixel(t_world *world, t_pixel psize, t_pixel pscaled)
{
	t_color	col;
	t_pixel	filler;
	t_pixel	center;

	center.x = pscaled.x + psize.x / 2;
	center.y = pscaled.y + psize.y / 2;
	col = render_pixel(world, center, 1);
	filler.x = pscaled.x - 1;
	while (++filler.x < pscaled.x + psize.x)
	{
		filler.y = pscaled.y - 1;
		while (++filler.y < pscaled.y + psize.y)
			paint_pixel(filler, col, world->canvas);
	}
}

static void	*render_thr_fast(void *thpar)
{
	t_pixel	p;
	t_pixel	psize;
	t_pixel	pscaled;
	t_world	*world;
	int		p_y;

	p.x = -1;
	world = ((t_thr_par *)thpar)->world;
	p_y = ((t_thr_par*)thpar)->p_y;
	psize.x = world->canvas->win_size.x / world->canvas->fast_win_size.x;
	psize.y = world->canvas->win_size.y / world->canvas->fast_win_size.y;
	while (++p.x < world->canvas->fast_win_size.x)
	{
		p.y = p_y - 1;
		pscaled.x = p.x * psize.x;
		while (++p.y < p_y + world->canvas->fast_win_size.y / NTHREADS)
		{
			pscaled.y = p.y * psize.y;
			render_big_pixel(world, psize, pscaled);
		}
	}
	free(thpar);
	return (NULL);
}

void		paint_threaded_fast(t_world *world)
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
		if (pthread_create(&(ids[i]), NULL, render_thr_fast, (void*)tpar))
			exit(0);
		p_y += world->canvas->fast_win_size.y / NTHREADS;
	}
	while (--i >= 0)
		if (pthread_join(ids[i], NULL))
			exit(0);
	update_progress_bar(world);
}
