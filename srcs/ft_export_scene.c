/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:31:29 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 09:52:17 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_cobjs_2(t_cobject cobj, char *shape, int fd)
{
	dprintf(fd, "\t\t<cobject type=\"%s\">\n", shape);
	ft_print_cobject(cobj, fd);
	if (ft_strcmp(shape, "obj") == 0)
		dprintf(fd, "\t\t\t<src>%s</src>\n", cobj.filename);
	else if (ft_strcmp(shape, "adn") == 0)
		ft_print_adn(cobj, fd);
	else
		ft_print_sphere_torus(cobj, fd);
	dprintf(fd, "\t\t</cobject>\n");
}

void	ft_print_cobjs(t_cobjlist *lst, int fd)
{
	t_cobject	cobj;
	char		*shape;
	int			type;

	cobj = *(lst->cobject);
	type = -1;
	shape = ft_get_cobject_name(cobj, &type);
	if (type == 0)
	{
		dprintf(fd, "\t\t<def_cobject name=\"%s\">\n", shape);
		ft_print_cobject(cobj, fd);
		dprintf(fd, "\t\t</def_cobject>\n");
	}
	else
	{
		if (type == 1)
			ft_print_cobjs_2(cobj, shape, fd);
		else
			ft_print_cobjs_3(lst, cobj, fd);
	}
}

void	ft_print_cobjlist(t_world *world, int fd)
{
	t_cobjlist	*lst;

	lst = world->cobjlist;
	if (lst != NULL)
	{
		dprintf(fd, "\t<objlist>\n");
		while (lst != NULL)
		{
			ft_print_cobjs(lst, fd);
			lst = lst->next;
		}
		dprintf(fd, "\t</objlist>\n");
	}
}

void	ft_print_defines(t_world *world, int fd)
{
	t_cobjlist	*lst;
	t_objlist	*lst2;
	t_cobject	cobj;

	lst = world->defcobjlist;
	while (lst != NULL)
	{
		cobj = *(lst->cobject);
		dprintf(fd, "\t\t<define name=\"%s\">\n", cobj.name);
		ft_print_cobject(cobj, fd);
		lst2 = lst->cobject->objlist;
		while (lst2 != NULL)
		{
			ft_print_object(*(lst2->object), fd);
			lst2 = lst2->next;
		}
		dprintf(fd, "\t\t</define>\n");
		lst = lst->next;
	}
}

int		ft_export_scene(t_world *world)
{
	int			fd;
	char		*name;

	name = ft_get_name(".xml");
	if ((fd = open(name, O_RDWR | O_CREAT, 0644)) == -1)
		return (-1);
	dprintf(fd, "<scene>\n");
	ft_print_camera(world, fd);
	ft_print_defines(world, fd);
	ft_print_cobjlist(world, fd);
	ft_print_others(world, fd);
	dprintf(fd, "</scene>\n");
	free(name);
	close(fd);
	return (1);
}
