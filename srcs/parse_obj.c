/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/29 17:18:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	ft_print_triangle(t_object object)
{
	ft_print_point3d(object.object_union.triangle.v1);
	ft_print_point3d(object.object_union.triangle.v2);
	ft_print_point3d(object.object_union.triangle.v3);
}

void	ft_add_triangles(char *source, t_world *world)
{
	t_cobject *cobject;
	t_obj_parser parser;
	t_object *triangle;
	int nb_faces;

	cobject = world->cobjlist->cobject;
	parser = ft_parse_obj(source);
	triangle = ft_new_object(*cobject);
	triangle->intersect_func = intersect_triangle;
	triangle->normal_func = normal_triangle;
	triangle->inside_func = inside_plane;
	
	nb_faces = 0;
	while (nb_faces < parser.nb_faces)
	{
		triangle->object_union.triangle.v1.x = parser.vertices[parser.faces[nb_faces].x].x;
		triangle->object_union.triangle.v1.y = -parser.vertices[parser.faces[nb_faces].x].y;
		triangle->object_union.triangle.v1.z = parser.vertices[parser.faces[nb_faces].x].z;

		triangle->object_union.triangle.v2.x = parser.vertices[parser.faces[nb_faces].y].x;
		triangle->object_union.triangle.v2.y = -parser.vertices[parser.faces[nb_faces].y].y;
		triangle->object_union.triangle.v2.z = parser.vertices[parser.faces[nb_faces].y].z;

		triangle->object_union.triangle.v3.x = parser.vertices[parser.faces[nb_faces].z].x;
		triangle->object_union.triangle.v3.y = -parser.vertices[parser.faces[nb_faces].z].y;
		triangle->object_union.triangle.v3.z = parser.vertices[parser.faces[nb_faces].z].z;
		add_obj_cpy(&cobject->objlist, triangle);
		nb_faces++;
	}
	free(triangle);
}

void	ft_parse_src(t_parser *parser, t_world *world, char *line)
{
	char *source;
	(void)world;
	if (parser->parse_enum == e_parse_cobject &&
			!ft_strcmp(parser->attribute, "obj"))
	{
		source = ft_get_between_tag(&line);
		ft_add_triangles(source, world);
		free(source);
	}
	else
	{
		ft_dprintf(2, "line %d: only obj cobject can have a \"src\" tag\n",
				parser->nb_lines, parser->tag);
		exit(1);
	}
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}
