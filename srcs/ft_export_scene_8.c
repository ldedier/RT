/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene_8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:46:02 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 09:46:35 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_camera(t_world *world, int fd)
{
	dprintf(fd, "\t<camera>\n");
	dprintf(fd, "\t\t<positionXYZ>");
	dprintf(fd, "%f %f %f", world->cam->o.x, world->cam->o.y, world->cam->o.z);
	dprintf(fd, "</positionXYZ>\n");
	dprintf(fd, "\t\t<rotationXYZ>");
	dprintf(fd, "%f %f %f", world->cam->rotation.x, world->cam->rotation.y,
			world->cam->rotation.z);
	dprintf(fd, "</rotationXYZ>\n");
	dprintf(fd, "\t</camera>\n");
}
