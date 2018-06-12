/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 20:09:40 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 19:02:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_process_parsing_cut_attributes(t_parser *parser, t_cut *cut)
{
	if (!ft_strcmp(parser->attribute, "relative"))
		;
	else if (!ft_strcmp(parser->attribute, "absolute"))
		cut->relative = 0;
	else if (!ft_strcmp(parser->attribute, "color"))
		cut->color = 1;
	else if (!ft_strcmp(parser->attribute, "circular"))
		cut->circular = 1;
	else
	{
		ft_dprintf(2, "line %d: attribute %s unknown\n", parser->nb_lines,
				parser->attribute);
		exit(1);
	}
}

void	ft_process_parsing_cut_xyz(t_parser *parser, t_world *world,
		char *line)
{
	t_point3d	*cut_xyz;

	if (parser->parse_enum == e_parse_cut)
		cut_xyz = &(((t_cut *)(world->cobjlist->cobject->objlist->object->cuts
						->content))->cut_xyz);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a cutXYZ tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(cut_xyz->x));
	read_double(&line, &(cut_xyz->y));
	read_double(&line, &(cut_xyz->z));
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_attribute_inequality_func(int (**func)(double, double), char *desc,
		t_parser *parser)
{
	if (!ft_strcmp(desc, "less than"))
		*func = less_than;
	else if (!ft_strcmp(desc, "more than"))
		*func = bigger_than;
	else if (!ft_strcmp(desc, "less than or equal"))
		*func = less_than_or_equal;
	else if (!ft_strcmp(desc, "more than or equal"))
		*func = bigger_than_or_equal;
	else if (!ft_strcmp(desc, "equal"))
		*func = equal;
	else
	{
		ft_dprintf(2, "line %d: %s function is not valid\n",
				parser->nb_lines, desc);
		exit(1);
	}
}

void	ft_process_parsing_inequality(t_parser *parser, t_world *world,
		char *line)
{
	int		(**func)(double, double);
	char	*tmp;

	if (parser->parse_enum == e_parse_cut)
		func = &(((t_cut *)(world->cobjlist->cobject->objlist->object->cuts->
						content))->inequality);
	else if (parser->parse_enum == e_parse_mod)
		func = &(parser->mod.inequality);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a inequality tag\n",
				parser->nb_lines);
		exit(1);
	}
	tmp = ft_get_between_tag(&line);
	ft_attribute_inequality_func(func, tmp, parser);
	free(tmp);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_process_parsing_value(t_parser *parser, t_world *world,
		char *line)
{
	double	*value;

	if (parser->parse_enum == e_parse_cut)
		value = &(((t_cut *)(world->cobjlist->cobject->objlist->object->
						cuts->content))->value);
	else if (parser->parse_enum == e_parse_mod)
		value = &(parser->mod.value);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a value tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, value);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
