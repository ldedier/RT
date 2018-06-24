/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_stereoscopic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 05:58:28 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 05:17:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cyan(t_canvas *canvas, int *pixels)
{
	int	i;
	int	j;

	i = -1;
	while (++i < canvas->win_size.x)
	{
		j = -1;
		while (++j < canvas->win_size.y)
			pixels[i + j * canvas->win_size.x] =
				scale_convert_color(cyanscale(get_intcolor(get_color(
									pixels[i +
									j * canvas->win_size.x]))), 1).col;
	}
}

void		red(t_canvas *canvas, int *pixels)
{
	int	i;
	int	j;

	i = -1;
	while (++i < canvas->win_size.x)
	{
		j = -1;
		while (++j < canvas->win_size.y)
			pixels[i + j * canvas->win_size.x] =
				scale_convert_color(redscale(get_intcolor(get_color(
									pixels[i +
									j * canvas->win_size.x]))), 1).col;
	}
}

static void	finish_stereoscopic(t_world *world)
{
	int	p_y;
	int	i;

	i = -1;
	p_y = 0;
	world->cam->o = translate_vec(world->cam->o, world->cam->right, -0.1);
	while (++i < NTHREADS)
	{
		start_thread(world, p_y, i, (int *)world->canvas->red_pixels);
		p_y += world->canvas->win_size.y / NTHREADS;
	}
	if (!join_threads(world))
	{
		red(world->canvas, world->canvas->red_pixels);
		cyan(world->canvas, (int *)world->canvas->surface->pixels);
		merge_canvas(world);
		fill_canvas(world);
	}
}

void		ft_paint_stereoscopic(t_world *world)
{
	int	p_y;
	int	i;

	i = -1;
	p_y = 0;
	while (++i < NTHREADS)
	{
		start_thread(world, p_y, i, (int *)world->canvas->surface->pixels);
		p_y += world->canvas->win_size.y / NTHREADS;
	}
	if (!join_threads(world))
		finish_stereoscopic(world);
	world->cam->o = translate_vec(world->cam->o, world->cam->right, 0.1);
}
