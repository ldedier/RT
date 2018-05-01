/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:04:01 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/15 18:50:32 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;

	if (!s || (ss = ft_strnew(len)) == NULL)
		return (NULL);
	i = (size_t)start;
	while (i < len + start)
	{
		ss[i - start] = s[i];
		i++;
	}
	return (ss);
}
