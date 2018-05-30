/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specifics_cobject.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:11:33 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/29 17:50:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_nb_spheres(t_parser *parser, t_world *world, char *line)
{
	int *nb_spheres;

	if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("sphere_torus", parser->attribute))
		nb_spheres = &(world->cobjlist->cobject\
				->cobject_union.sphere_torus.nb_spheres);
	else
	{
		ft_dprintf(2, "line %d: current object can not have nb_spheres tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, nb_spheres);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_spheres_radius(t_parser *parser, t_world *world, char *line)
{
	double *spheres_radius;

	if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("sphere_torus", parser->attribute))
		spheres_radius = &(world->cobjlist->cobject\
				->cobject_union.sphere_torus.spheres_radius);
	else
	{
		ft_dprintf(
				2, "line %d: current object can not have spheres_radius tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, spheres_radius);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_length(t_parser *parser, t_world *world, char *line)
{
	int *length;

	if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("adn", parser->attribute))
		length = &(world->cobjlist->cobject\
				->cobject_union.sphere_torus.nb_spheres);
	else
	{
		ft_dprintf(2, "line %d: current object can not have length tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, length);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}