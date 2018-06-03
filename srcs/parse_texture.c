/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 05:44:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/03 07:10:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		world->cobjlist->cobject->objlist->object->parser = ft_parse_bmp(tmp);
		free(tmp);
	}
	else
	{
		ft_dprintf(2, "line %d: current object can not have a texture tag\n",
				parser->nb_lines);
		exit(1);
	}
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}
