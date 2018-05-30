/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specifics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:31:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/30 17:29:43 by ldedier          ###   ########.fr       */
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
	else if (object->intersect_func == intersect_goursat)
	{
		object->object_union.goursat.a = 5;
		object->object_union.goursat.b = 11.8;
	}
	else if (object->intersect_func == intersect_triangle)
	{
		object->object_union.triangle.v1 = ft_new_vec3(-1, 0, 0);
		object->object_union.triangle.v2 = ft_new_vec3(0, -1, 0);
		object->object_union.triangle.v3 = ft_new_vec3(1, 0, 0);
	}
	else if (object->intersect_func == intersect_hyperboloid)
		object->object_union.hyperboloid.radius = 1;
}

void	set_funcs(t_object *obj,
		int (*intersect_func)(t_line, t_object, double[MAX_DEGREE]),
		int (*inside_func)(t_hit, t_object),
		t_point3d (*normal_func)(t_object, t_point3d, t_line))
{
	obj->intersect_func = intersect_func;
	obj->inside_func = inside_func;
	obj->normal_func = normal_func;
}

void	ft_process_parsing_object_attributes(t_parser *parser, t_object *object)
{
	if (!ft_strcmp(parser->attribute, "sphere"))
		set_funcs(object, intersect_sphere, inside_sphere, normal_sphere);
	else if (!ft_strcmp(parser->attribute, "cone"))
		set_funcs(object, intersect_cone, inside_cone, normal_cone);
	else if (!ft_strcmp(parser->attribute, "cylinder"))
		set_funcs(object, intersect_cylinder, inside_cylinder, normal_cylinder);
	else if (!ft_strcmp(parser->attribute, "plane"))
		set_funcs(object, intersect_plane, inside_plane, normal_plane);
	else if (!ft_strcmp(parser->attribute, "ellipsoid"))
		set_funcs(object, intersect_ellipsoid, inside_plane, normal_ellipsoid);
	else if (!ft_strcmp(parser->attribute, "torus"))
		set_funcs(object, intersect_torus, inside_plane, normal_torus);
	else if (!ft_strcmp(parser->attribute, "goursat"))
		set_funcs(object, intersect_goursat, inside_plane, normal_goursat);
	else if (!ft_strcmp(parser->attribute, "lemniscate"))
		set_funcs(object, intersect_lemniscate, inside_plane, normal_lemniscate);
	else if (!ft_strcmp(parser->attribute, "roman"))
		set_funcs(object, intersect_roman, inside_plane, normal_roman);
	else if (!ft_strcmp(parser->attribute, "piriform"))
		set_funcs(object, intersect_piriform, inside_plane, normal_piriform);
	else if (!ft_strcmp(parser->attribute, "triangle"))
		set_funcs(object, intersect_triangle, inside_plane, normal_triangle);
	else if (!ft_strcmp(parser->attribute, "paraboloid"))
		set_funcs(object, intersect_paraboloid, inside_plane, normal_paraboloid);
	else if (!ft_strcmp(parser->attribute, "hyperboloid"))
		set_funcs(object, intersect_hyperboloid, inside_plane, normal_hyperboloid);
	else if (!ft_strcmp(parser->attribute, "mobius"))
		set_funcs(object, intersect_mobius, inside_plane, normal_mobius);
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
	else if (parser->parse_enum == e_parse_object &&
			!ft_strcmp("hyperboloid", parser->attribute))
		radius = &(world->cobjlist->cobject->objlist->object\
				->object_union.hyperboloid.radius);
	else if (parser->parse_enum == e_parse_cobject &&
			!ft_strcmp("sphere_torus", parser->attribute))
		radius = &(world->cobjlist->cobject->cobject_union\
				.sphere_torus.radius);
	else if (parser->parse_enum == e_parse_cobject &&
			!ft_strcmp("adn", parser->attribute))
		radius = &(world->cobjlist->cobject->cobject_union\
				.adn.radius);
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
