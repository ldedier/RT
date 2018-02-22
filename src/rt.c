/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 04:37:03 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/22 18:06:20 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				display_usage(void)
{
	ft_putendl("usage: ./fractol scene_number");
	ft_putendl("scenes:\n\t1: sphere\n\t2: 3 spheres\n\t3: blahblahblah");
	return (0);
}

int				main(int argc, char **args)
{
	t_world	*world;

	if (argc != 2)
		return (display_usage());
	if (ft_strcmp(args[1], "1") == 0)
		world = new_world(1);
	else if (ft_strcmp(args[1], "2") == 0)
		world = new_world(2);
	else if (ft_strcmp(args[1], "3") == 0)
		world = new_world(3);
	else
		return (display_usage());
	mlx_loop_hook(world->canvas->mlx, draw_frame, (void*)world);
	mlx_key_hook(world->canvas->win, key_press, (void*)world);
	paint_threaded(world);
	mlx_loop(world->canvas->mlx);
	return (0);
}
