/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_tools_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 05:10:59 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 05:11:43 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_objects_scrollbar_size(t_world *world, int len)
{
	int			h;
	float		size;
	t_cobjlist	*lst;
	t_objlist	*lst2;

	//ne pas additioner les objects d'un obj genre 42/teapot
	world->menu.nobjects = 0;
	lst = world->cobjlist;
	while (lst != NULL)
	{
		lst->cobject->id = (world->menu.nobjects)++;
		lst2 = lst->cobject->objlist;
		while (lst2 != NULL)
		{
			lst2->object->id = (world->menu.nobjects)++;
			lst2 = lst2->next;
		}
		lst = lst->next;
	}
	h = (world->menu.nobjects) * (50 + 15);
	if (h <= len)
		size = 1;
	else
		size = len / (float)h;
	return ((len - 10) * size);
}
