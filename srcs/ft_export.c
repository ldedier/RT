/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:03:58 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/09 07:02:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_image		ft_populate_image(t_world *world)
{
	return ft_new_image(world->canvas->win_size.x,
			world->canvas->win_size.y, world->canvas->surface->pixels);
}

int			ft_export(t_image image, char *extension)
{
	char *name;

	name = ft_get_name(extension);
	if (!ft_strcmp(extension, ".ppm"))
		return (ft_export_ppm(name, image));
	if (!ft_strcmp(extension, ".bmp"))
		return (ft_export_bmp(name, image));
	else
	{
		ft_printf("extension not supported\n");
		return (1);
	}
}

int			ft_export_rt(t_world *world, char * extension)
{
	t_image	image;

	image = ft_populate_image(world);
	return ft_export(image, extension);
}
