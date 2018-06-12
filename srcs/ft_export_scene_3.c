/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:42:45 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 10:38:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_get_object_name_2(t_object obj)
{
	if (obj.intersect_func == intersect_paraboloid)
		return ("paraboloid");
	if (obj.intersect_func == intersect_triangle)
		return ("triangle");
	return ("UNKNOWN");
}

char	*ft_get_object_name(t_object obj)
{
	if (obj.intersect_func == intersect_sphere)
		return ("sphere");
	if (obj.intersect_func == intersect_plane)
		return ("plane");
	if (obj.intersect_func == intersect_cone)
		return ("cone");
	if (obj.intersect_func == intersect_cylinder)
		return ("cylinder");
	if (obj.intersect_func == intersect_ellipsoid)
		return ("ellipsoid");
	if (obj.intersect_func == intersect_torus)
		return ("torus");
	if (obj.intersect_func == intersect_goursat)
		return ("goursat");
	if (obj.intersect_func == intersect_lemniscate)
		return ("lemniscate");
	if (obj.intersect_func == intersect_roman)
		return ("roman");
	if (obj.intersect_func == intersect_piriform)
		return ("piriform");
	if (obj.intersect_func == intersect_mobius)
		return ("mobius");
	if (obj.intersect_func == intersect_hyperboloid)
		return ("hyperboloid");
	return (ft_get_object_name_2(obj));
}

void	ft_print_obj_perturbation(t_object obj, int fd)
{
	char	*type;

	if (obj.pert == e_none)
		type = "none";
	else if (obj.pert == e_waves)
		type = "waves";
	else if (obj.pert == e_ripple)
		type = "ripple";
	else if (obj.pert == e_noise)
		type = "noise";
	else if (obj.pert == e_chess)
		type = "chess";
	else if (obj.pert == e_perlin)
		type = "perlin";
	else if (obj.pert == e_marble)
		type = "marble";
	else
		type = "UNKNOWN";
	dprintf(fd, "\t\t\t\t<perturbation name=\"%s\"></perturbation>\n", type);
}

void	ft_print_object(t_object obj, int fd)
{
	char	*shape;

	shape = ft_get_object_name(obj);
	dprintf(fd, "\t\t\t<object name=\"%s\">\n\t\t\t\t<positionXYZ>", shape);
	dprintf(fd, "%f %f %f</positionXYZ>\n", obj.o.x, obj.o.y, obj.o.z);
	dprintf(fd, "\t\t\t\t<rotationXYZ>");
	dprintf(fd, "%f %f %f</rotationXYZ>\n", obj.r.x, obj.r.y, obj.r.z);
	dprintf(fd, "\t\t\t\t<scaleXYZ>");
	dprintf(fd, "%f %f %f</scaleXYZ>\n", obj.s.x, obj.s.y, obj.s.z);
	dprintf(fd, "\t\t\t\t<color>0x%X</color>\n", obj.c.col);
	dprintf(fd, "\t\t\t\t<shine>%f</shine>\n", obj.shine);
	dprintf(fd, "\t\t\t\t<reflection>%f</reflection>\n", obj.reflect);
	dprintf(fd, "\t\t\t\t<refraction>%f</refraction>\n", obj.refract);
	dprintf(fd, "\t\t\t\t<transparency>%f</transparency>\n", obj.transp);
	if (obj.negative == 1)
		dprintf(fd, "\t\t\t\t<negative>%d</negative>\n", obj.negative);
	obj.print_caracteristics(obj, fd);
	ft_print_obj_perturbation(obj, fd);
	ft_print_object_cuts(obj, fd);
	if (obj.parser.width > -1)
		dprintf(fd, "\t\t\t\t<texture>%s</texture>\n", obj.parser.filename);
	if (obj.parser_normal.width > -1)
		dprintf(fd, "\t\t\t\t<normal_texture>%s</normal_texture>\n",
				obj.parser_normal.filename);
	dprintf(fd, "\t\t\t</object>\n");
}

void	ft_print_cobj_perturbation(t_cobject cobj, int fd)
{
	char	*type;

	if (cobj.pert == e_none)
		type = "none";
	else if (cobj.pert == e_waves)
		type = "waves";
	else if (cobj.pert == e_ripple)
		type = "ripple";
	else if (cobj.pert == e_noise)
		type = "noise";
	else if (cobj.pert == e_chess)
		type = "chess";
	else if (cobj.pert == e_perlin)
		type = "perlin";
	else if (cobj.pert == e_marble)
		type = "marble";
	else
		type = "UNKNOWN";
	dprintf(fd, "\t\t\t<perturbation name=\"%s\"></perturbation>\n", type);
}
