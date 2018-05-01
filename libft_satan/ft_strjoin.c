/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:15:35 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/15 18:42:00 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if ((str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
		return (NULL);
	str = ft_strcat(ft_strcpy(str, s1), s2);
	return (str);
}
