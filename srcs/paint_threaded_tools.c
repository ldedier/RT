/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_threaded_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 06:00:57 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 06:47:56 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

static void	join_threads2(t_world *world, int *oldi, int *cancel)
{
	int	i;

	i = *oldi;
	if (world->cancel_render == 1)
	{
		i = -1;
		world->cancel_render = 0;
		*cancel = 1;
	}
	if (world->thr_state[++(i)] == 2 ||
			(world->thr_state[i] == 1 && *cancel == 1))
	{
		if (pthread_join(world->threads[i], NULL))
		{
			ft_dprintf(2, "cannot join thread %d! exit...\n", i);
			exit(freeworld(&world, 1));
		}
		world->thr_state[i] = 0;
	}
	*oldi = i;
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
		join_threads2(world, &i, &cancel);
		if (i == NTHREADS)
			i = -1;
		if (get_input(world))
			exit(freeworld(&world, 0));
	}
	if ((ret = (cancel == 1)) == 1)
		ft_printf("rendering cancelled\n");
	world->progress = 0;
	world->cancel_render = 0;
	return (ret);
}
