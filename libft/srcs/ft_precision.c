/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 21:15:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:17:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_precision_base(t_pf pf, int base)
{
	int nb_diff;
	int res;

	res = 1;
	while (pf.var.integer / base != 0)
	{
		pf.var.integer /= base;
		res++;
	}
	nb_diff = pf.flags.precision - res;
	while (nb_diff > 0)
	{
		ft_putchar_buff('0');
		nb_diff--;
	}
}

void	ft_add_precision_o(t_pf pf)
{
	int nb_diff;
	int res;

	res = 1 + pf.flags.display_style;
	while (pf.var.integer / 8 != 0)
	{
		pf.var.integer /= 8;
		res++;
	}
	nb_diff = pf.flags.precision - res;
	while (nb_diff > 0)
	{
		ft_putchar_buff('0');
		nb_diff--;
	}
}

void	ft_add_precision_base_u(t_pf pf, int base)
{
	int				nb_diff;
	int				res;
	unsigned int	nb;

	nb = pf.var.integer;
	res = 1;
	while (nb / base != 0)
	{
		nb /= base;
		res++;
	}
	nb_diff = pf.flags.precision - res;
	while (nb_diff > 0)
	{
		ft_putchar_buff('0');
		nb_diff--;
	}
}
