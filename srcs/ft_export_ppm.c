/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ppm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:07:03 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 19:30:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		length_integer(int a)
{
	int res;

	if (a < 0)
		res = 2;
	else
		res = 1;
	while (res / 10 != 0)
		res /= 10;
	return (res);
}

int		ppm_image_header_length(t_image image)
{
	return (9 + length_integer(image.width) + length_integer(image.height));
}

void	ft_process_export_ppm(char *buff, int width, int height, int *pix)
{
	int n;
	int i;
	int j;

	n = ft_sprintf(buff, "P3\n%d %d\n255\n", width, height);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			n += ft_sprintf(&(buff[n]), "%d	%d	%d	",
					(pix[j + i * width] >> 16) & 0xff,
				(pix[j + i * width] >> 8) & 0xff,
					pix[j + i * width] & 0xff);
			j++;
		}
		n += ft_sprintf(&(buff[n]), "\n");
		i++;
	}
}

int		ft_export_ppm(char *name, t_image image)
{
	int		fd;
	char	*buff;

	buff = ft_strnew(4 * 3 * image.width * image.height + image.width +
		ppm_image_header_length(image));
	if ((fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
		return (-1);
	ft_process_export_ppm(buff, image.width, image.height, image.pix);
	ft_dprintf(fd, "%s", buff);
	close(fd);
	return (0);
}
