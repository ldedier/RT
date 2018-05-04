/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 08:29:48 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/04 16:19:41 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	key_camera(int keycode, t_camera *cam)
{
	if (keycode == KEY_UP)
		cam->o = translate_vec(cam->o, cam->up, cam->speed);
	else if (keycode == KEY_DOWN)
		cam->o = translate_vec(cam->o, cam->up, -cam->speed);
	else if (keycode == KEY_LEFT)
		cam->o = translate_vec(cam->o, cam->right, -cam->speed);
	else if (keycode == KEY_RIGHT)
		cam->o = translate_vec(cam->o, cam->right, cam->speed);
	else if (keycode == KEY_FORWARD)
		cam->o = translate_vec(cam->o, cam->look, cam->speed);
	else if (keycode == KEY_BACKWARD)
		cam->o = translate_vec(cam->o, cam->look, -cam->speed);
	else if (keycode == KEY_ABOVE)
		cam->rotation.y += 0.3;
	else if (keycode == KEY_BELOW)
		cam->rotation.y -= 0.3;
	else if (keycode == KEY_TLEFT)
		cam->rotation.x -= 0.3;
	else if (keycode == KEY_TRIGHT)
		cam->rotation.x += 0.3;
	apply_rotation(cam);
}

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

int			key_press(int keycode, void *param)
{
	t_world *world;

	world = (t_world *)param;
	ft_putstr("pressed key ");
	ft_putnbr(keycode);
	if (keycode == 53)
		end(world);
	key_camera(keycode, world->cam);
	ft_putchar('\n');
	paint_threaded(world);
	return (keycode);
}
