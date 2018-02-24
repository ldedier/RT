/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:36:26 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/24 01:17:02 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_canvas		*new_canvas(void)
{
	t_canvas	*canvas;

	if ((canvas = malloc(sizeof(t_canvas))) == NULL)
		return (NULL);
	canvas->mlx = mlx_init();
	canvas->win_size.x = HRES;
	canvas->win_size.y = VRES;
	canvas->halved_win_size.x = HRES / 2;
	canvas->halved_win_size.y = VRES / 2;
	if ((canvas->win = mlx_new_window(canvas->mlx, canvas->win_size.x,
					canvas->win_size.y, "rtv1")) == NULL)
		return (NULL);
	if ((canvas->next_img = mlx_new_image(canvas->mlx,
					canvas->win_size.x, canvas->win_size.y)) == NULL)
		return (NULL);
	canvas->bpp = 32;
	canvas->endian = 1;
	canvas->ratio = HRES/VRES;
	canvas->size_line = canvas->win_size.x;
	canvas->img_arr = (int *)mlx_get_data_addr(canvas->next_img,
			&(canvas->bpp), &(canvas->size_line), &(canvas->endian));
	return (canvas);
}

t_world				*new_world(unsigned char scene)
{
	t_canvas	*canvas;
	t_world		*world;

	if ((canvas = new_canvas()) == NULL ||
			!(world = malloc(sizeof(t_world))) ||
			!(world->cam = malloc(sizeof(t_camera))))
		return (NULL);
	world->canvas = canvas;
	world->cam->o.x = CAMERA_X;
	world->cam->o.y = CAMERA_Y;
	world->cam->o.z = CAMERA_Z;
	//TODO: add cam->v i que la pantalla roti i tal
	world->cam->fd = CAMERA_FD;
	world->cam->pd = ZOOM / HRES;
	world->objlist = NULL;
	populate_world(world, scene);
	return (world);
}
