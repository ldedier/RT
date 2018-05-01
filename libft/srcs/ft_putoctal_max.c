/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal_max.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 21:43:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:15:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putoctal_max(uintmax_t nb)
{
	if ((nb / 8) == 0)
		ft_putchar_buff(nb % 8 + '0');
	else
	{
		ft_putoctal_max((uintmax_t)nb / (uintmax_t)8);
		ft_putchar_buff(nb % 8 + '0');
	}
}
