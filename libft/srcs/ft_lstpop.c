/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:55:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/08 04:56:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop(t_list **list)
{
	void	*content;
	t_list	*ptr;

	if (*list != NULL)
	{
		ptr = *list;
		content = ptr->content;
		*list = (*list)->next;
		free(ptr);
		return (content);
	}
	return (NULL);
}
