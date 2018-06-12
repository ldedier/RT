/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:42:53 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 09:48:32 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_hyperboloid_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.hyperboloid.radius);
}

void	ft_print_paraboloid_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}

void	ft_print_triangle_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<vertexA>%f %f %f</vertexA>\n",
			obj.object_union.triangle.v1.x, obj.object_union.triangle.v1.y,
			obj.object_union.triangle.v1.z);
	dprintf(fd, "\t\t\t\t<vertexB>%f %f %f</vertexB>\n",
			obj.object_union.triangle.v2.x, obj.object_union.triangle.v2.y,
			obj.object_union.triangle.v2.z);
	dprintf(fd, "\t\t\t\t<vertexC>%f %f %f</vertexC>\n",
			obj.object_union.triangle.v3.x, obj.object_union.triangle.v3.y,
			obj.object_union.triangle.v3.z);
}

void	ft_print_cut(t_cut cut, int fd)
{
	dprintf(fd, "\t\t\t\t\t<cutXYZ>");
	dprintf(fd, "%f %f %f", cut.cut_xyz.x, cut.cut_xyz.y, cut.cut_xyz.z);
	dprintf(fd, "</cutXYZ>\n");
	if (cut.inequality == bigger_than)
		dprintf(fd, "\t\t\t\t\t<inequality>more than</inequality>\n");
	else if (cut.inequality == less_than)
		dprintf(fd, "\t\t\t\t\t<inequality>less than</inequality>\n");
	else if (cut.inequality == less_than_or_equal)
		dprintf(fd, "\t\t\t\t\t<inequality>less than or equal</inequality>\n");
	else if (cut.inequality == bigger_than_or_equal)
		dprintf(fd, "\t\t\t\t\t<inequality>more than or equal</inequality>\n");
	else
		dprintf(fd, "\t\t\t\t\t<inequality>UNKNOWN</inequality>\n");
	dprintf(fd, "\t\t\t\t\t<value>");
	dprintf(fd, "%f", cut.value);
	dprintf(fd, "</value>\n");
}

void	ft_print_object_cuts(t_object obj, int fd)
{
	t_list	*lst;
	t_cut	*cut;
	char	*type;

	lst = obj.cuts;
	while (lst != NULL)
	{
		cut = (t_cut *)(lst->content);
		if (cut->relative == 1 && cut->circular == 1)
			type = "circular";
		else if (cut->relative == 1)
			type = "relative";
		else if (cut->relative == 0)
			type = "absolute";
		else
			type = "UNKNOWN";
		dprintf(fd, "\t\t\t\t<cut type=\"%s\">\n", type);
		ft_print_cut(*cut, fd);
		dprintf(fd, "\t\t\t\t</cut>\n");
		lst = lst->next;
	}
}
