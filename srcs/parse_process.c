/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/22 01:45:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_process_parsing_stack_3(t_parser *parser, t_world *world, char *line)
{
	if (!ft_strcmp(parser->tag, "ellipsoidABC"))
		ft_parse_ellipsoid_abc(parser, world, line);
	else if (!ft_strcmp(parser->tag, "big_radius"))
		ft_parse_big_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "small_radius"))
		ft_parse_small_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "goursatAB"))
		ft_parse_goursat_ab(parser, world, line);
	else if (strcmp(parser->tag, "scene") &&
			strcmp(parser->tag, "objlist") &&
			strcmp(parser->tag, "lightlist"))
	{
		ft_dprintf(2, "line %d: unknown tag <%s>\n", parser->nb_lines,
				parser->tag);
		exit(1);
	}
}

void	ft_process_parsing_stack_2(t_parser *parser, t_world *world, char *line)
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
	else
		ft_process_parsing_stack_3(parser, world, line);
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

int		parse_line_new(char *line, t_world *world, t_parser *parser)
{
	parser->nb_lines++;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_parsing(parser, world, line);
	return (0);
}
