/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nwords.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 02:09:30 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/16 06:21:21 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nwords(char const *s, char c)
{
	size_t	nwords;
	size_t	i;

	if (*s == '\0')
		return (0);
	nwords = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
		}
		if (s[i] != '\0')
			nwords++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
		}
	}
	return (nwords);
}
