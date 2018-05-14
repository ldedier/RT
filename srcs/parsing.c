/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 00:34:20 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/15 01:21:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_init_parser(t_parser *parser)
{
	parser->nb_lines = 0;
	parser->tag_stack = NULL;
}

int		ft_parse_tag(char **line, char **tag, char **attribute)
{
	int		i;
	int		length;
	char	*str;
	int		ret;
	int		start;

	ret = -1;
	str = *line;

	i = 0;
	while (str[i] && str[i] != '<')
		i++;
	if (str[i])
	{
		ret = STACK;
		i++;
		if (str[i] == '/')
		{
			i++;
			ret = POP;
		}
		start = i;
		while (str[i] && (str[i] != ' ' && str[i] != '>'))
			i++;
		length = i - start;
		*tag = ft_strndup(&(str[start]), length);
		if (str[i] == ' ')
		{
			while (str[i] && str[i] != '"')
				i++;
			i++;
			start = i;
			while (str[i] && str[i] != '"')
				i++;
			length = i - start;
			*attribute = ft_strndup(&(str[start]), length);
		}
	}
	*(line) += i;
	return (ret);
}

void	ft_process_tag_stack(t_parser *parser)
{
	char *str;

	if (parser->op == POP)
	{
		str = (char *)(ft_lstpop(&(parser->tag_stack)));
		if (strcmp(parser->tag, str))
		{
			ft_dprintf(2, "line %d: expected ending tag %s instead of %s\n", 
					parser->nb_lines, str, parser->tag);
			exit(1);
		}
	}
	else if (parser->op == STACK)
		ft_lstadd(&(parser->tag_stack),
				ft_lstnew_ptr(parser->tag, sizeof(parser->tag)));
}

void	ft_process_parsing_pos(t_parser *parser, t_world *world, char *line)
{
	t_point3d	*pos;

	if (parser->parse_enum == e_parse_camera)
		pos = &(world->cam->o);
	else
		pos = &(parser->object.o);
	read_double(&line, &(pos->x));
	read_double(&line, &(pos->y));
	read_double(&line, &(pos->z));
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}


void	ft_process_parsing_rot(t_parser *parser, t_world *world, char *line)
{
	t_point3d	*pos;

	if (parser->parse_enum == e_parse_camera)
		pos = &(world->cam->rotation);
	else
		pos = &(parser->object.o);
	read_double(&line, &(pos->x));
	read_double(&line, &(pos->y));
	read_double(&line, &(pos->z));
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_process_parsing_object_start(t_parser *parser, t_world *world)
{
	parser->parse_enum = e_parse_object;
	(void)world;

}

void	ft_process_parsing_cobject_start(t_parser *parser, t_world *world)
{
	parser->parse_enum = e_parse_cobject;
	(void)world;
}


void	ft_process_parsing_object_end(t_parser *parser, t_world *world)
{
	(void)world;
	(void)parser;
}

void	ft_process_parsing_cobject_end(t_parser *parser, t_world *world)
{
	(void)world;
	(void)parser;
}

void	ft_process_parsing_light_start(t_parser *parser, t_world *world)
{
	parser->parse_enum = e_parse_cobject;
	(void)world;
}


void	ft_process_parsing_light_end(t_parser *parser, t_world *world)
{
	(void)world;
	(void)parser;
}

void	ft_process_parsing_color(t_parser *parser, char *line)
{
	t_color	*color;
	int col;

	if (parser->parse_enum == e_parse_cobject)
		color = &(parser->cobject.c);
	else if (parser->parse_enum == e_parse_object)
		color = &(parser->object.c);
//	else
//		exit(1);
	read_hex(&line, &(col));
	*color = get_color(col);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);

	(void)line;
	(void)parser;
}

void	ft_process_parsing(t_parser *parser, t_world *world, char *line)
{
	ft_process_tag_stack(parser);
	if (parser->op == STACK)
	{
		if (!ft_strcmp(parser->tag, "camera"))
			parser->parse_enum = e_parse_camera;
		else if (!ft_strcmp(parser->tag, "positionXYZ"))
			ft_process_parsing_pos(parser, world, line);
		else if (!ft_strcmp(parser->tag, "rotationXYZ"))
			ft_process_parsing_rot(parser, world, line);
		else if (!ft_strcmp(parser->tag, "object"))
		{

		}
		else if (!ft_strcmp(parser->tag, "cobject"))
		{

		}
		else if (!ft_strcmp(parser->tag, "radius"))
		{

		}
		else if (!ft_strcmp(parser->tag, "angle"))
		{

		}
		else if (!ft_strcmp(parser->tag, "light"))
		{

		}
		else if (!ft_strcmp(parser->tag, "angle"))
		{

		}
		else if (!ft_strcmp(parser->tag, "src"))
		{

		}
		else if (!ft_strcmp(parser->tag, "color"))
			ft_process_parsing_color(parser, line);
		else if (!ft_strcmp(parser->tag, "lightlist"))
		{

		}
		else if (!ft_strcmp(parser->tag, "ambientlight"))
		{

		}
		else if (strcmp(parser->tag, "scene") &&
				strcmp(parser->tag, "objlist") &&
				strcmp(parser->tag, "lightlist"))
		{
			ft_dprintf(2, "line %d: unknown tag <%s>\n", parser->nb_lines,
					parser->tag);
			exit(1);
		}
	}
	else
	{
		if (!ft_strcmp(parser->tag, "objet"))
			ft_process_parsing_object_end(parser, world);
		else if (!ft_strcmp(parser->tag, "cobject"))
			ft_process_parsing_cobject_end(parser, world);
	}
}

int	parse_line_new(char *line, t_world *world, t_parser *parser)
{
	parser->nb_lines++;
	parser->attribute = NULL;
	parser->tag = NULL;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	//printf("%s %s %d\n", tag, bis, ret);
	ft_process_parsing(parser, world, line);
	return (0);
}
