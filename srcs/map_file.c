/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 07:08:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/05 23:23:18 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mmap  ft_map_file(char *filename)
{
	t_mmap res;
	int fd;
	int size;
	struct stat s;

	fd = open (filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "could not open file\n");
		exit(1);
	}
	fstat (fd, &s);
	size = s.st_size;
	res.ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
	res.size = size;
	return (res);
}

