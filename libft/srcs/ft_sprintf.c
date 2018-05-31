/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:38:11 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 02:52:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



int		ft_svprintf(char *buffer, const char *format, va_list va)
{
	t_pf		pf;
	int			i;

	pf.buffer = buffer;
	ft_init_pf(&pf);
	i = 0;
	while (format[i] != '\0')
	{
		while (format[i] != '\0' && format[i] != '%')
		{
			ft_putchar_buff(format[i], pf.fd);
			i++;
		}
		if (format[i] == '%')
		{
			if (ft_process_percent(format, &i, &pf, va) == -1)
				return (-1);
		}
	}
	ft_empty_buffer(pf.fd);
	return (ft_reset_return());
}

int     ft_sprintf(char *buffer, const char *restrict format, ...)
{

	static int  broken = 0;
	int         ret;
	va_list     va;

	va_start(va, format);
	if ((ret = ft_svprintf(buffer, format, va)) == -1)
		broken = 1;
	va_end(va);
	if (broken)
		return (-1);
	else
		return (ret);
}
