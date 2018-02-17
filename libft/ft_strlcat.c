/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:19:12 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/18 03:30:49 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t lend;
	size_t lens;

	lend = ft_pstrchr(&dst, '\0');
	lens = ft_strlen(src);
	if (lend < size)
	{
		if (ft_strncpy(dst, src, size - lend - 1) == NULL)
		{
			return (0);
		}
		dst[size - lend - 1] = '\0';
		return (lens + lend);
	}
	else
		return (lens + size);
}
