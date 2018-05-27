/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 07:08:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/27 07:09:28 by ldedier          ###   ########.fr       */
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
	fstat (fd, &s);
	size = s.st_size;
	res.ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
	res.size = size;
	return (res);
}

