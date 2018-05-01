/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:11:39 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/15 23:21:35 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*dst;

	len = ft_strlen(s1);
	if ((dst = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	return ((char *)ft_memcpy(dst, (void*)s1, len + 1));
}
