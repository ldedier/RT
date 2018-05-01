/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:55:59 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/16 08:07:46 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nl;
	size_t	i;
	char	*hayaux;

	if (*needle == '\0')
		return ((char *)haystack);
	hayaux = (char *)haystack;
	nl = ft_strlen(needle);
	i = 0;
	while (*hayaux != '\0' && i < len - (nl - 1))
	{
		if (nl > len)
			return (NULL);
		i += ft_pstrchr(&hayaux, needle[0]);
		if (i < len - (nl - 1) && ft_strncmp(hayaux, needle, nl) == 0)
			return ((char *)hayaux);
		if (*hayaux == '\0')
			return (NULL);
		i++;
		hayaux++;
	}
	return (NULL);
}
