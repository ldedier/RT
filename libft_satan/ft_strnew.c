/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:54:52 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/15 18:26:36 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	if ((str = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < size + 1)
		str[i++] = '\0';
	return (str);
}
