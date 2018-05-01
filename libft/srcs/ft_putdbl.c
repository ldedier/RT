/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:56:20 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/28 21:21:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putdbl_process(int d, int decal)
{
	if (d / 10 == 0)
	{
		ft_putchar_buff(d % 10 + '0');
	}
	else
	{
		ft_putdbl_process(d / 10, decal - 1);
		ft_putchar_buff(d % 10 + '0');
	}
	if (decal == 0)
		ft_putchar_buff('.');
}

void	ft_putdbl_short(double d, int precision)
{
	int		decal;
	double	frac;

	decal = 0;
	frac = d - (int)d;
	while (frac != 0 && precision)
	{
		d = d * 10;
		frac = d - (int)d;
		decal++;
		precision--;
	}
	if (d < 0)
		ft_putchar_buff('-');
	ft_putdbl_process(ft_fabs(d), decal);
	precision--;
	while (precision >= 0)
	{
		ft_putchar_buff('0');
		precision--;
	}
}

void	ft_process_precision_double(int precision, double frac, int decal)
{
	double frac2;

	frac2 = 1;
	while (frac2 != 0 && precision)
	{
		frac = frac * 10;
		frac2 = frac - (intmax_t)frac;
		decal++;
		precision--;
	}
	ft_putchar_buff('.');
	ft_putnbr_max((intmax_t)frac);
	precision--;
	while (precision >= 0)
	{
		ft_putchar_buff('0');
		precision--;
	}
}

void	ft_putdbl_long(double d, int precision)
{
	int		decal;
	double	frac;

	if (d < 0)
	{
		ft_putchar_buff('-');
		d = -d;
	}
	decal = 0;
	frac = d - (intmax_t)d;
	ft_putnbr_max(ft_abs_max((intmax_t)(d)));
	if (precision != 0)
		ft_process_precision_double(precision, frac, decal);
}

void	ft_putdbl(double d, int precision)
{
	if (ft_fabs(d) > 65655)
		ft_putdbl_long(d, precision);
	else
		ft_putdbl_short(d, precision);
}
