/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:41:51 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 09:50:38 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_cobject(t_cobject cobj, int fd)
{
	dprintf(fd, "\t\t\t<positionXYZ>");
	dprintf(fd, "%f %f %f", cobj.o.x, cobj.o.y, cobj.o.z);
	dprintf(fd, "</positionXYZ>\n");
	dprintf(fd, "\t\t\t<rotationXYZ>");
	dprintf(fd, "%f %f %f", cobj.r.x, cobj.r.y, cobj.r.z);
	dprintf(fd, "</rotationXYZ>\n");
	dprintf(fd, "\t\t\t<scaleXYZ>");
	dprintf(fd, "%f %f %f", cobj.s.x, cobj.s.y, cobj.s.z);
	dprintf(fd, "</scaleXYZ>\n");
	dprintf(fd, "\t\t\t<color>");
	dprintf(fd, "0x%X", cobj.c.col);
	dprintf(fd, "</color>\n");
	dprintf(fd, "\t\t\t<shine>%f</shine>\n", cobj.shine);
	dprintf(fd, "\t\t\t<reflection>%f</reflection>\n", cobj.reflect);
	dprintf(fd, "\t\t\t<refraction>%f</refraction>\n", cobj.refract);
	dprintf(fd, "\t\t\t<transparency>%f</transparency>\n", cobj.transp);
	ft_print_cobj_perturbation(cobj, fd);
}

char	*ft_get_cobject_name(t_cobject cobj, int *type)
{
	if (cobj.name != NULL)
	{
		*type = 0;
		return (cobj.name);
	}
	if (cobj.descriptor != NULL)
	{
		*type = 1;
		return (cobj.descriptor);
	}
	*type = 2;
	return (NULL);
}

void	ft_print_adn(t_cobject cobj, int fd)
{
	dprintf(fd, "\t\t\t<length>%d</length>\n", cobj.cobject_union.adn.length);
	dprintf(fd, "\t\t\t<radius>%f</radius>\n", cobj.cobject_union.adn.radius);
	dprintf(fd, "\t\t\t<color1>0x%X</color1>\n", cobj.cobject_union.adn.color1);
	dprintf(fd, "\t\t\t<color2>0x%X</color2>\n", cobj.cobject_union.adn.color2);
	dprintf(fd, "\t\t\t<color3>0x%X</color3>\n", cobj.cobject_union.adn.color3);
	if (cobj.cobject_union.adn.style == e_plain)
		dprintf(fd, "\t\t\t<style>plain</style>\n");
	else
		dprintf(fd, "\t\t\t<style>irregular</style>\n");
}

void	ft_print_sphere_torus(t_cobject cobj, int fd)
{
	dprintf(fd, "\t\t\t<nb_spheres>%d</nb_spheres>\n",
			cobj.cobject_union.sphere_torus.nb_spheres);
	dprintf(fd, "\t\t\t<radius>%f</radius>\n",
			cobj.cobject_union.sphere_torus.radius);
	dprintf(fd, "\t\t\t<spheres_radius>%f</spheres_radius>\n",
			cobj.cobject_union.sphere_torus.spheres_radius);
}

void	ft_print_cobjs_3(t_cobjlist *lst, t_cobject cobj, int fd)
{
	t_objlist	*lst2;

	dprintf(fd, "\t\t<cobject>\n");
	ft_print_cobject(cobj, fd);
	lst2 = lst->cobject->objlist;
	while (lst2 != NULL)
	{
		ft_print_object(*(lst2->object), fd);
		lst2 = lst2->next;
	}
	dprintf(fd, "\t\t</cobject>\n");
}
