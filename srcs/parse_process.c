/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 00:50:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_process_parsing_stack(t_parser *parser, t_world *world,
		char *line)
{
	if (!ft_strcmp(parser->tag, "positionXYZ"))
		ft_process_parsing_pos(parser, world, line);
	else if (!ft_strcmp(parser->tag, "rotationXYZ"))
		ft_process_parsing_rot(parser, world, line);
	else if (!ft_strcmp(parser->tag, "scaleXYZ"))
		ft_process_parsing_scale(parser, world, line);
	else if (!ft_strcmp(parser->tag, "camera"))
		parser->parse_enum = e_parse_camera;
	else if (!ft_strcmp(parser->tag, "object"))
		ft_process_parsing_object_start(parser, world);
	else if (!ft_strcmp(parser->tag, "cobject"))
		ft_process_parsing_cobject_start(parser, world);
	else if (!ft_strcmp(parser->tag, "define"))
		ft_process_parsing_define_start(parser, world);
	else if (!ft_strcmp(parser->tag, "def_cobject"))
		ft_process_parsing_def_cobject_start(parser, world);
	else if (!ft_strcmp(parser->tag, "ambientlight"))
		parser->parse_enum = e_parse_ambient;
	else if (!ft_strcmp(parser->tag, "fog"))
		parser->parse_enum = e_parse_fog;
	else if (!ft_strcmp(parser->tag, "light"))
		ft_process_parsing_light_start(parser, world);
	else
		ft_process_parsing_stack_2(parser, world, line);
}

void		ft_parse_pop_others(t_parser *parser, t_world *world)
{
	if (parser->parse_enum == e_parse_cobject)
	{
		if (parser->attribute != NULL &&
				world->cobjlist->cobject->name == NULL)
			ft_process_automatic(parser, world);
		else if (world->cobjlist->cobject->name != NULL &&
				world->cobjlist->cobject->defining)
			ft_process_switch_list_cobject(&(world->cobjlist),
					&(world->defcobjlist));
	}
	parser->parse_enum = e_parse_scene;
}

void		ft_process_tag_pre_pop(t_parser *parser, t_world *world)
{
	if (!ft_strcmp(parser->tag, "cut"))
		parser->parse_enum = e_parse_object;
	else if (!ft_strcmp(parser->tag, "object"))
	{
		ft_give_object_name(world->cobjlist->cobject->objlist->object,
			parser->attribute);
		parser->parse_enum = e_parse_cobject;
	}
	else if (!ft_strncmp(parser->tag, "mod_", 4))
	{
		parser->parse_enum = e_parse_object;
		ft_transfer_mod_parser(parser, world);
	}
	else
		ft_parse_pop_others(parser, world);
}

void		ft_process_parsing(t_parser *parser, t_world *world, char *line)
{
	if (parser->op == STACK)
	{
		ft_process_tag_stack_stack(parser);
		ft_process_parsing_stack(parser, world, line);
	}
	else if (parser->op == POP)
	{
		ft_process_tag_pre_pop(parser, world);
		ft_process_tag_pop(parser);
	}
	else
	{
		ft_dprintf(2, "line %d: not xml format\n", parser->nb_lines);
		exit(1);
	}
}

int			parse_line_new(char *line, t_world *world, t_parser *parser)
{
	parser->nb_lines++;
	parser->op = ft_parse_tag(&line, parser);
	ft_process_parsing(parser, world, line);
	return (0);
}
