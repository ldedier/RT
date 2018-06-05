/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:42:29 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/30 22:33:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_obj(t_objlist **lst, t_object *object)
{
	t_objlist *new;

	if (!(new = malloc(sizeof(t_objlist))))
	{
		perror("cant malloc new node");
		exit(errno);
	}
	new->object = object;
	new->next = *lst;
	*lst = new;
}

void	add_obj_cpy(t_objlist **lst, t_object *object)
{
	t_objlist *new;
	t_object *new_obj;
	if (!(new = malloc(sizeof(t_objlist))))
	{
		perror("cant malloc new node");
		exit(errno);
	}
	new_obj = malloc(sizeof(t_object));
	new->object = ft_memcpy(new_obj, object, sizeof(t_object));
	new->next = *lst;
	*lst = new;
}

void	add_cobj(t_cobjlist **lst, t_cobject *cobject)
{
	t_cobjlist *new;

	if (!(new = malloc(sizeof(t_cobjlist))))
	{
		perror("cant malloc new node");
		exit(errno);
	}
	new->cobject = cobject;
	new->next = *lst;
	*lst = new;
}

t_objlist	*objlist_cpy(t_objlist *objlist)
{
	t_objlist *ptr;
	t_objlist *res;

	res = NULL;
	ptr = objlist;
	while (ptr)
	{
		add_obj_cpy(&res, ptr->object);
		ptr = ptr->next;
	}
	return (res);
}

void	add_cobj_cpy(t_cobjlist **lst, t_cobject *cobject)
{
	t_cobjlist *new;
	t_cobject *new_cobj;
	if (!(new = malloc(sizeof(t_cobjlist))))
	{
		perror("cant malloc new node");
		exit(errno);
	}
	new_cobj = malloc(sizeof(t_cobject));
	new->cobject = ft_memcpy(new_cobj, cobject, sizeof(t_cobject));
	new->cobject->objlist = objlist_cpy(cobject->objlist);
	new->next = *lst;
	*lst = new;
}
/*
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
*/
/*
void	add_cobj(t_cobjlist **lst, t_cobject *cobject)
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
*/
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
