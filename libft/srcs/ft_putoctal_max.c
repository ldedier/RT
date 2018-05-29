/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal_max.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 21:43:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 23:00:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putoctal_max(uintmax_t nb, int fd)
{
	if ((nb / 8) == 0)
		ft_putchar_buff(nb % 8 + '0', fd);
	else
	{
		ft_putoctal_max((uintmax_t)nb / (uintmax_t)8, fd);
		ft_putchar_buff(nb % 8 + '0', fd);
	}
}
