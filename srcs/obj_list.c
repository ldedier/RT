/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:42:29 by lcavalle          #+#    #+#             */
/*   Updated: 2018/04/24 19:16:00 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_obj(t_objlist **lst, t_object *object)
{
	t_objlist	*prev;
	t_objlist	*first;

	prev = *lst;
	first = *lst;
	while (*lst != NULL)
	{
		prev = *lst;
		*lst = (*lst)->next;
	}
	if (!(*lst = malloc(sizeof(t_objlist))))
	{
		perror("cant malloc new object");
		exit(errno);
	}
	if (first == NULL)
		first = *lst;
	(*lst)->next = NULL;
	(*lst)->object = object;
	if (prev != NULL)
		prev->next = *lst;
	*lst = first;
}

void	del_lst(t_objlist **lst)
{
	t_objlist	*aux;

	while (*lst != NULL)
	{
		aux = *lst;
		*lst = (*lst)->next;
		free(aux->object);
		free(aux);
		aux = NULL;
	}
}
