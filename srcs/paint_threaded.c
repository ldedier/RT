/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_threaded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:19:18 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/09 08:30:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	*render_thr(void *thpar)
{
	t_world		*world;
	t_pixel		p;
	int			p_y;
	int			selfid;
	int			*pixels;

	world = ((t_thr_par *)thpar)->world;
	pixels = ((t_thr_par *)thpar)->pixels;
	selfid = ((t_thr_par *)thpar)->id;
	printf("##thread started: %i\n",selfid);
	p.x = 0;
	p_y = ((t_thr_par*)thpar)->p_y;
	while (world->cancel_render == 0 && p.x < world->canvas->win_size.x)
	{
		p.y = p_y;
		while (world->cancel_render == 0 &&
				p.y < p_y + world->canvas->win_size.y / NTHREADS)
		{
			paint_pixel(p, render_pixel(world, p, 0), pixels,
					world->canvas->win_size);
			world->progress++;
			p.y++;
		}
		p.x++;
	}
	free(thpar);
	world->thr_state[selfid] = 2;
	return (NULL);
}

static int	working_count(t_world *world)
{
	int i;
	int	count;

	i = -1;
	count = 0;
	while (++i < NTHREADS)
	{
		if (world->thr_state[i] != 0)
			count++;
	}
	return (count);
}

int			join_threads(t_world *world)
{
	int	i;
	int	ret;
	int	cancel;

	i = -1;
	cancel = 0;
	while (working_count(world) > 0)
	{
		update_progress_bar(world);
		if (world->cancel_render == 1)
		{
			i = -1;
			world->cancel_render = 0;
			cancel = 1;
		}
		if (world->thr_state[++i] == 2 ||
				(world->thr_state[i] == 1 && cancel == 1))
		{
			printf("joining thread %i of %i\n",i , NTHREADS);
			if (pthread_join(world->threads[i], NULL))
			{
				printf("cannot join thread %i!!!! exit...\n", i);
				exit(freeworld(&world, 1));
			}
			world->thr_state[i] = 0;
		}
		if (i == NTHREADS)
			i = -1;
		if (get_input(world))
			exit(freeworld(&world, 0));
	}
	if ((ret = (cancel == 1)) == 1)
		printf("all threads cancelled\n");
	printf("threads joined, progress: %i, ret: %i\n", world->progress, ret);
	world->progress = 0;
	world->cancel_render = 0;
	return (ret);
}

void		ft_paint_stereoscopic(t_world *world)
{

	t_thr_par	*tpar;
	int			p_y;
	int			i;

	i = -1;
	p_y = 0;
	printf("%i\n",world->canvas->win_size.y);
	while (++i < NTHREADS)
	{
		if (!(tpar = malloc(sizeof(t_thr_par))))
			exit(1);
		tpar->world = world;
		tpar->pixels = (int *)world->canvas->surface->pixels;
		tpar->p_y = p_y;
		tpar->id = i;
		world->thr_state[i] = 1;
		if (pthread_create(&(world->threads[i]), NULL, render_thr, (void*)tpar))
			exit(1);
		p_y += world->canvas->win_size.y / NTHREADS;
	}
	printf("joining threads...\n");
	if (!join_threads(world))
	{
		i = -1;
		p_y = 0;
		world->cam->o = translate_vec(world->cam->o, world->cam->right, -0.1);
		while (++i < NTHREADS)
		{
			if (!(tpar = malloc(sizeof(t_thr_par))))
				exit(0);
			tpar->world = world;
			tpar->pixels = world->canvas->red_pixels;
			tpar->p_y = p_y;
			tpar->id = i;
			world->thr_state[i] = 1;
			if (pthread_create(&(world->threads[i]), NULL, render_thr, (void*)tpar))
				exit(0);
			p_y += world->canvas->win_size.y / NTHREADS;
		}
		printf("joining threads...\n");
		if (!join_threads(world))
		{
			red(world->canvas, world->canvas->red_pixels);
			cyan(world->canvas, (int *)world->canvas->surface->pixels);
			merge_canvas(world);
			fill_canvas(world);
		}
	}
	world->cam->o = translate_vec(world->cam->o, world->cam->right, 0.1);
}

void		paint_threaded(t_world *world)
{
	t_thr_par	*tpar;
	int			p_y;
	int			i;

	if (world->stereoscopic)
		ft_paint_stereoscopic(world);
	else
	{
		i = -1;
		p_y = 0;
		printf("%i\n",world->canvas->win_size.y);
		while (++i < NTHREADS)
		{
			if (!(tpar = malloc(sizeof(t_thr_par))))
				exit(0);
			tpar->world = world;
			tpar->pixels = (int *)world->canvas->surface->pixels;
			tpar->p_y = p_y;
			tpar->id = i;
			world->thr_state[i] = 1;
			if (pthread_create(&(world->threads[i]), NULL, render_thr, (void*)tpar))
				exit(0);
			p_y += world->canvas->win_size.y / NTHREADS;
		}
		printf("joining threads...\n");
		if (!join_threads(world))
		{
			if (world->shader == 2)
				draw_borders(world->canvas);
			apply_convolution(world);
			fill_canvas(world);
		}
	}
}
