/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specifics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:31:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 00:19:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_angle(t_parser *parser, t_world *world, char *line)
{
	double *angle;

	if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("cone", parser->attribute))
		angle = &(world->cobjlist->cobject->objlist->object\
				->object_union.cone.angle);
	else if (parser->parse_enum == e_parse_light)
		angle = &(world->lights[world->nlights - 1].angle);
	else
	{
		ft_dprintf(2, "line %d: current object can not have angle tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, angle);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

int		assign_ret(double **radius, double *value)
{
	*radius = value;
	return (1);
}

int		ft_assign_radius2(t_parser *parser, t_world *world, double **radius)
{
	if (parser->parse_enum == e_parse_cobject &&
			!ft_strcmp("sphere_torus", parser->attribute))
		return (assign_ret(radius, &(world->cobjlist->cobject->cobject_union.
		sphere_torus.radius)));
	else if (parser->parse_enum == e_parse_cobject &&
			!ft_strcmp("adn", parser->attribute))
		return (assign_ret(radius, &(world->cobjlist->cobject->cobject_union.
		adn.radius)));
	else
		return (0);
}

int		ft_assign_radius(t_parser *parser, t_world *world, double **radius)
{
	if (parser->parse_enum == e_parse_object &&
	!ft_strcmp("sphere", parser->attribute))
		return (assign_ret(radius, &(world->cobjlist->cobject->objlist->object
		->object_union.sphere.radius)));
	else if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("cylinder", parser->attribute))
		return (assign_ret(radius, &(world->cobjlist->cobject->objlist->object
		->object_union.cylinder.radius)));
	else if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("ellipsoid", parser->attribute))
		return (assign_ret(radius, &(world->cobjlist->cobject->objlist->object
		->object_union.ellipsoid.radius)));
	else if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("hyperboloid", parser->attribute))
		return (assign_ret(radius, &(world->cobjlist->cobject->objlist->object
		->object_union.hyperboloid.radius)));
	else
		return (ft_assign_radius2(parser, world, radius));
}

void	ft_parse_radius(t_parser *parser, t_world *world, char *line)
{
	double *radius;

	radius = NULL;
	if (!parser->attribute)
	{
		ft_dprintf(2, "line %d: current object does not have radius tag\n",
				parser->nb_lines);
		exit(1);
	}
	if (!ft_assign_radius(parser, world, &radius))
	{
		ft_dprintf(2, "line %d: current object does not have radius tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_cdouble(&line, radius, 0.0001, 100000000);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
