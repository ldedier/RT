/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 08:21:48 by lcavalle          #+#    #+#             */
/*   Updated: 2017/11/14 08:59:43 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *aux;

	while ((*alst)->next != NULL)
	{
		aux = *alst;
		del((*alst)->content, (*alst)->content_size);
		*alst = (*alst)->next;
		free(aux);
	}
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	((*alst) = NULL);
}
