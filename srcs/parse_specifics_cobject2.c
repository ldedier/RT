/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specifics_cobject2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:14:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 22:14:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_color_n(t_parser *parser, t_world *world, char *line, int n)
{
	int *color;

	if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("adn", parser->attribute) && n == 1)
		color = &(world->cobjlist->cobject\
				->cobject_union.adn.color1);
	else if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("adn", parser->attribute) && n == 2)
		color = &(world->cobjlist->cobject\
				->cobject_union.adn.color2);
	else if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("adn", parser->attribute) && n == 3)
		color = &(world->cobjlist->cobject\
				->cobject_union.adn.color3);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a style tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_hex(&line, color);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
