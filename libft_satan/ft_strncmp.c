/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:25:45 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/15 18:25:26 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	lesslen;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1) + 1;
	s2len = ft_strlen(s2) + 1;
	if (s1len <= s2len)
		lesslen = s1len;
	else
		lesslen = s2len;
	if (n < lesslen)
		lesslen = n;
	return (ft_memcmp(s1, s2, lesslen));
}
