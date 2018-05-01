/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putitab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:29:20 by lcavalle          #+#    #+#             */
/*   Updated: 2017/12/11 02:21:35 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putitab(int **tab, int i, int j)
{
	int k;
	int l;

	k = 0;
	while (k < i)
	{
		l = 0;
		while (l < j)
		{
			ft_putnbr(tab[k][l]);
			ft_putchar(' ');
			l++;
		}
		ft_putchar('\n');
		k++;
	}
}
