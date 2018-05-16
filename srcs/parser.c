/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 22:44:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/16 02:29:31 by ldedier          ###   ########.fr       */
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

/*
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
   {
   add_obj(&(world->objlist), obj);
   world->selected_object = obj;
   }
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
   */

t_cobject		*ft_new_cobject(void)
{
	t_cobject *cobject;

	if (!(cobject = ft_memalloc(sizeof(t_cobject))))
		return (NULL);
	cobject->objlist = NULL;
	cobject->o = ft_new_vec3(0, 0, 0);
	cobject->r = ft_new_vec3(0, 0, 0);
	cobject->s = ft_new_vec3(1, 1, 1);
	cobject->c = get_color(0xFFFFFF);
	cobject->transp = 0;
	cobject->refract = 0;
	cobject->reflect = 0;
	cobject->shine = 0;
	cobject->objlist = NULL;
	return (cobject);
}

void	ft_add_obj_to_cobj(t_cobject *cobject, t_object *object)
{
	add_obj(&(cobject->objlist), object);
}

t_object	*ft_new_object(t_cobject cobject)
{
	t_object *object;

	if (!(object = ft_memalloc(sizeof(t_object))))
		return (NULL);
	object->o = ft_new_vec3(0, 0, 0);
	object->r = ft_new_vec3(0, 0, 0);
	object->s = ft_new_vec3(1, 1, 1);
	object->c = get_color(cobject.c.col);
	object->transp = cobject.transp;
	object->refract = cobject.refract;
	object->reflect = cobject.reflect;
	object->shine = cobject.shine;
	return (object);
}

void	ft_init_light(t_light *light)
{
	light->o = ft_new_vec3(0, 0, 0);
	light->v = ft_new_vec3(0, 1, 0);
	light->c = get_color(0xFFFFFF);
	light->intensity = 1;
	light->angle = M_PI / 4;
}

void		ft_check_parser(t_parser parser)
{
	if (!parser.got_scene)
	{
		ft_dprintf(2, "every config file must begin with a <scene> tag\n");
		exit(1);
	}
}

void	ft_free_parser(t_parser *parser)
{
	int		i;
	t_list	**ptr;
	t_list	*tmp;

	i = 0;
	if (parser->attribute != NULL)
		free(parser->attribute);
	if (parser->tag != NULL)
		free(parser->tag);
	ptr = &(parser->tag_stack);
	while (*ptr)
	{
		tmp = *ptr;
		free(tmp->content);
		free(tmp);
		*ptr = (*ptr)->next;
		i++;
	}
	if (i)
	{
		ft_dprintf(2, "some opening tags are not closed\n");
		exit(1);
	}
	ft_check_parser(*parser);
}

int				read_world(t_world *world, char *file)
{
	char		*line;
	int			fd;
	int			ret;
	t_parser	parser;

	ft_init_parser(&parser);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	line = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if ((ret = parse_line_new(line, world, &parser)))
		{
			free(line);
			close(fd);
			return (ret);
		}
		free(line);
	}
	ft_free_parser(&parser);
	close(fd);
	if (ret == -1)
		return (-2);
	free(line);
	return (0);
}
