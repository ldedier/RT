/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defining.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 18:45:54 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/30 22:44:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

t_cobject *get_defcobject(char *str, t_cobjlist *cobjlist)
{
	t_cobjlist *ptr;

	ptr = cobjlist;
	while (ptr != NULL)
	{
		if (ptr->cobject->name && !ft_strcmp(ptr->cobject->name, str))
			return (ptr->cobject);
		ptr = ptr->next;
	}
	return (NULL);
}

int		already_exists_defcobj(char *str, t_cobjlist *cobjlist)
{
	t_cobjlist *ptr;

	ptr = cobjlist;
	while (ptr != NULL)
	{
		if (ptr->cobject->name && !ft_strcmp(ptr->cobject->name, str))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	ft_process_switch_list_cobject(t_cobjlist **cobjlist,
		t_cobjlist **defcobjlist)
{
	t_cobjlist *tmp;

	tmp = *cobjlist;
	tmp->cobject->defining = 0;
	*cobjlist = (*cobjlist)->next;
	tmp->next = *defcobjlist;
	*defcobjlist = tmp;
}
