/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:45:17 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 09:47:38 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_filter(t_world *world, int fd)
{
	if (world->filters[0] == 1)
		dprintf(fd, "\t<filter type=\"blur\"></filter>\n");
	if (world->filters[1] == 1)
		dprintf(fd, "\t<filter type=\"sharpen\"></filter>\n");
	if (world->filters[2] == 1)
		dprintf(fd, "\t<filter type=\"sobel\"></filter>\n");
	if (world->filters[3] == 1)
		dprintf(fd, "\t<filter type=\"emboss\"></filter>\n");
	if (world->filters[4] == 1)
		dprintf(fd, "\t<filter type=\"grey\"></filter>\n");
	if (world->filters[5] == 1)
		dprintf(fd, "\t<filter type=\"motion_blur\"></filter>\n");
}

void	ft_print_light(t_world *world, int fd, char *type, int i)
{
	dprintf(fd, "\t\t<light type=\"%s\">\n", type);
	dprintf(fd, "\t\t\t<positionXYZ>");
	dprintf(fd, "%f %f %f", world->lights[i].o.x, world->lights[i].o.y,
			world->lights[i].o.z);
	dprintf(fd, "</positionXYZ>\n");
	dprintf(fd, "\t\t\t<rotationXYZ>");
	dprintf(fd, "%f %f %f", world->lights[i].v.x, world->lights[i].v.y,
			world->lights[i].v.z);
	dprintf(fd, "</rotationXYZ>\n");
	dprintf(fd, "\t\t\t<color>");
	dprintf(fd, "0x%X", world->lights[i].c.col);
	dprintf(fd, "</color>\n");
	dprintf(fd, "\t\t\t<intensity>");
	dprintf(fd, "%f", world->lights[i].intensity);
	dprintf(fd, "</intensity>\n");
	dprintf(fd, "\t\t\t<angle>");
	dprintf(fd, "%f", world->lights[i].angle);
	dprintf(fd, "</angle>\n");
	dprintf(fd, "\t\t\t<ebloui>");
	dprintf(fd, "%d", world->lights[i].ebloui);
	dprintf(fd, "</ebloui>\n");
	dprintf(fd, "\t\t</light>\n");
}

void	ft_print_lights(t_world *world, int fd)
{
	int		i;
	char	*type;

	if (world->nlights > 0)
	{
		dprintf(fd, "\t<lightlist>\n");
		i = 0;
		while (i < world->nlights)
		{
			if (world->lights[i].type == 'p')
				type = "point";
			else if (world->lights[i].type == 's')
				type = "spotlight";
			else if (world->lights[i].type == 'd')
				type = "directional";
			else
				type = "UNKNOWN";
			ft_print_light(world, fd, type, i);
			i++;
		}
		dprintf(fd, "\t</lightlist>\n");
	}
}

void	ft_print_others_2(t_world *world, int fd)
{
	if (world->shader == 1)
		dprintf(fd, "\t<shader type=\"normal\"></shader>\n");
	else if (world->shader == 2)
		dprintf(fd, "\t<shader type=\"cartoon\"></shader>\n");
	dprintf(fd, "\t<resolution>");
	dprintf(fd, "%d %d", world->canvas->win_size.x, world->canvas->win_size.y);
	dprintf(fd, "</resolution>\n");
}

void	ft_print_others(t_world *world, int fd)
{
	ft_print_lights(world, fd);
	dprintf(fd, "\t<ambientlight>\n");
	dprintf(fd, "\t\t<intensity>");
	dprintf(fd, "%f", world->ambient.in);
	dprintf(fd, "</intensity>\n");
	dprintf(fd, "\t\t<color>");
	dprintf(fd, "0x%X", world->ambient.color.col);
	dprintf(fd, "</color>\n");
	dprintf(fd, "\t</ambientlight>\n");
	dprintf(fd, "\t<fog>\n");
	dprintf(fd, "\t\t<intensity>");
	dprintf(fd, "%f", world->fog.in);
	dprintf(fd, "</intensity>\n");
	dprintf(fd, "\t\t<color>");
	dprintf(fd, "0x%X", world->fog.color.col);
	dprintf(fd, "</color>\n");
	dprintf(fd, "\t</fog>\n");
	ft_print_filter(world, fd);
	dprintf(fd, "\t<antialiasing>");
	dprintf(fd, "%d", world->aa_sq_size);
	dprintf(fd, "</antialiasing>\n");
	ft_print_others_2(world, fd);
}
