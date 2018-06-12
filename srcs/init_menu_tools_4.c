/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_tools_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 05:10:59 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 03:52:59 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_objects_scrollbar_size_2(t_world *world, t_cobjlist *lst, int *nb)
{
	t_objlist	*lst2;

	lst2 = lst->cobject->objlist;
	if (lst->cobject->descriptor &&
			(ft_strcmp(lst->cobject->descriptor, "obj") == 0 ||
			ft_strcmp(lst->cobject->descriptor, "adn") == 0 ||
			ft_strcmp(lst->cobject->descriptor, "sphere_torus") == 0))
	{
		while (lst2 != NULL)
		{
			lst2->object->id = (world->menu.nobjects)++;
			lst2 = lst2->next;
		}
	}
	else
	{
		while (lst2 != NULL)
		{
			*nb += 1;
			lst2->object->id = (world->menu.nobjects)++;
			lst2 = lst2->next;
		}
	}
}

int		ft_objects_scrollbar_size(t_world *world, int len)
{
	int			h;
	int			nb;
	float		size;
	t_cobjlist	*lst;

	nb = 0;
	world->menu.nobjects = 0;
	lst = world->cobjlist;
	while (lst != NULL)
	{
		nb++;
		lst->cobject->id = (world->menu.nobjects)++;
		ft_objects_scrollbar_size_2(world, lst, &nb);
		lst = lst->next;
	}
	h = (nb) * (50 + 15);
	if (h <= len)
		size = 1;
	else
		size = len / (float)h;
	return ((len - 10) * size);
}
