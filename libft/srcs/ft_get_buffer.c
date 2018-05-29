/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:55:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 23:13:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_empty_buffer(int fd)
{
	int		display;
	char	*toprint;

	display = 0;
	toprint = ft_get_buffer("", 0, &display, fd);
	write(fd, toprint, display);
	ft_add_return(display);
	display = 1;
	ft_get_buffer("", 0, &display, fd);
}

char	*ft_get_buffer(const void *s, size_t n, int *display, int fd)
{
	static char	buffer[BUF_SIZE] = {0};
	static int	cursor = 0;

	if (*display)
		cursor = 0;
	else
	{
		if (cursor + n < BUF_SIZE)
		{
			ft_strncpy(&(buffer[(int)(cursor)]), s, n);
			cursor += n;
		}
		else
		{
			ft_empty_buffer(fd);
			write(fd, s, n);
			ft_add_return(n);
		}
	}
	*display = cursor;
	return ((char *)(buffer));
}
