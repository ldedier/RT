/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:50:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 00:37:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_process_parsing_light_start(t_parser *parser, t_world *world)
{
	parser->parse_enum = e_parse_light;
	if (world->nlights++ > MAX_LIGHTS)
	{
		ft_dprintf(2, "line %d: too much lights in the scene (max = %d)\n",
				parser->nb_lines, MAX_LIGHTS);
		exit(1);
	}
	ft_init_light(&(world->lights[world->nlights - 1]));
	if (parser->attribute == NULL)
	{
		ft_dprintf(2, "line %d: light should have a type (e.g. diffuse)");
		exit(1);
	}
	if (!ft_strcmp(parser->attribute, "point"))
		world->lights[world->nlights - 1].type = 'p';
	else if (!ft_strcmp(parser->attribute, "spotlight"))
		world->lights[world->nlights - 1].type = 's';
	else if (!ft_strcmp(parser->attribute, "directional"))
		world->lights[world->nlights - 1].type = 'd';
	else
	{
		ft_dprintf(2, "line %d: %s: unknown type of light\n", parser->nb_lines,
				parser->attribute);
		exit(1);
	}
}

void	ft_process_parsing_mod_start(t_parser *parser, t_world *world)
{
	(void)world;
	if (parser->parse_enum != e_parse_object)
	{
		ft_dprintf(2, "line %d: can only declare mod inside objects\n",
				parser->nb_lines);
		exit(1);
	}
	parser->parse_enum = e_parse_mod;
	parser->mod = ft_new_mod();
}

void	ft_process_parsing_cut_start(t_parser *parser, t_world *world)
{
	t_cut *cut;

	if (parser->parse_enum != e_parse_object)
	{
		ft_dprintf(2, "line %d: can only declare cut inside objects\n",
				parser->nb_lines);
		exit(1);
	}
	parser->parse_enum = e_parse_cut;
	if (!(cut = ft_new_cut()))
		ft_error("could not malloc object");
	if (parser->attribute == NULL)
	{
		ft_dprintf(2, "line %d: cut must have a specified type\n");
		exit(1);
	}
	ft_process_parsing_cut_attributes(parser, cut);
	ft_lstadd(&(world->cobjlist->cobject->objlist->object->cuts),
		ft_lstnew_ptr(cut, sizeof(t_cut)));
}
