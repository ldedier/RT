/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ppm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:07:03 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/09 01:11:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_export_ppm(char *name, t_image image)
{
	int fd;
	int i;
	int j;

	if ((fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1) 
		return (-1);
	ft_dprintf(fd, "P3\n%d %d\n255\n", image.width, image.height);
	i = 0;
	while (i < image.height)
	{
		j = 0;
		while (j < image.width)
		{
			ft_dprintf(fd, "%d	%d	%d	",
					image.pix[j + i * image.width] & 0xff,
				(image.pix[j + i * image.width] >> 8) & 0xff,
					(image.pix[j + i * image.width] >> 16) & 0xff);
			j++;
		}
		ft_dprintf(fd, "\n");
		i++;
	}
	return (0);
}
