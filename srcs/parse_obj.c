/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/27 07:41:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_add_triangles(char *source, t_world *world)
{
	t_cobject *cobject;
	t_obj_parser parser;
	t_object *triangle;
	int i;

	cobject = world->cobjlist->cobject;
	parser = ft_parse_obj(source);
	triangle = ft_new_triangle(*cobject);
	i = 0;
	while (i < parser.nb_faces)
	{
		triangle->object_union.triangle.v1.x = parser.draw_array[9 *i];
		triangle->object_union.triangle.v1.y = -parser.draw_array[9 *i + 1];
		triangle->object_union.triangle.v1.z = parser.draw_array[9 *i + 2];
		triangle->object_union.triangle.v2.x = parser.draw_array[9 * i + 3];
		triangle->object_union.triangle.v2.y = -parser.draw_array[9 * i + 4];
		triangle->object_union.triangle.v2.z = parser.draw_array[9 * i + 5];
		triangle->object_union.triangle.v3.x = parser.draw_array[9 * i + 6];
		triangle->object_union.triangle.v3.y = -parser.draw_array[9 * i + 7];
		triangle->object_union.triangle.v3.z = parser.draw_array[9 * i + 8];
		add_obj_cpy(&(cobject->objlist), triangle);
		i++;
	}
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
