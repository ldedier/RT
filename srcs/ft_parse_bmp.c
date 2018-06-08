/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:48:32 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/07 23:59:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bmp_parser	ft_parse_bmp(char *filename)
{
	t_mmap			map;
	t_bmp_parser	parser;
	int				size;
	int				i;

	i = 0;
	map = ft_map_file(filename);
	if ((ft_strlen((char *)map.ptr) < 2) || map.ptr[0] != 'B' ||
			map.ptr[1] != 'M')
	{
		parser.pixels = NULL;
		munmap(map.ptr, map.size);
		return (parser);
	}
	parser.width = *(int *)&(map.ptr[18]);
	parser.height = *(int *)&(map.ptr[22]);
	parser.bpp = *(short *)&(map.ptr[28]);
	parser.bitmap_index = *(int *)&(map.ptr[10]);

	size = parser.width * parser.height * (parser.bpp / 8);
	parser.pixels = malloc(sizeof(unsigned char) * size + 1);

	i = 0;
	while (i < size)
	{
		parser.pixels[i] = map.ptr[i + parser.bitmap_index + 0];
		parser.pixels[i + 1] = map.ptr[i + parser.bitmap_index + 1];
		parser.pixels[i + 2] = map.ptr[i + parser.bitmap_index + 2];
		parser.pixels[i + 3] = map.ptr[i + parser.bitmap_index + 3];
		i+= parser.bpp / 8;
	}
	munmap(map.ptr, map.size);
	return (parser);
}
