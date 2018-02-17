/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putctab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:29:20 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/26 05:06:44 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putctab(char **tab)
{
	while (tab != NULL && *tab != NULL)
	{
		ft_putendl(*tab);
		tab++;
	}
}
