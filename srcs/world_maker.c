/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:36:26 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 16:15:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	freecanvas(t_canvas **canvas)
{
	SDL_DestroyRenderer((*canvas)->renderer);
	SDL_DestroyWindow((*canvas)->window);
	SDL_DestroyTexture((*canvas)->texture);
	SDL_FreeSurface((*canvas)->surface);
	SDL_DestroyTexture((*canvas)->win_texture);
	SDL_FreeSurface((*canvas)->win_surface);
	free(*canvas);
	*canvas = NULL;
}

int			freeworld(t_world **world, int ret)
{
	(void)world;
	ft_printf("byee (-‘ _ ‘-)つ \n");
	return (ret);
}

int			new_world_2(t_world **world, t_canvas *canvas, char *file)
{
	int			rw_err;

	if ((rw_err = read_world(*world, file)))
	{
		return (freeworld(world, rw_err));
	}
	if (ft_init_sdl(*world) == 0)
	{
		freecanvas(&canvas);
		return (-3);
	}
	set_positions(*world);
	return (0);
}

int			new_world(char *file, t_world **world)
{
	t_canvas	*canvas;

	if ((canvas = new_canvas()) == NULL)
		return (-3);
	if (!(*world = malloc(sizeof(t_world))))
	{
		freecanvas(&canvas);
		return (-3);
	}
	if (!((*world)->cam = malloc(sizeof(t_camera))))
	{
		freecanvas(&canvas);
		free(*world);
		return (-3);
	}
	(*world)->canvas = canvas;
	set_defaults(*world);
	return (new_world_2(world, canvas, file));
}
