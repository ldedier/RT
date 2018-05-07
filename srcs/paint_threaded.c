/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_threaded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:19:18 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/07 12:29:46 by lcavalle         ###   ########.fr       */
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
			//	printf("=====%i\n",world->cancel_render);
			paint_pixel(p, render_pixel(world, p, 0), world->canvas);
			world->progress++;
			//update_progress_bar(world);
			p.y++;
		}
		p.x++;
	}
	free(thpar);
//	if (world->cancel_render) printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAi\n\n");
	world->thr_state[selfid] = 2;
	return (NULL);
}

static int	working_count(t_world *world)
{
	int i;
	int	count;

	i = -1;
	count = 0;
//	printf("---------------------\n");
	while (++i < NTHREADS)
	{
//		printf("thread %i: state %i\n", i, world->thr_state[i]);
		if (world->thr_state[i] != 0)
			count++;
	}
	return (count);
}

void	join_threads(t_world *world)
{
	int	i;

	i = -1;
//	printf("cancel_render: %i, working: %i\n", world->cancel_render, working_count(world));
//	printf("in da join_threasd");
	while (working_count(world) > 0)
	{
		update_progress_bar(world);
		if (world->thr_state[++i] == 2 || 
				(world->thr_state[i] == 1 && world->cancel_render == 1))
		{
			printf("joining thread %i of %i\n",i , NTHREADS);
			if (pthread_join(world->threads[i], NULL))
			{
				printf("cannot join thread %i!!!! exit...\n", i);
				exit(0);
			}
			world->thr_state[i] = 0;
		}
//		printf("holi");
		if (i  == NTHREADS)
			i = -1;
		if (get_input(world))
			end(world);
	}
//	printf("out of da while");
	if (world->cancel_render == 1) printf("all threads cancelled\n");
	world->progress = 0;
	world->cancel_render = 0;
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
	join_threads(world);
	fill_canvas(world);
}
