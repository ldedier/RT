/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 05:14:30 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 05:14:33 by ldedier          ###   ########.fr       */
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
		free(aux->cobject);
		free(aux);
		aux = NULL;
	}
}
