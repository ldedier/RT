/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:55:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/11 15:43:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_empty_buffer(void)
{
	int		display;
	char	*toprint;

	display = 0;
	toprint = ft_get_buffer("", 0, &display);
	write(1, toprint, display);
	ft_add_return(display);
	display = 1;
	ft_get_buffer("", 0, &display);
}

char	*ft_get_buffer(const void *s, size_t n, int *display)
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
			ft_empty_buffer();
			write(1, s, n);
			ft_add_return(n);
		}
	}
	*display = cursor;
	return ((char *)(buffer));
}
