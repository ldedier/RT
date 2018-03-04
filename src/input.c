/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 08:29:48 by lcavalle          #+#    #+#             */
/*   Updated: 2018/03/04 02:15:40 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	key_camera(int keycode, t_camera *cam)
{
	if (keycode == KEY_UP)
		cam->o = translate_vec(cam->o, cam->up, -0.35);
	else if (keycode == KEY_DOWN)
		cam->o = translate_vec(cam->o, cam->up, 0.35);
	else if (keycode == KEY_LEFT)
		cam->o = translate_vec(cam->o, crossprod(cam->look, cam->up), 0.35);
	else if (keycode == KEY_RIGHT)
		cam->o = translate_vec(cam->o, crossprod(cam->look, cam->up), -0.35);
	else if (keycode == KEY_FORWARD)
		cam->o = translate_vec(cam->o, cam->look, 0.35);
	else if (keycode == KEY_BACKWARD)
		cam->o = translate_vec(cam->o, cam->look, -0.35);
	else if (keycode == KEY_RESET)
	{
		cam->o = CAMERA_POS;
		cam->look = normalize(CAMERA_LOOK);
		cam->up = normalize(CAMERA_UP);
	}
	else if (keycode == 124)
		cam->look = rotate_vec(cam->look, H_ROTATION);
	else if (keycode == 123)
		cam->look = rotate_vec(cam->look, scale(H_ROTATION, -1.0));
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

int			expose(void *param)
{
	t_world	*world;

	world = (t_world *)param;
	ft_putendl("expose called");
	mlx_put_image_to_window(world->canvas->mlx, world->canvas->win,
			world->canvas->next_img, 0, 0);
	return (0);
}

int			draw_frame(void *param)
{
	(void)param;
	return (0);
}
