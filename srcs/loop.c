/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 02:47:18 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/01 03:26:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_loop(t_world *e)
{
	int end;
	SDL_Event event;
//	ft_init_scene(e);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	paint_threaded(e);
	end = 0;
	while (!end)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN)
				ft_keys_down(e, event);
			if (event.type == SDL_KEYUP)
				ft_keys_up(e, event);
			if (event.type == SDL_MOUSEMOTION)
				ft_mouse_motion(e, event);
			if (event.window.event == SDL_WINDOWEVENT_CLOSE ||
					(event.key.keysym.sym == SDLK_ESCAPE
					 && event.type == SDL_KEYDOWN))
				end = 1;
		}
		if(1) // KEY PRESSED
		{
			ft_process(e);
			paint_threaded(e);
		}
		SDL_Delay(12);
	}
}
