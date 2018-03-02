/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 04:37:03 by lcavalle          #+#    #+#             */
/*   Updated: 2018/03/02 20:32:17 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				display_usage(void)
{
	ft_putendl("usage: ./rtv1 scene_number");
	ft_putendl("scenes:\n\t1: plane\n"
			"\t2: plane + sphere\n"
			"\t3: cylinder (not rotated)\n"
			"\t4: cone\n\t5: lots of things\n"
			"\t6: lots of things (cylinder rotated)");
	return (0);
}

int				main(int argc, char **args)
{
	t_world	*world;
	int		scene;

	if (argc != 2)
		return (display_usage());
	scene = ft_atoi(args[1]);
	if (scene > 0 && scene <= 6)
		world = new_world(scene);
	else
		return (display_usage());
	mlx_loop_hook(world->canvas->mlx, draw_frame, (void*)world);
	mlx_key_hook(world->canvas->win, key_press, (void*)world);
	mlx_expose_hook(world->canvas->win, expose, (void*)world);
	paint_threaded(world);
	mlx_loop(world->canvas->mlx);
	return (0);
}
