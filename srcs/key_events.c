/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:27:44 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/05 03:39:12 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_keys_event(t_world *e, SDL_Event event, int press)
{
	if (e->focus || !e->focus)
	{
		if (event.key.keysym.sym == SDLK_UP)
			e->keys[up] = press;
		else if (event.key.keysym.sym == SDLK_DOWN)
			e->keys[down] = press;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			e->keys[right] = press;
		else if (event.key.keysym.sym == SDLK_LEFT)
			e->keys[left] = press;
		else if (event.key.keysym.sym == SDLK_KP_8)
			e->keys[key_8] = press;
		else if (event.key.keysym.sym == SDLK_KP_7)
			e->keys[key_7] = press;
		else if (event.key.keysym.sym == SDLK_KP_5)
			e->keys[key_5] = press;
		else if (event.key.keysym.sym == SDLK_KP_4)
			e->keys[key_4] = press;
		else if (event.key.keysym.sym == SDLK_KP_2)
			e->keys[key_2] = press;
		else if (event.key.keysym.sym == SDLK_KP_1)
			e->keys[key_1] = press;
		else if (event.key.keysym.sym == SDLK_w)
			e->keys[key_w] = press;
		else if (event.key.keysym.sym == SDLK_a)
			e->keys[key_a] = press;
		else if (event.key.keysym.sym == SDLK_s)
			e->keys[key_s] = press;
		else if (event.key.keysym.sym == SDLK_d)
			e->keys[key_d] = press;
		else if (event.key.keysym.sym == SDLK_q)
			e->keys[key_q] = press;
		else if (event.key.keysym.sym == SDLK_e)
			e->keys[key_e] = press;
		else if (event.key.keysym.sym == SDLK_z)
			e->keys[key_z] = press;
		else if (event.key.keysym.sym == SDLK_c)
			e->keys[key_c] = press;
		else if (event.key.keysym.sym == SDLK_x)
			e->keys[key_x] = press;
		else if (event.key.keysym.sym == SDLK_v)
			e->keys[key_v] = press;
		else if (event.key.keysym.sym == SDLK_o)
			e->keys[key_o] = press;
		else if (event.key.keysym.sym == SDLK_p)
			e->keys[key_p] = press;
		else if (event.key.keysym.sym == SDLK_n)
			e->keys[key_n] = press;
		else if (event.key.keysym.sym == SDLK_m)
			e->keys[key_m] = press;
		else if (event.key.keysym.sym == SDLK_f && press == 1)
			e->animate = !e->animate;
		else if (event.key.keysym.sym == SDLK_LCTRL)
			e->keys[key_ctrl] = press;
		else if (event.key.keysym.sym == SDLK_k)
			e->keys[key_k] = press;
		else if (event.key.keysym.sym == SDLK_l)
			e->keys[key_l] = press;
		else if (event.key.keysym.sym == SDLK_SPACE)
			e->keys[key_space] = press;
		else if (event.key.keysym.sym == SDLK_RETURN && e->progress == 0)
			e->keys[key_enter] = press;
		else if (event.key.keysym.sym == SDLK_LSHIFT)
		{
			if (press == 1)
				e->cam->speed = 1;
			else
				e->cam->speed = 0.2;
		}
		else if (event.key.keysym.sym == SDLK_r)
		{
			if (press == 1)
			{
				if (e->can_export)
				{
					ft_export_rt(e, ".ppm");
					e->can_export = 0;
				}
			}
			else
				e->can_export = 1;
		}
		else if (event.key.keysym.sym == SDLK_h)
		{
			if (press == 1 && e->can_export)
			{
				if (e->exporting_video)
				{
					ft_export_y4m(e->video);
					e->exporting_video = 0;
				}
				else
					e->exporting_video = 1;
			}
			else
				e->can_export = 1;
		}
		else if (event.key.keysym.sym == SDLK_y)
		{
			if (press == 1)
			{
				if (e->can_export)
				{
					ft_export_scene(e);
					e->can_export = 0;
				}
			}
			else
				e->can_export = 1;
		}
	}
}
