/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 23:33:02 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:14:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putoctal(unsigned int nb)
{
	if ((nb / 8) == 0)
		ft_putchar_buff(nb % 8 + '0');
	else
	{
		ft_putoctal(nb / 8);
		ft_putchar_buff(nb % 8 + '0');
	}
}
