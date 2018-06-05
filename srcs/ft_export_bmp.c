/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:14:21 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 21:48:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_export_bmp(char *name, t_image image)
{
	int fd;

	if ((fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
		return (-1);
	write(fd, "BM", 2);
//	write(fd, )
	(void)image;
	(void)name;
	return 0;
}
