/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 02:02:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/04 02:11:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_stretch_x(t_parser *parser, t_world *world, char *line)
{
	double *stretch_x;

	if ((parser->parse_enum == e_parse_object) &&
			 (!ft_strcmp("plane", parser->attribute)))
		stretch_x = &(world->cobjlist->cobject->objlist->object->object_union.plane.texture_stretch_x);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a stretch tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_cdouble(&line, stretch_x, 0.1, 100000);
	if (*stretch_x < 0)
	{
		ft_dprintf(2, "line %d: stretch can not be negative\n",
				parser->nb_lines);
		exit(1);
	}
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_stretch_y(t_parser *parser, t_world *world, char *line)
{
	double *stretch_y;

	if ((parser->parse_enum == e_parse_object) &&
			 (!ft_strcmp("plane", parser->attribute)))
		stretch_y = &(world->cobjlist->cobject->objlist->object->object_union.plane.texture_stretch_y);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a stretch tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_cdouble(&line, stretch_y, 0.1, 100000);
	if (*stretch_y < 0)
	{
		ft_dprintf(2, "line %d: stretch can not be negative\n",
				parser->nb_lines);
		exit(1);
	}
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_trans_x(t_parser *parser, t_world *world, char *line)
{
	int *trans_x;

	if ((parser->parse_enum == e_parse_object) &&
			 (!ft_strcmp("plane", parser->attribute)))
		trans_x = &(world->cobjlist->cobject->objlist->object->object_union.plane.texture_trans_x);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a stretch tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, trans_x);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_trans_y(t_parser *parser, t_world *world, char *line)
{
	int *trans_y;

	if ((parser->parse_enum == e_parse_object) &&
			 (!ft_strcmp("plane", parser->attribute)))
		trans_y = &(world->cobjlist->cobject->objlist->object->object_union.plane.texture_trans_y);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a stretch tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, trans_y);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
