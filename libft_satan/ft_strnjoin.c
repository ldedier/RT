/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:15:35 by lcavalle          #+#    #+#             */
/*   Updated: 2017/12/04 18:34:26 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, size_t n1, char const *s2, size_t n2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if ((str = ft_strnew(n1 + n2 + 1)) == NULL)
		return (NULL);
	str = ft_strncat(ft_strncpy(str, s1, n1), s2, n2);
	return (str);
}
