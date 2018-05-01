/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:17:50 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/27 20:58:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_non_printable(char const *s, size_t n)
{
	int display;
	int i;

	i = 0;
	while (s[i] && n - i)
	{
		display = 0;
		if (ft_isprint(s[i]))
			ft_get_buffer(&(s[i]), 1, &display);
		else
			ft_get_buffer(".", 1, &display);
		i++;
	}
}
