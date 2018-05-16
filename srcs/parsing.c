/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 00:34:20 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/16 02:50:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_init_parser(t_parser *parser)
{
	parser->nb_lines = 0;
	parser->tag_stack = NULL;
	parser->attribute = NULL;
	parser->tag = NULL;
	parser->parse_enum = e_parse_scene;
	parser->got_scene = 0;
}

void	ft_process_parsing_pos(t_parser *parser, t_world *world, char *line)
{
	t_point3d	*pos;

	if (parser->parse_enum == e_parse_camera)
		pos = &(world->cam->o);
	else if (parser->parse_enum == e_parse_object)
		pos = &(world->cobjlist->cobject->objlist->object->o);
	else if (parser->parse_enum == e_parse_cobject)
		pos = &(world->cobjlist->cobject->o);
	else if (parser->parse_enum == e_parse_light)
		pos = &(world->lights[world->nlights - 1].o);
	else
	{
		ft_dprintf(2, "line %d: current object can not have positionXYZ tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(pos->x));
	read_double(&line, &(pos->y));
	read_double(&line, &(pos->z));
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_process_parsing_rot(t_parser *parser, t_world *world, char *line)
{
	t_point3d	*rot;

	if (parser->parse_enum == e_parse_camera)
		rot = &(world->cam->rotation);
	else if (parser->parse_enum == e_parse_object)
		rot = &(world->cobjlist->cobject->objlist->object->r);
	else if (parser->parse_enum == e_parse_cobject)
		rot = &(world->cobjlist->cobject->r);
	else if (parser->parse_enum == e_parse_light)
		rot = &(world->lights[world->nlights - 1].v);
	else
	{
		ft_dprintf(2, "line %d: current object can not have rotationXYZ tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(rot->x));
	read_double(&line, &(rot->y));
	read_double(&line, &(rot->z));
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_process_parsing_scale(t_parser *parser, t_world *world, char *line)
{
	t_point3d	*scale;

	if (parser->parse_enum == e_parse_object)
		scale = &(world->cobjlist->cobject->objlist->object->s);
	else if (parser->parse_enum == e_parse_cobject)
		scale = &(world->cobjlist->cobject->s);
	else
	{
		ft_dprintf(2, "line %d: current object can not have rotationXYZ tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, &(scale->x));
	read_double(&line, &(scale->y));
	read_double(&line, &(scale->z));
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_give_default_characteristics(t_object *object)
{
	if (object->intersect_func == intersect_sphere)
		object->object_union.sphere.radius = 1;
	else if (object->intersect_func == intersect_cylinder)
		object->object_union.cylinder.radius = 1;
	else if (object->intersect_func == intersect_cone)
		object->object_union.cone.angle = M_PI / 4;
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
	else
	{
		ft_dprintf(2, "line %d: attribute %s unknown\n", parser->nb_lines,
				parser->attribute);
		exit(1);
	}
}

void	ft_process_parsing_object_start(t_parser *parser, t_world *world)
{
	t_object *object;

	if (parser->parse_enum != e_parse_cobject)
	{
		printf("%d\n", parser->parse_enum);
		ft_dprintf(2, "line %d: can only declare object inside cobject\n",
				parser->nb_lines);
		exit(1);
	}
	parser->parse_enum = e_parse_object;
	if (!(object = ft_new_object(*(world->cobjlist->cobject))))
		ft_error("could not malloc object");
	if (parser->attribute == NULL)
	{
		ft_dprintf(2, "line %d: object must have a specified name\n");
		exit(1);
	}
	ft_process_parsing_object_attributes(parser, object);
	ft_give_default_characteristics(object);
	add_obj(&(world->cobjlist->cobject->objlist), object);
}

void	ft_process_parsing_cobject_start(t_parser *parser, t_world *world)
{
	t_cobject *cobject;

	if (!(cobject = ft_new_cobject()))
		ft_error("could not malloc cobject");
	world->selected_cobject = cobject;
	add_cobj(&(world->cobjlist), cobject);
	parser->parse_enum = e_parse_cobject;
}

void	ft_process_parsing_light_start(t_parser *parser, t_world *world)
{
	parser->parse_enum = e_parse_light;
	if (world->nlights++ > MAX_LIGHTS)
	{
		ft_dprintf(2, "line %d: too much lights in the scene (max = %d)\n",
				parser->nb_lines, MAX_LIGHTS);
		exit(1);
	}
	ft_init_light(&(world->lights[world->nlights - 1]));
	if (parser->attribute == NULL)
	{
		ft_dprintf(2, "line %d: light should have a type (e.g. diffuse)");
		exit(1);
	}
	if (!ft_strcmp(parser->attribute, "diffuse"))
		world->lights[world->nlights - 1].type = 'p';
	else if (!ft_strcmp(parser->attribute, "spotlight"))
		world->lights[world->nlights - 1].type = 'd';
	else
	{
		ft_dprintf(2, "line %d: %s: unknown type of light\n", parser->nb_lines,
				parser->attribute);
		exit(1);
	}
}

void	ft_process_parsing_ambient_start(t_parser *parser, t_world *world)
{
	parser->parse_enum = e_parse_ambient;
	(void)world;
}

void	ft_parse_color(t_parser *parser, t_world *world, char *line)
{
	t_color	*color;
	int		col;

	if (parser->parse_enum == e_parse_object)
		color = &(world->cobjlist->cobject->objlist->object->c);
	else if (parser->parse_enum == e_parse_cobject)
		color = &(world->cobjlist->cobject->c);
	else if (parser->parse_enum == e_parse_light)
		color = &(world->lights[world->nlights - 1].c);
	else if (parser->parse_enum == e_parse_ambient)
		color = &(world->ambient.color);
	else
	{
		ft_dprintf(2, "line %d: current object can not have rotationXYZ tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_hex(&line, &(col));
	*color = get_color(col);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
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

void	ft_parse_src(t_parser *parser, t_world *world, char *line)
{
	(void)world;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_refraction(t_parser *parser, t_world *world, char *line)
{
	double *refraction;

	if (parser->parse_enum == e_parse_object)
		refraction = &(world->cobjlist->cobject->objlist->object->refract);
	else if (parser->parse_enum == e_parse_cobject)
		refraction = &(world->cobjlist->cobject->refract);
	else
	{
		ft_dprintf(2, "line %d: current object does not have refraction tag",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, refraction);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_transparency(t_parser *parser, t_world *world, char *line)
{
	double *transparency;

	if (parser->parse_enum == e_parse_object)
		transparency = &(world->cobjlist->cobject->objlist->object->transp);
	else if (parser->parse_enum == e_parse_cobject)
		transparency = &(world->cobjlist->cobject->transp);
	else
	{
		ft_dprintf(2,
				"line %d: current object does not have transparency tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, transparency);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_shine(t_parser *parser, t_world *world, char *line)
{
	double *shine;

	if (parser->parse_enum == e_parse_object)
		shine = &(world->cobjlist->cobject->objlist->object->shine);
	else if (parser->parse_enum == e_parse_cobject)
		shine = &(world->cobjlist->cobject->shine);
	else
	{
		ft_dprintf(2, "line %d: current object does not have shine tag",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, shine);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_intensity(t_parser *parser, t_world *world, char *line)
{
	double	*intensity;

	if (parser->parse_enum == e_parse_light)
		intensity = &(world->lights[world->nlights - 1].intensity);
	else if (parser->parse_enum == e_parse_ambient)
		intensity = &(world->ambient.in);
	else
	{
		ft_dprintf(2, "line %d: current object does not have intensity tag",
				parser->nb_lines);
		exit(1);
	}
	read_double(&line, intensity);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_process_parsing_stack_2(t_parser *parser, t_world *world, char *line)
{
	if (!ft_strcmp(parser->tag, "src"))
		ft_parse_src(parser, world, line);
	else if (!ft_strcmp(parser->tag, "color"))
		ft_parse_color(parser, world, line);
	else if (!ft_strcmp(parser->tag, "refraction"))
		ft_parse_refraction(parser, world, line);
	else if (!ft_strcmp(parser->tag, "transparency"))
		ft_parse_transparency(parser, world, line);
	else if (!ft_strcmp(parser->tag, "shine"))
		ft_parse_shine(parser, world, line);
	else if (!ft_strcmp(parser->tag, "intensity"))
		ft_parse_intensity(parser, world, line);
	else if (strcmp(parser->tag, "scene") &&
			strcmp(parser->tag, "objlist") &&
			strcmp(parser->tag, "lightlist"))
	{
		ft_dprintf(2, "line %d: unknown tag <%s>\n", parser->nb_lines,
				parser->tag);
		exit(1);
	}
}

void	ft_process_parsing_stack(t_parser *parser, t_world *world, char *line)
{
	if (!ft_strcmp(parser->tag, "positionXYZ"))
		ft_process_parsing_pos(parser, world, line);
	else if (!ft_strcmp(parser->tag, "rotationXYZ"))
		ft_process_parsing_rot(parser, world, line);
	else if (!ft_strcmp(parser->tag, "scaleXYZ"))
		ft_process_parsing_scale(parser, world, line);
	else if (!ft_strcmp(parser->tag, "camera"))
		parser->parse_enum = e_parse_camera;
	else if (!ft_strcmp(parser->tag, "object"))
		ft_process_parsing_object_start(parser, world);
	else if (!ft_strcmp(parser->tag, "cobject"))
		ft_process_parsing_cobject_start(parser, world);
	else if (!ft_strcmp(parser->tag, "ambientlight"))
		ft_process_parsing_ambient_start(parser, world);
	else if (!ft_strcmp(parser->tag, "light"))
		ft_process_parsing_light_start(parser, world);
	else if (!ft_strcmp(parser->tag, "radius"))
		ft_parse_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "angle"))
		ft_parse_angle(parser, world, line);
	else
		ft_process_parsing_stack_2(parser, world, line);
}

void	ft_process_parsing(t_parser *parser, t_world *world, char *line)
{
	ft_process_tag_stack(parser);
	if (parser->op == STACK)
		ft_process_parsing_stack(parser, world, line);
	else if (parser->op == POP)
	{
		if (!ft_strcmp(parser->tag, "object"))
			parser->parse_enum = e_parse_cobject;
		else
			parser->parse_enum = e_parse_scene;
		if (parser->attribute != NULL)
			ft_strdel(&(parser->attribute));
	}
	else
	{
		ft_dprintf(2, "line %d: not xml format\n", parser->nb_lines);
		exit(1);
	}
}

int	parse_line_new(char *line, t_world *world, t_parser *parser)
{
	parser->nb_lines++;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_parsing(parser, world, line);
	return (0);
}
