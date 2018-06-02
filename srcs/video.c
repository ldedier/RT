/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:44:58 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/02 03:19:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_video(t_video *video)
{
	video->width = HRES;
	video->height = VRES;
	video->images = NULL;
}

void	ft_add_frame_to_video(t_world *world)
{
	int *pix;

	pix = (int *)world->canvas->surface->pixels;
	ft_lstpushback(&(world->video.images), ft_lstnew(pix, sizeof(int) * VRES * HRES));
}
