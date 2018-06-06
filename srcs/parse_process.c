/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/06 00:27:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_process_parsing_stack_3(t_parser *parser, t_world *world,
		char *line)
{
	if (!ft_strcmp(parser->tag, "resolution"))
		ft_parse_resolution(parser, world, line);
	else if (!ft_strcmp(parser->tag, "perturbation"))
		ft_parse_pert(parser, world, line);
	else if (!ft_strcmp(parser->tag, "fast_resolution"))
		ft_parse_fast_resolution(parser, world, line);
	else if (!ft_strcmp(parser->tag, "ellipsoidABC"))
		ft_parse_ellipsoid_abc(parser, world, line);
	else if (!ft_strcmp(parser->tag, "big_radius"))
		ft_parse_big_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "small_radius"))
		ft_parse_small_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "goursatAB"))
		ft_parse_goursat_ab(parser, world, line);
	else if (!ft_strcmp(parser->tag, "cut"))
		ft_process_parsing_cut_start(parser, world);
	else if (!ft_strcmp(parser->tag, "cutXYZ"))
		ft_process_parsing_cut_xyz(parser, world, line);
	else if (!ft_strcmp(parser->tag, "inequality"))
		ft_process_parsing_cut_inequality(parser, world, line);
	else if (!ft_strcmp(parser->tag, "value"))
		ft_process_parsing_cut_value(parser, world, line);
	else if (!ft_strcmp(parser->tag, "vertexA"))
		ft_process_parsing_vertex_a(parser, world, line);
	else if (!ft_strcmp(parser->tag, "vertexB"))
		ft_process_parsing_vertex_b(parser, world, line);
	else if (!ft_strcmp(parser->tag, "vertexC"))
		ft_process_parsing_vertex_c(parser, world, line);
	else if (!ft_strcmp(parser->tag, "nb_spheres"))
		ft_parse_nb_spheres(parser, world, line);
	else if (!ft_strcmp(parser->tag, "spheres_radius"))
		ft_parse_spheres_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "length"))
		ft_parse_length(parser, world, line);
	else if (!ft_strcmp(parser->tag, "color1"))
		ft_parse_color_n(parser, world, line, 1);
	else if (!ft_strcmp(parser->tag, "color2"))
		ft_parse_color_n(parser, world, line, 2);
	else if (!ft_strcmp(parser->tag, "color3"))
		ft_parse_color_n(parser, world, line, 3);
	else if (!ft_strcmp(parser->tag, "style"))
		ft_parse_style(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture_trans_x"))
		ft_parse_trans_x(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture_trans_y"))
		ft_parse_trans_y(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture_stretch_x"))
		ft_parse_stretch_x(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture_stretch_y"))
		ft_parse_stretch_y(parser, world, line);
	else if (strcmp(parser->tag, "scene") &&
			strcmp(parser->tag, "objlist") &&
			strcmp(parser->tag, "lightlist"))
	{
		ft_dprintf(2, "line %d: unknown tag <%s>\n", parser->nb_lines,
				parser->tag);
		exit(1);
	}
}

void		ft_process_parsing_stack_2(t_parser *parser, t_world *world,
		char *line)
{
	if (!ft_strcmp(parser->tag, "src"))
		ft_parse_src(parser, world, line);
	else if (!ft_strcmp(parser->tag, "color"))
		ft_parse_color(parser, world, line);
	else if (!ft_strcmp(parser->tag, "refraction"))
		ft_parse_refraction(parser, world, line);
	else if (!ft_strcmp(parser->tag, "reflection"))
		ft_parse_reflection(parser, world, line);
	else if (!ft_strcmp(parser->tag, "transparency"))
		ft_parse_transparency(parser, world, line);
	else if (!ft_strcmp(parser->tag, "shine"))
		ft_parse_shine(parser, world, line);
	else if (!ft_strcmp(parser->tag, "intensity"))
		ft_parse_intensity(parser, world, line);
	else if (!ft_strcmp(parser->tag, "shader"))
		ft_parse_shader(parser, world, line);
	else if (!ft_strcmp(parser->tag, "filter"))
		ft_parse_filter(parser, world, line);
	else if (!ft_strcmp(parser->tag, "negative"))
		ft_parse_negative(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture"))
		ft_parse_texture(parser, world, line);
	else if (!ft_strcmp(parser->tag, "normal_texture"))
		ft_parse_normal_texture(parser, world, line);
	else if (!ft_strcmp(parser->tag, "cut_color"))
		ft_process_parsing_cut_color(parser, world, line);
	else
		ft_process_parsing_stack_3(parser, world, line);
}

void		ft_process_parsing_stack(t_parser *parser, t_world *world,
		char *line)
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
	else if (!ft_strcmp(parser->tag, "define"))
		ft_process_parsing_define_start(parser, world);
	else if (!ft_strcmp(parser->tag, "def_cobject"))
		ft_process_parsing_def_cobject_start(parser, world);
	else if (!ft_strcmp(parser->tag, "ambientlight"))
		parser->parse_enum = e_parse_ambient;
	else if (!ft_strcmp(parser->tag, "fog"))
		parser->parse_enum = e_parse_fog;
	else if (!ft_strcmp(parser->tag, "light"))
		ft_process_parsing_light_start(parser, world);
	else if (!ft_strcmp(parser->tag, "radius"))
		ft_parse_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "angle"))
		ft_parse_angle(parser, world, line);
	else
		ft_process_parsing_stack_2(parser, world, line);
}

void		ft_process_parsing(t_parser *parser, t_world *world, char *line)
{
	ft_process_tag_stack(parser);
	if (parser->op == STACK)
		ft_process_parsing_stack(parser, world, line);
	else if (parser->op == POP)
	{
		if (!ft_strcmp(parser->tag, "cut"))
			parser->parse_enum = e_parse_object;
		else if (!ft_strcmp(parser->tag, "object"))
			parser->parse_enum = e_parse_cobject;
		else
		{
			if (parser->parse_enum == e_parse_cobject)
			{
				if (parser->attribute != NULL && 
						world->cobjlist->cobject->name == NULL)
					ft_process_automatic(parser, world);
				else if (world->cobjlist->cobject->name != NULL && 
					world->cobjlist->cobject->defining)
					ft_process_switch_list_cobject(&(world->cobjlist), 
						&(world->defcobjlist));
			}
			parser->parse_enum = e_parse_scene;
		}
		if (parser->attribute != NULL)
			ft_strdel(&(parser->attribute));
	}
	else
	{
		ft_dprintf(2, "line %d: not xml format\n", parser->nb_lines);
		exit(1);
	}
}

int			parse_line_new(char *line, t_world *world, t_parser *parser)
{
	parser->nb_lines++;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_parsing(parser, world, line);
	return (0);
}
