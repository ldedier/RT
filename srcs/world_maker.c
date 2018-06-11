/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:36:26 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 06:12:05 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	freecanvas(t_canvas *canvas)
{
	free(canvas);
}

int		freeworld(t_world *world, int ret)
{
	del_clst(&(world->cobjlist));
	free(world->cam);
	free(world);
	return (ret);
}

int		new_world_2(t_world **world, t_canvas *canvas, char *file)
{
	int			rw_err;

	if ((rw_err = read_world(*world, file)))
	{
		freecanvas(canvas);
		return (freeworld(*world, rw_err));
	}
	if (ft_init_sdl(*world) == 0)
	{
		freecanvas(canvas);
		return (-3);
	}
	set_positions(*world);
	return (0);
}

int		new_world(char *file, t_world **world)
{
	t_canvas	*canvas;

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
	return (new_world_2(world, canvas, file));
}
