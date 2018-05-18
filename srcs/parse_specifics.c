/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specifics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:31:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/17 19:10:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_give_default_characteristics(t_object *object)
{
	if (object->intersect_func == intersect_sphere)
		object->object_union.sphere.radius = 1;
	else if (object->intersect_func == intersect_cylinder)
		object->object_union.cylinder.radius = 1;
	else if (object->intersect_func == intersect_cone)
		object->object_union.cone.angle = M_PI / 4;
	else if (object->intersect_func == intersect_ellipsoid)
	{
		object->object_union.ellipsoid.abc = ft_new_vec3(1, 1.2, 0.7);
		object->object_union.ellipsoid.radius = 1;
	}
	else if (object->intersect_func == intersect_torus)
	{
		object->object_union.torus.big_rad = 2;
		object->object_union.torus.small_rad = 1;
	}
}

void	ft_process_parsing_object_attributes(t_parser *parser, t_object *object)
{
	if (!ft_strcmp(parser->attribute, "sphere"))
		object->intersect_func = intersect_sphere;
	else if (!ft_strcmp(parser->attribute, "cone"))
		object->intersect_func = intersect_cone;
	else if (!ft_strcmp(parser->attribute, "cylinder"))
		object->intersect_func = intersect_cylinder;
	else if (!ft_strcmp(parser->attribute, "plane"))
		object->intersect_func = intersect_plane;
	else if (!ft_strcmp(parser->attribute, "ellipsoid"))
		object->intersect_func = intersect_ellipsoid;
	else if (!ft_strcmp(parser->attribute, "torus"))
		object->intersect_func = intersect_torus;
	else
	{
		ft_dprintf(2, "line %d: attribute %s unknown\n", parser->nb_lines,
				parser->attribute);
		exit(1);
	}
}

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
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_radius(t_parser *parser, t_world *world, char *line)
{
	double *radius;

	if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("sphere", parser->attribute))
		radius = &(world->cobjlist->cobject->objlist->object\
				->object_union.sphere.radius);
	else if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("cylinder", parser->attribute))
		radius = &(world->cobjlist->cobject->objlist->object\
				->object_union.cylinder.radius);
	else if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("ellipsoid", parser->attribute))
		radius = &(world->cobjlist->cobject->objlist->object\
				->object_union.ellipsoid.radius);
	else
	{
		ft_dprintf(2, "line %d: current object does not have radius tag",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, radius);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}
