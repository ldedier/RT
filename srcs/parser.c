/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 05:06:45 by lcavalle          #+#    #+#             */
/*   Updated: 2018/04/24 15:05:48 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			read_hex(char **line, int *to)
{
	int scss;

	scss = 1;
	*to = ft_patoi_hex(line, &scss);
	return (scss);
}

int			read_double(char **line, double *to)
{
	int scss;

	scss = 1;
	*to = ft_patof(line, &scss);
	return (scss);
}

static int	read_param(char *line, t_world *world, int line_count)
{
	if (line[0] == '#')
		;
	else if (line[0] == 'a' && parse_ambient(line + 2, &(world->ambient)))
		;
	else if (line[0] == 'f' && parse_fog(line + 2, &(world->fog)))
		;
	else
		return (line_count);
	return (0);
}

static int	parse_line(char *line, t_world *world)
{
	t_object	*obj;
	static int	line_count = 0;

	line_count++;
	obj = ft_memalloc(sizeof(t_object));
	if ((line[0] == 's' && parse_sphere(line + 2, obj)) ||
			(line[0] == 'p' && parse_plane(line + 2, obj)) ||
			(line[0] == 'y' && parse_cylinder(line + 2, obj)) ||
			(line[0] == 'c' && parse_cone(line + 2, obj)))
		add_obj(&(world->objlist), obj);
	else if (line[0] == 'l')
	{
		if (world->nlights >= MAX_LIGHTS ||
				!parse_light(line + 2, (world->lights + world->nlights)))
		{
			if (world->nlights >= MAX_LIGHTS)
				ft_putstr("Too many lights! => ");
			return (line_count);
		}
		world->nlights++;
	}
	else if (read_param(line, world, line_count))
		return (line_count);
	return (0);
}

int			read_world(t_world *world, char *file)
{
	char	*line;
	int		fd;
	int		gnl_ret;
	int		pl_ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	line = NULL;
	while ((gnl_ret = get_next_line(fd, &line)) == 1)
	{
		if ((pl_ret = parse_line(line, world)))
		{
			free(line);
			close(fd);
			return (pl_ret);
		}
	}
	close(fd);
	if (gnl_ret == -1)
		return (-2);
	free(line);
	return (0);
}
