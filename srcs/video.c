/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:44:58 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/05 05:36:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_video(t_video *video)
{
	video->width = HRES / VIDEO_RES_RATIO;
	video->height = VRES / VIDEO_RES_RATIO;
	video->images = NULL;
}

void	ft_add_frame_to_video(t_world *world)
{
	int *pix;
	int *frame;
	int i;
	int j;
	t_pixel res;

	pix = (int *)world->canvas->surface->pixels;
	res.x = HRES / VIDEO_RES_RATIO;
	res.y = VRES / VIDEO_RES_RATIO;
	frame = malloc(sizeof(int) * res.x * res.y);
	i = 0;
	while (i < res.y)
	{
		j = 0;
		while (j < res.x)
		{
			frame[j + i * res.x] = pix[VIDEO_RES_RATIO * (j + i * HRES)];
			j++;
		}
		i++;
	}
	ft_lstpushback(&(world->video.images), ft_lstnew_ptr(frame, 
				sizeof(int) * res.x * res.y));
}
