/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 04:37:03 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 05:13:12 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		display_usage(int err)
{
	if (err == 0)
		ft_putendl("usage: ./rt [file_name]");
	else if (err == -1)
		ft_putendl("error at open file");
	else if (err == -2)
		ft_putendl("error at read file");
	else if (err == -3)
		ft_putendl("memory error");
	return (0);
}

int				main(int argc, char **args)
{
	t_world	*world;
	int		err;

	world = NULL;
	if (argc != 2)
		return (display_usage(0));
	if ((err = new_world(args[1], &world)))
		return (display_usage(err));
	ft_compute_matrices_clist(world->cobjlist);
	apply_rotation(world->cam);
	ft_loop(world);
	freeworld(&world, 0);
	return (0);
}
