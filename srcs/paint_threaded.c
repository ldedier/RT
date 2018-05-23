/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_threaded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:19:18 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/22 08:52:20 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	*render_thr(void *thpar)
{
	t_world		*world;
	t_pixel		p;
	int			p_y;
	int			selfid;

	world = ((t_thr_par *)thpar)->world;
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
			paint_pixel(p, render_pixel(world, p, 0), world->canvas);
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
				exit(0);
			}
			world->thr_state[i] = 0;
		}
		if (i == NTHREADS)
			i = -1;
		if (get_input(world))
			end(world);
	}
	if ((ret = (cancel == 1)) == 1)
		printf("all threads cancelled\n");
	printf("threads joined, progress: %i, ret: %i\n", world->progress, ret);
	world->progress = 0;
	world->cancel_render = 0;
	printf("oju que ara el join retorna %i\n",ret);fflush(stdout);
	return (ret);
}

void		paint_threaded(t_world *world)
{
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
		tpar->id = i;
		world->thr_state[i] = 1;
		if (pthread_create(&(world->threads[i]), NULL, render_thr, (void*)tpar))
			exit(0);
		p_y += world->canvas->win_size.y / NTHREADS;
	}
	printf("oju ara crido join threads desde paint_threaded\n");fflush(stdout);
	if (!join_threads(world))
	{
		apply_convolution(world);
		fill_canvas(world);
		printf("canvas filled\n");fflush(stdout);
	}
}

void	paint_not_threaded(t_world *world)
{
	t_pixel p;

	p.y = 0;
	while (world->cancel_render == 0 && p.y < world->canvas->win_size.y)
	{
		p.x = 0;
		while (world->cancel_render == 0 &&  p.x < world->canvas->win_size.x)
		{
			paint_pixel(p, render_pixel(world, p, 0), world->canvas);
			p.x++;
		}
		p.y++;
	}
	fill_canvas(world);
}
