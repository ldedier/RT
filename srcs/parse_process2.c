/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 20:14:10 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 20:14:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_process_parsing_stack_6(t_parser *parser, t_world *world,
		char *line)
{
	if (!ft_strcmp(parser->tag, "mod_value"))
		ft_process_parsing_mod_value(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture_trans_x"))
		ft_parse_trans_x(parser, world, line);
	else if (!ft_strcmp(parser->tag, "mod_transp") ||
				!ft_strcmp(parser->tag, "mod_refract") ||
					!ft_strcmp(parser->tag, "mod_reflect"))
		ft_process_parsing_mod_start(parser, world);
	else if (strcmp(parser->tag, "scene") &&
			strcmp(parser->tag, "objlist") &&
			strcmp(parser->tag, "lightlist"))
	{
		ft_dprintf(2, "line %d: unknown tag <%s>\n", parser->nb_lines,
				parser->tag);
		exit(1);
	}
}

void		ft_process_parsing_stack_5(t_parser *parser, t_world *world,
		char *line)
{
	if (!ft_strcmp(parser->tag, "texture_trans_y"))
		ft_parse_trans_y(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture_stretch_x"))
		ft_parse_stretch_x(parser, world, line);
	else if (!ft_strcmp(parser->tag, "texture_stretch_y"))
		ft_parse_stretch_y(parser, world, line);
	else if (!ft_strcmp(parser->tag, "normal_texture"))
		ft_parse_normal_texture(parser, world, line);
	else if (!ft_strcmp(parser->tag, "ebloui"))
		ft_parse_ebloui(parser, world, line);
	else if (!ft_strcmp(parser->tag, "radius"))
		ft_parse_radius(parser, world, line);
	else if (!ft_strcmp(parser->tag, "angle"))
		ft_parse_angle(parser, world, line);
	else if (!ft_strcmp(parser->tag, "cut_color"))
		ft_process_parsing_cut_color(parser, world, line);
	else
		ft_process_parsing_stack_6(parser, world, line);
}

void		ft_process_parsing_stack_4(t_parser *parser, t_world *world,
		char *line)
{
	if (!ft_strcmp(parser->tag, "mod_color"))
		ft_process_parsing_mod_color(parser, world, line);
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
	else
		ft_process_parsing_stack_5(parser, world, line);
}

void		ft_process_parsing_stack_3(t_parser *parser, t_world *world,
		char *line)
{
	if (!ft_strcmp(parser->tag, "resolution"))
		ft_parse_resolution(parser, world, line);
	else if (!ft_strcmp(parser->tag, "perturbation"))
		ft_parse_pert(parser, world, line);
	else if (!ft_strcmp(parser->tag, "antialiasing"))
		ft_parse_antialiasing(parser, world, line);
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
		ft_process_parsing_inequality(parser, world, line);
	else if (!ft_strcmp(parser->tag, "value"))
		ft_process_parsing_value(parser, world, line);
	else
		ft_process_parsing_stack_4(parser, world, line);
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
	else
		ft_process_parsing_stack_3(parser, world, line);
}
