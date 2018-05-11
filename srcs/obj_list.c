/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:42:29 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/11 18:13:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_cobj(t_objlist **lst, t_cobject *cobject)
{
	t_cobjlist	*prev;
	t_cobjlist	*first;

	prev = *lst;
	first = *lst;
	while (*lst != NULL)
	{
		prev = *lst;
		*lst = (*lst)->next;
	}
	if (!(*lst = malloc(sizeof(t_cobjlist))))
	{
		perror("cant malloc new object");
		exit(errno);
	}
	if (first == NULL)
		first = *lst;
	(*lst)->next = NULL;
	(*lst)->cobject = cobject;
	if (prev != NULL)
		prev->next = *lst;
	*lst = first;
}

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

void	del_list(t_objlist **lst)
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

void	del_clst(t_cobjlist **lst)
{
	t_cobjlist	*aux;

	while (*lst != NULL)
	{
		aux = *lst;
		*lst = (*lst)->next;
		del_list(&(aux->cobject->objlist));
		free(aux->cobject);
		free(aux);
		aux = NULL;
	}
}
