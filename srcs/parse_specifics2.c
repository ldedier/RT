/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specifics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:31:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/07 22:56:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_negative(t_parser *parser, t_world *world, char *line)
{
	int		*neg;
	char	*name;

	name = parser->attribute;
	neg = NULL;
	if (parser->parse_enum == e_parse_object)
		neg = &(world->cobjlist->cobject->objlist->object->negative);
	else if (parser->parse_enum == e_parse_cobject)
		neg = &(world->cobjlist->cobject->negative);
	if (!neg || (ft_strcmp(name, "sphere") && ft_strcmp(name, "plane") &&
				ft_strcmp(name, "hyperboloid") && ft_strcmp(name, "cylinder") &&
				ft_strcmp(name, "cone") && ft_strcmp(name, "ellipsoid") &&
				ft_strcmp(name, "paraboloid") && ft_strcmp(name, "torus")))
	{
		ft_dprintf(2, "line %d: current object can not be negative\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, neg);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_ellipsoid_abc(t_parser *parser, t_world *world, char *line)
{
	t_point3d	*abc;

	if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("ellipsoid", parser->attribute))
		abc = &(world->cobjlist->cobject->objlist->object\
				->object_union.ellipsoid.abc);
	else
	{
		ft_dprintf(2, "line %d: current object can not have ellipsoidABC tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(abc->x));
	read_double(&line, &(abc->y));
	read_double(&line, &(abc->z));
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_big_radius(t_parser *parser, t_world *world, char *line)
{
	double	*big_rad;

	if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("torus", parser->attribute))
		big_rad = &(world->cobjlist->cobject->objlist->object\
				->object_union.torus.big_rad);
	else
	{
		ft_dprintf(2, "line %d: current object can not have big_radius tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, big_rad);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_small_radius(t_parser *parser, t_world *world, char *line)
{
	double	*small_rad;

	if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("torus", parser->attribute))
		small_rad = &(world->cobjlist->cobject->objlist->object\
				->object_union.torus.small_rad);
	else
	{
		ft_dprintf(2, "line %d: current object can not have small_radius tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, small_rad);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_goursat_ab(t_parser *parser, t_world *world, char *line)
{
	double *a;
	double *b;

	if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("goursat", parser->attribute))
	{
		a = &(world->cobjlist->cobject->objlist->object\
				->object_union.goursat.a);
		b = &(world->cobjlist->cobject->objlist->object\
				->object_union.goursat.b);
	}
	else
	{
		ft_dprintf(2, "line %d: current object can not have goursatAB tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, a);
	read_double(&line, b);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
