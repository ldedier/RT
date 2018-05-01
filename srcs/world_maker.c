/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:36:26 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 03:45:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			freecanvas(t_canvas *canvas)
{
//	mlx_destroy_image(canvas->mlx, canvas->next_img);
//	mlx_destroy_window(canvas->mlx, canvas->win);
//	free(canvas->mlx);
	free(canvas);
}

static int			freeworld(t_world *world, int ret)
{
	del_lst(&(world->objlist));
	free(world->cam);
	free(world);
	return (ret);
}

int					new_world(char *file, t_world **world)
{
	t_canvas	*canvas;
	int			rw_err;

	if ((canvas = new_canvas()) == NULL)
		return (-3);
	if (!(*world = malloc(sizeof(t_world))))
	{
		freecanvas(canvas);
		return (-3);
	}
	if (!((*world)->cam = malloc(sizeof(t_camera))))
	{
		freecanvas(canvas);
		free(*world);
		return (-3);
	}
	(*world)->canvas = canvas;

	set_defaults(*world);
	if ((rw_err = read_world(*world, file)))
	{
		freecanvas(canvas);
		return (freeworld(*world, rw_err));
	}
	return (0);
}
