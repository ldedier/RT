/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:55:59 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/12 05:15:40 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t nl;

	if (*needle == '\0')
		return ((char *)haystack);
	nl = ft_strlen(needle);
	haystack = ft_strchr(haystack, needle[0]);
	while (haystack != NULL)
	{
		if (ft_strncmp(haystack, needle, nl) == 0)
			return ((char *)haystack);
		haystack = ft_strchr(haystack + 1, needle[0]);
	}
	return (0);
}
