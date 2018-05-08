/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:12:15 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 17:29:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_image		ft_new_image(int width, int height, int *pix)
{
	t_image img;

	img.width = width;
	img.height = height;
	img.pix = pix;
	return (img);
}
