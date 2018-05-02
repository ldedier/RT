/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 04:37:03 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 06:35:39 by ldedier          ###   ########.fr       */
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
	else
	{
		ft_putstr("line ");
		ft_putnbr(err);
		ft_putstr(": wrong format. Correct format:\n"
				"\tsphere:\t\ts [x] [y] [z] [rad] [color]\n"
				"\tplane(n=normal):p [x] [y] [z] [n.x] [n.y] [n.z]) [color]\n"
				"\tcone:\t\t\tc [x] [y] [z] [v.x] [v.y] [v.z] [angle] [color]\n"
				"\tcylinder:\t\ty [x] [y] [z] [v.x] [v.y] [v.z] [rad] [color]\n"
				"\tlight(max: ");
		ft_putnbr(MAX_LIGHTS);
		ft_putendl("):\t\tl [x] [y] [z] [intensity(0-1)] [color]");
	}
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
	print_list(world->objlist);
	print_lights(world);
	ft_compute_matrices_list(world->objlist);
	ft_loop(world);
//	paint_threaded(world);
	return (0);
}
