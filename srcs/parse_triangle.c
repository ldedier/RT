/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 05:21:00 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 18:46:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_process_parsing_vertex_a(t_parser *parser, t_world *world,
		char *line)
{
	t_point3d	*a;

	if (parser->parse_enum == e_parse_object)
		a = &(world->cobjlist->cobject->objlist->object->object_union.
				triangle.v1);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a vertex tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(a->x));
	read_double(&line, &(a->y));
	read_double(&line, &(a->z));
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_process_parsing_vertex_b(t_parser *parser, t_world *world,
			char *line)
{
	t_point3d	*b;

	if (parser->parse_enum == e_parse_object)
		b = &(world->cobjlist->cobject->objlist->object->object_union.
				triangle.v2);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a vertex tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(b->x));
	read_double(&line, &(b->y));
	read_double(&line, &(b->z));
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_process_parsing_vertex_c(t_parser *parser, t_world *world,
		char *line)
{
	t_point3d	*c;

	if (parser->parse_enum == e_parse_object)
		c = &(world->cobjlist->cobject->objlist->object->object_union.
			triangle.v3);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a vertex tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(c->x));
	read_double(&line, &(c->y));
	read_double(&line, &(c->z));
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
