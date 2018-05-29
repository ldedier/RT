/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 02:41:11 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/18 00:02:57 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	size_t	digits;
	size_t	i;

	digits = (ft_ndigits(n));
	if ((str = ft_strnew(digits)) == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		if (n == -MAX_INT - 1)
			return (ft_strcpy(str, "-2147483648"));
		str[i] = '-';
		n = -n;
		i++;
	}
	while (i < digits)
	{
		str[digits - 1] = (n % 10) + '0';
		n = n / 10;
		digits--;
	}
	return (str);
}
