/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 08:29:48 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/16 22:46:13 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			end(t_world *world)
{
	ft_putendl(": EXIT");
//	mlx_destroy_image(world->canvas->mlx, world->canvas->next_img);
//	mlx_destroy_window(world->canvas->mlx, world->canvas->win);
//	free(world->canvas->mlx);
	free(world->cam);
	free(world->canvas);
//	del_lst(&(world->objlist));
	free(world);
	exit(0);
	return (0);
}
