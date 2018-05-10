/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:56:20 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 23:11:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putdbl_process(int d, int decal, int fd)
{
	if (d / 10 == 0)
	{
		ft_putchar_buff(d % 10 + '0', fd);
	}
	else
	{
		ft_putdbl_process(d / 10, decal - 1, fd);
		ft_putchar_buff(d % 10 + '0', fd);
	}
	if (decal == 0)
		ft_putchar_buff('.', fd);
}

void	ft_putdbl_short(double d, int precision, int fd)
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
		ft_putchar_buff('-', fd);
	ft_putdbl_process(ft_fabs(d), decal, fd);
	precision--;
	while (precision >= 0)
	{
		ft_putchar_buff('0', fd);
		precision--;
	}
}

void	ft_process_precision_double(int pre, double frac, int decal, int fd)
{
	double frac2;

	frac2 = 1;
	while (frac2 != 0 && pre)
	{
		frac = frac * 10;
		frac2 = frac - (intmax_t)frac;
		decal++;
		pre--;
	}
	ft_putchar_buff('.', fd);
	ft_putnbr_max((intmax_t)frac, fd);
	pre--;
	while (pre >= 0)
	{
		ft_putchar_buff('0', fd);
		pre--;
	}
}

void	ft_putdbl_long(double d, int precision, int fd)
{
	int		decal;
	double	frac;

	if (d < 0)
	{
		ft_putchar_buff('-', fd);
		d = -d;
	}
	decal = 0;
	frac = d - (intmax_t)d;
	ft_putnbr_max(ft_abs_max((intmax_t)(d)), fd);
	if (precision != 0)
		ft_process_precision_double(precision, frac, decal, fd);
}

void	ft_putdbl(double d, int precision, int fd)
{
	if (ft_fabs(d) > 65655)
		ft_putdbl_long(d, precision, fd);
	else
		ft_putdbl_short(d, precision, fd);
}
