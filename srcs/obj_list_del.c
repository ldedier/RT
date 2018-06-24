/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 05:14:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 15:17:09 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		del_list(t_objlist **lst)
{
	t_objlist	*aux;

	while (*lst != NULL)
	{
		aux = *lst;
		*lst = (*lst)->next;
		free(aux->object->descriptor);
		if (aux->object->parser.pixels)
			free(aux->object->parser.pixels);
		if (aux->object->parser.filename)
			free(aux->object->parser.filename);
		if (aux->object->parser_normal.pixels)
			free(aux->object->parser_normal.pixels);
		if (aux->object->parser_normal.filename)
			free(aux->object->parser_normal.filename);
		free(aux->object);
		free(aux);
		aux = NULL;
	}
}

void		del_clst(t_cobjlist **lst)
{
	t_cobjlist	*aux;

	while (*lst != NULL)
	{
		aux = *lst;
		*lst = (*lst)->next;
		del_list(&(aux->cobject->objlist));
		free(aux->cobject->name);
		free(aux->cobject->descriptor);
		free(aux->cobject->filename);
		free(aux->cobject);
		free(aux);
		aux = NULL;
	}
}
