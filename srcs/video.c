/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:44:58 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 07:55:51 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_video(t_world *world, t_video *video)
{
	video->width = world->canvas->win_size.x / VIDEO_RES_RATIO;
	video->height = world->canvas->win_size.y / VIDEO_RES_RATIO;
	video->images = NULL;
}

void	ft_add_frame_to_video(t_world *world)
{
	int		*pix;
	int		*frame;
	int		i;
	int		j;
	t_pixel	res;

	pix = (int *)world->canvas->surface->pixels;
	res.x = world->canvas->win_size.x / VIDEO_RES_RATIO;
	res.y = world->canvas->win_size.y / VIDEO_RES_RATIO;
	if (!(frame = malloc(sizeof(int) * res.x * res.y)))
		ft_error("malloc error");
	i = 0;
	while (i < res.y)
	{
		j = 0;
		while (j < res.x)
		{
			frame[j + i * res.x] = pix[VIDEO_RES_RATIO *
				(j + i * world->canvas->win.w)];
			j++;
		}
		i++;
	}
	ft_lstpushback(&(world->video.images), ft_lstnew_ptr(frame,
				sizeof(int) * res.x * res.y));
}
