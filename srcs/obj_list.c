/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 22:42:29 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 18:14:10 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		add_obj(t_objlist **lst, t_object *object)
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

void		add_obj_cpy(t_objlist **lst, t_object *object)
{
	t_objlist	*new;
	t_object	*new_obj;

	if (!(new = malloc(sizeof(t_objlist))))
	{
		perror("cant malloc new node");
		exit(errno);
	}
	if (!(new_obj = malloc(sizeof(t_object))))
		ft_error("error malloc");
	new->object = ft_memcpy(new_obj, object, sizeof(t_object));
	new->next = *lst;
	*lst = new;
}

void		add_cobj(t_cobjlist **lst, t_cobject *cobject)
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

void		add_cobj_cpy(t_cobjlist **lst, t_cobject *cobject)
{
	t_cobjlist	*new;
	t_cobject	*new_cobj;

	if (!(new = malloc(sizeof(t_cobjlist))))
	{
		perror("cant malloc new node");
		exit(errno);
	}
	if (!(new_cobj = malloc(sizeof(t_cobject))))
		ft_error("error malloc");
	new->cobject = ft_memcpy(new_cobj, cobject, sizeof(t_cobject));
	new->cobject->objlist = objlist_cpy(cobject->objlist);
	new->next = *lst;
	*lst = new;
}
