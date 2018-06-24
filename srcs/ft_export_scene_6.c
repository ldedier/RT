/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:44:53 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 09:49:06 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_sphere_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.sphere.radius);
}

void	ft_print_plane_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<texture_stretch_x>%f</texture_stretch_x>\n",
			obj.object_union.plane.texture_stretch_x);
	dprintf(fd, "\t\t\t\t<texture_stretch_y>%f</texture_stretch_y>\n",
			obj.object_union.plane.texture_stretch_y);
	dprintf(fd, "\t\t\t\t<texture_trans_x>%d</texture_trans_x>\n",
			obj.object_union.plane.texture_trans_x);
	dprintf(fd, "\t\t\t\t<texture_trans_y>%d</texture_trans_y>\n",
			obj.object_union.plane.texture_trans_y);
}

void	ft_print_cone_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<angle>%f</angle>\n",
			obj.object_union.cone.angle);
}

void	ft_print_cylinder_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.cylinder.radius);
}

void	ft_print_ellipsoid_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.ellipsoid.radius);
	dprintf(fd, "\t\t\t\t<ellipsoidABC>%f %f %f</ellipsoidABC>\n",
			obj.object_union.ellipsoid.abc.x, obj.object_union.ellipsoid.abc.y,
			obj.object_union.ellipsoid.abc.z);
}
