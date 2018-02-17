/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 08:29:48 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/15 10:52:51 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	key_camera(int keycode, t_camera *cam)
{
	if (keycode == 13)
		cam->o.y -= 0.2;
	else if (keycode == 0)
		cam->o.x -= 0.2;
	else if (keycode == 1)
		cam->o.y += 0.2;
	else if (keycode == 2)
		cam->o.x += 0.2;
	else if (keycode == 49)
	{
		cam->o.x = 0.0;
		cam->o.y = 0.0;
	}
}

int			key_press(int keycode, void *param)
{
	t_world *world;

	world = (t_world *)param;
	ft_putstr("pressed key ");
	ft_putnbr(keycode);
	if (keycode == 53)
	{
		ft_putendl(": EXIT");
		mlx_destroy_image(world->canvas->mlx, world->canvas->next_img);
		mlx_destroy_window(world->canvas->mlx, world->canvas->win);
		free(world->cam);
		free(world->canvas);
		del_lst(&(world->objlist));
		free(world);
		exit(0);
	}
	key_camera(keycode, world->cam);
	ft_putchar('\n');
	paint_threaded(world);
	return (keycode);
}

int			draw_frame(void *param)
{
	(void)param;
	return (0);
}
