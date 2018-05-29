/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:33:11 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/18 03:26:17 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	size;
	void	*aux;

	size = ft_strlen(src) + 1;
	if ((aux = ft_memccpy(dst, src, '\0', len)) != NULL)
		if (size < len)
			ft_bzero(aux, len - size);
	return (dst);
}
