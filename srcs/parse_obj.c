/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 08:27:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_triangle(t_object object)
{
	ft_print_point3d(object.object_union.triangle.v1);
	ft_print_point3d(object.object_union.triangle.v2);
	ft_print_point3d(object.object_union.triangle.v3);
}

void	ft_free_obj_parser(t_obj_parser *parser)
{
	free(parser->faces);
	free(parser->vertices);
}

void	ft_process_add_triangle(int i, t_object *tr, t_obj_parser parser)
{
	tr->object_union.triangle.v1.x = parser.vertices[parser.faces[i].x].x;
	tr->object_union.triangle.v1.y = -parser.vertices[parser.faces[i].x].y;
	tr->object_union.triangle.v1.z = parser.vertices[parser.faces[i].x].z;
	tr->object_union.triangle.v2.x = parser.vertices[parser.faces[i].y].x;
	tr->object_union.triangle.v2.y = -parser.vertices[parser.faces[i].y].y;
	tr->object_union.triangle.v2.z = parser.vertices[parser.faces[i].y].z;
	tr->object_union.triangle.v3.x = parser.vertices[parser.faces[i].z].x;
	tr->object_union.triangle.v3.y = -parser.vertices[parser.faces[i].z].y;
	tr->object_union.triangle.v3.z = parser.vertices[parser.faces[i].z].z;
}

void	ft_add_triangles(char *source, t_world *world)
{
	t_cobject		*cobject;
	t_object		*triangle;
	t_obj_parser	parser;
	int				nb_faces;

	cobject = world->cobjlist->cobject;
	parser = ft_parse_obj(source);
	triangle = ft_new_object(*cobject);
	triangle->cobject = cobject;
	triangle->intersect_func = intersect_triangle;
	triangle->normal_func = normal_triangle;
	nb_faces = 0;
	while (nb_faces < parser.nb_faces)
	{
		ft_process_add_triangle(nb_faces, triangle, parser);
		add_obj_cpy(&cobject->objlist, triangle);
		nb_faces++;
	}
	free(triangle);
	ft_free_obj_parser(&parser);
}

void	ft_parse_src(t_parser *parser, t_world *world, char *line)
{
	char *source;

	(void)world;
	if (parser->parse_enum == e_parse_cobject &&
			!ft_strcmp(parser->attribute, "obj") &&
			!world->cobjlist->cobject->populated)
	{
		world->cobjlist->cobject->populated = 1;
		source = ft_get_between_tag(&line);
		world->cobjlist->cobject->filename = source;
		ft_add_triangles(source, world);
	}
	else
	{
		ft_dprintf(2, "line %d: only obj cobject can have one \"src\" tag \n",
				parser->nb_lines, parser->tag);
		exit(1);
	}
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
