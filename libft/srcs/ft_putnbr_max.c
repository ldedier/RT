/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 16:42:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 22:58:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_max(uintmax_t nb, int fd)
{
	if ((uintmax_t)((uintmax_t)nb / (uintmax_t)10) == 0)
		ft_putchar_buff(nb % 10 + '0', fd);
	else
	{
		ft_putnbr_max((uintmax_t)((uintmax_t)nb / (uintmax_t)10), fd);
		ft_putchar_buff(nb % 10 + '0', fd);
	}
}
