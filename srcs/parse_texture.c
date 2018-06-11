/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 05:44:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/09 06:14:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_free_bmp_parser(t_bmp_parser *parser)
{
	free(parser->pixels);
	parser->pixels = NULL;
	parser->width = -1;
	parser->height = -1;
	parser->bitmap_index = -1;
	parser->bpp = -1;
}

void	ft_parse_texture(t_parser *parser, t_world *world, char *line)
{
	char *tmp;

	if ((parser->parse_enum == e_parse_object) &&
			((!ft_strcmp("sphere", parser->attribute)) ||
			 (!ft_strcmp("cylinder", parser->attribute)) ||
			 (!ft_strcmp("cone", parser->attribute)) ||
			 (!ft_strcmp("plane", parser->attribute))))
	{
		tmp = ft_get_between_tag(&line);
		if (world->cobjlist->cobject->objlist->object->parser.pixels != NULL)
			ft_free_bmp_parser(&(
				world->cobjlist->cobject->objlist->object->parser));
		world->cobjlist->cobject->objlist->object->parser = ft_parse_bmp(tmp);
		free(tmp);
	}
	else
	{
		ft_dprintf(
			2, "line %d: current object can not have a texture tag\n",
				parser->nb_lines);
		exit(1);
	}
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_normal_texture(t_parser *parser, t_world *world, char *line)
{
	char *tmp;

	if ((parser->parse_enum == e_parse_object) &&
			((!ft_strcmp("sphere", parser->attribute))))
	{
		tmp = ft_get_between_tag(&line);
		if (world->cobjlist->cobject->objlist->object->parser_normal.pixels != NULL)
			ft_free_bmp_parser(&(world->cobjlist->cobject->objlist->object->parser_normal));

		world->cobjlist->cobject->objlist->object->parser_normal = ft_parse_bmp(tmp);
		free(tmp);
	}
	else
	{
		ft_dprintf(
			2, "line %d: current object can not have a normal texture tag\n",
				parser->nb_lines);
		exit(1);
	}
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
