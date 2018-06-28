/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:14:21 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 08:14:17 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_export_bmp(char *name, t_image image)
{
	int fd;
	int wr;

	if ((fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
		return (-1);
	wr = write(fd, "BM", 2);
	(void)wr;
	(void)image;
	(void)name;
	return (0);
}
