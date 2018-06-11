/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 05:06:43 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 05:10:28 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_init_objects(t_world *world)
{
	t_cobjlist	*lst;
	t_objlist	*lst2;

	lst = world->cobjlist;
	while (lst != NULL)
	{
		lst->cobject->scale = 1;
		lst2 = lst->cobject->objlist;
		while (lst2 != NULL)
		{
			lst2->object->scale = 1;
			lst2 = lst2->next;
		}
		lst = lst->next;
	}
}

int			ft_lights_scrollbar_size(t_world *world, int len)
{
	int			h;
	float		size;

	h = world->nlights * (50 + 15);
	if (h <= len)
		size = 1;
	else
		size = len / (float)h;
	return ((len - 10) * size);
}

t_scrollbar	ft_new_scrollbar(t_world *world, int len, int type)
{
	t_scrollbar	sb;

	sb.active = 0;
	sb.len = len;
	if (type == 0)
		sb.height = ft_lights_scrollbar_size(world, len);
	else
		sb.height = ft_objects_scrollbar_size(world, len);
	sb.pos = 0;
	sb.step = 0;
	return (sb);
}

void		ft_cobjlist_reverse(t_cobjlist **alst)
{
	t_cobjlist	*new;
	t_cobjlist	*next;
	t_cobjlist	*current;

	new = 0;
	current = *alst;
	while (current != NULL)
	{
		next = current->next;
		current->next = new;
		new = current;
		current = next;
	}
	*alst = new;
}

void		ft_objlist_reverse(t_objlist **alst)
{
	t_objlist	*new;
	t_objlist	*next;
	t_objlist	*current;

	new = 0;
	current = *alst;
	while (current != NULL)
	{
		next = current->next;
		current->next = new;
		new = current;
		current = next;
	}
	*alst = new;
}
