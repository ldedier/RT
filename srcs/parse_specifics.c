/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specifics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:31:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 00:18:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_give_default_characteristics_cobject(char *attribute,
		t_cobject *cobject)
{
	if (!ft_strcmp(attribute, "sphere_torus"))
	{
		cobject->cobject_union.sphere_torus.nb_spheres = 16;
		cobject->cobject_union.sphere_torus.spheres_radius = 1;
		cobject->cobject_union.sphere_torus.radius = 5;
	}
	else if (!ft_strcmp(attribute, "adn"))
	{
		cobject->cobject_union.adn.length = 20;
		cobject->cobject_union.adn.radius = 2;
		cobject->cobject_union.adn.color1 = 0xFF0000;
		cobject->cobject_union.adn.color2 = 0x0000FF;
		cobject->cobject_union.adn.color3 = 0x00FFFF;
		cobject->cobject_union.adn.style = e_plain;
	}
	cobject->descriptor = ft_strdup(attribute);
}

void	ft_give_default_characteristics2(t_object *object)
{
	if (object->intersect_func == intersect_goursat)
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
	else if (object->intersect_func == intersect_plane)
	{
		object->object_union.plane.texture_stretch_x = 1;
		object->object_union.plane.texture_stretch_y = 1;
		object->object_union.plane.texture_trans_x = 0;
		object->object_union.plane.texture_trans_y = 0;
	}
}

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
	else
		ft_give_default_characteristics2(object);
}

void	ft_parse_ebloui(t_parser *parser, t_world *world, char *line)
{
	int *ebloui;

	if (parser->parse_enum == e_parse_light)
		ebloui = &(world->lights[world->nlights - 1].ebloui);
	else
	{
		ft_dprintf(2, "line %d: current object can not have ebloui tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, ebloui);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
