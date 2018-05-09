/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:25:54 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/09 18:25:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_keys_down(t_world *e, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
		e->keys.up = 1;
	else if (event.key.keysym.sym == SDLK_DOWN)
		e->keys.down = 1;
	else if (event.key.keysym.sym == SDLK_RIGHT)
		e->keys.right = 1;
	else if (event.key.keysym.sym == SDLK_LEFT)
		e->keys.left = 1;
	else if (event.key.keysym.sym == SDLK_KP_8)
		e->keys.key_8 = 1;
	else if (event.key.keysym.sym == SDLK_KP_7)
		e->keys.key_7 = 1;
	else if (event.key.keysym.sym == SDLK_KP_5)
		e->keys.key_5 = 1;
	else if (event.key.keysym.sym == SDLK_KP_4)
		e->keys.key_4 = 1;
	else if (event.key.keysym.sym == SDLK_KP_2)
		e->keys.key_2 = 1;
	else if (event.key.keysym.sym == SDLK_KP_1)
		e->keys.key_1 = 1;
	else if (event.key.keysym.sym == SDLK_w)
		e->keys.key_w = 1;
	else if (event.key.keysym.sym == SDLK_a)
		e->keys.key_a = 1;
	else if (event.key.keysym.sym == SDLK_s)
		e->keys.key_s = 1;
	else if (event.key.keysym.sym == SDLK_d)
		e->keys.key_d = 1;

	else if (event.key.keysym.sym == SDLK_q)
		e->keys.key_q = 1;
	else if (event.key.keysym.sym == SDLK_e)
		e->keys.key_e = 1;
	else if (event.key.keysym.sym == SDLK_o)
		e->keys.key_o = 1;
	else if (event.key.keysym.sym == SDLK_p)
		e->keys.key_p = 1;
	
	else if (event.key.keysym.sym == SDLK_LCTRL)
		e->keys.key_ctrl = 1;
	else if (event.key.keysym.sym == SDLK_SPACE)
		e->keys.key_space = 1;
	else if (event.key.keysym.sym == SDLK_LSHIFT)
		e->cam->speed = 1;
	else if (event.key.keysym.sym == SDLK_r && e->can_export)
	{
		ft_export_rt(e, ".ppm");
		e->can_export = 0;
	}
}

void	ft_keys_up(t_world *e, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
		e->keys.up = 0;
	else if (event.key.keysym.sym == SDLK_DOWN)
		e->keys.down = 0;
	else if (event.key.keysym.sym == SDLK_RIGHT)
		e->keys.right = 0;
	else if (event.key.keysym.sym == SDLK_LEFT)
		e->keys.left = 0;
	else if (event.key.keysym.sym == SDLK_p)
		e->keys.key_p = 0;
	else if (event.key.keysym.sym == SDLK_o)
		e->keys.key_o = 0;
	else if (event.key.keysym.sym == SDLK_KP_8)
		e->keys.key_8 = 0;
	else if (event.key.keysym.sym == SDLK_KP_7)
		e->keys.key_7 = 0;
	else if (event.key.keysym.sym == SDLK_KP_5)
		e->keys.key_5 = 0;
	else if (event.key.keysym.sym == SDLK_KP_4)
		e->keys.key_4 = 0;
	else if (event.key.keysym.sym == SDLK_KP_2)
		e->keys.key_2 = 0;
	else if (event.key.keysym.sym == SDLK_KP_1)
		e->keys.key_1 = 0;
	else if (event.key.keysym.sym == SDLK_w)
		e->keys.key_w = 0;
	else if (event.key.keysym.sym == SDLK_a)
		e->keys.key_a = 0;
	else if (event.key.keysym.sym == SDLK_s)
		e->keys.key_s = 0;
	else if (event.key.keysym.sym == SDLK_d)
		e->keys.key_d = 0;
	else if (event.key.keysym.sym == SDLK_q)
		e->keys.key_q = 0;
	else if (event.key.keysym.sym == SDLK_e)
		e->keys.key_e = 0;
	else if (event.key.keysym.sym == SDLK_LCTRL)
		e->keys.key_ctrl = 0;
	else if (event.key.keysym.sym == SDLK_SPACE)
		e->keys.key_space = 0;
	else if (event.key.keysym.sym == SDLK_LSHIFT)
		e->cam->speed = 0.2;
	else if (event.key.keysym.sym == SDLK_r)
		e->can_export = 1;
}

void	ft_mouse_motion(t_world *e, SDL_Event event)
{
	e->cam->rotation.x = e->cam->rotation.x - (event.motion.xrel) * M_PI / 1024.0;
	e->cam->rotation.y = ft_fclamp(-M_PI / 2, e->cam->rotation.y - (event.motion.yrel) * M_PI / 1024.0, M_PI / 2);
	apply_rotation(e->cam);
}
