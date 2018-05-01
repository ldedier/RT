/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_buff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 21:20:43 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/11 15:45:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_buff(char c)
{
	int		display;
	char	str[2];

	display = 0;
	str[0] = c;
	str[1] = '\0';
	ft_get_buffer((char *)str, 1, &display);
}
