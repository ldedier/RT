/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:33:06 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/16 06:21:37 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**a;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s || !c)
		return (NULL);
	if ((a = (char **)ft_memalloc((ft_nwords(s, c) + 1) * P_SIZE)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_nwords(s, c))
	{
		while (s[j] == c)
			j++;
		k = 0;
		while (s[j + k] != c && s[j + k] != '\0')
			k++;
		a[i] = ft_strsub(s, (unsigned int)j, k);
		j += k;
		i++;
	}
	a[i] = NULL;
	return (a);
}
