/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:54:25 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/18 03:30:42 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*aux;
	size_t			i;

	if ((aux = (unsigned char*)malloc(sizeof(char) * len)) == NULL)
		return (dst);
	i = 0;
	while (i < len)
	{
		aux[i] = ((unsigned char*)src)[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		((unsigned char*)dst)[i] = aux[i];
		i++;
	}
	free(aux);
	aux = NULL;
	return (dst);
}
