/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:27:10 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/18 04:05:58 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	pos;
	size_t	i;
	int		found;

	found = 0;
	i = 0;
	while (s[i] != '\0' || (c == '\0' && found == 0))
	{
		if (s[i] == c)
		{
			pos = i;
			found = 1;
		}
		i++;
	}
	if (found == 0)
		return (NULL);
	else
		return ((char *)s + pos);
}
