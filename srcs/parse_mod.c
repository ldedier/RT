/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:51:20 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 19:01:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_get_color(t_parser *parser, char *str)
{
	if (!ft_strcmp("red", str))
		return (0xff0000);
	else if (!ft_strcmp("blue", str))
		return (0x0000ff);
	else if (!ft_strcmp("green", str))
		return (0x00ff00);
	else
	{
		ft_dprintf(2, "line %d: color \"%s\" illegal\n", parser->nb_lines, str);
		exit(1);
	}
}

void	ft_process_parsing_cut_color(t_parser *parser, t_world *world,
		char *line)
{
	int		*color;
	char	*tmp;

	if (parser->parse_enum == e_parse_cut)
		color = &(((t_cut *)(world->cobjlist->cobject->objlist->object->cuts
						->content))->color);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a cut_color tag\n",
				parser->nb_lines);
		exit(1);
	}
	tmp = ft_get_between_tag(&line);
	*color = ft_get_color(parser, tmp);
	free(tmp);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_process_parsing_mod_color(t_parser *parser, t_world *world,
		char *line)
{
	int		*color;
	char	*tmp;

	(void)world;
	if (parser->parse_enum == e_parse_mod)
		color = &(parser->mod.color);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a mod_color tag\n",
				parser->nb_lines);
		exit(1);
	}
	tmp = ft_get_between_tag(&line);
	*color = ft_get_color(parser, tmp);
	free(tmp);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_process_parsing_mod_value(t_parser *parser, t_world *world,
		char *line)
{
	double	*value;

	(void)world;
	if (parser->parse_enum == e_parse_mod)
		value = &(parser->mod.mod_value);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a mod value tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, value);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
