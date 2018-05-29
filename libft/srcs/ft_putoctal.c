/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:33:02 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 22:59:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putoctal(unsigned int nb, int fd)
{
	if ((nb / 8) == 0)
		ft_putchar_buff(nb % 8 + '0', fd);
	else
	{
		ft_putoctal(nb / 8, fd);
		ft_putchar_buff(nb % 8 + '0', fd);
	}
}
