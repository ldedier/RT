/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specifics_cobject.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:11:33 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/31 00:45:51 by ldedier          ###   ########.fr       */
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
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
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
	read_cdouble(&line, spheres_radius, 0.01, 100000000);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_length(t_parser *parser, t_world *world, char *line)
{
	int *length;

	if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("adn", parser->attribute))
		length = &(world->cobjlist->cobject\
				->cobject_union.adn.length);
	else
	{
		ft_dprintf(2, "line %d: current object can not have length tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, length);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}


void	populate_style_through_string(t_parser *parser, char *str,
		t_style *style)
{
	if (!ft_strcmp(str, "irregular"))
		*style = e_irregular;
	else if (!ft_strcmp(str, "plain"))
		*style = e_plain;
	else
	{
		ft_dprintf(2, "line %d: %s style does not exist\n",
				parser->nb_lines);
		exit(1);
	}
}

void	ft_parse_style(t_parser *parser, t_world *world, char *line)
{
	char *str;
	t_style *style;

	if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("adn", parser->attribute))
		style = &(world->cobjlist->cobject\
				->cobject_union.adn.style);
	else
	{
		ft_dprintf(2, "line %d: current object can not have a style tag\n",
				parser->nb_lines);
		exit(1);
	}
	str = ft_get_between_tag(&line);
	populate_style_through_string(parser, str, style);
	free(str);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);

}

void	ft_parse_color_n(t_parser *parser, t_world *world, char *line, int n)
{
	int *color;

	if (parser->parse_enum == e_parse_cobject && parser->attribute &&
			!ft_strcmp("adn", parser->attribute)&& n == 1)
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
