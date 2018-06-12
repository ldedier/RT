/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specific_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:32:16 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 22:58:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_process_parsing_object_caract2(t_parser *parser,
		t_object *object)
{
	if (!ft_strcmp(parser->attribute, "piriform"))
		set_func(object, ft_print_piriform_caracteristics);
	else if (!ft_strcmp(parser->attribute, "triangle"))
		set_func(object, ft_print_triangle_caracteristics);
	else if (!ft_strcmp(parser->attribute, "paraboloid"))
		set_func(object, ft_print_paraboloid_caracteristics);
	else if (!ft_strcmp(parser->attribute, "hyperboloid"))
		set_func(object, ft_print_hyperboloid_caracteristics);
}

static void	ft_process_parsing_object_caract(t_parser *parser, t_object *object)
{
	if (!ft_strcmp(parser->attribute, "sphere"))
		set_func(object, ft_print_sphere_caracteristics);
	else if (!ft_strcmp(parser->attribute, "cone"))
		set_func(object, ft_print_cone_caracteristics);
	else if (!ft_strcmp(parser->attribute, "cylinder"))
		set_func(object, ft_print_cylinder_caracteristics);
	else if (!ft_strcmp(parser->attribute, "plane"))
		set_func(object, ft_print_plane_caracteristics);
	else if (!ft_strcmp(parser->attribute, "ellipsoid"))
		set_func(object, ft_print_ellipsoid_caracteristics);
	else if (!ft_strcmp(parser->attribute, "torus"))
		set_func(object, ft_print_torus_caracteristics);
	else if (!ft_strcmp(parser->attribute, "goursat"))
		set_func(object, ft_print_goursat_caracteristics);
	else if (!ft_strcmp(parser->attribute, "lemniscate"))
		set_func(object, ft_print_lemniscate_caracteristics);
	else if (!ft_strcmp(parser->attribute, "roman"))
		set_func(object, ft_print_roman_caracteristics);
	else
		ft_process_parsing_object_caract2(parser, object);
}

void		ft_process_parsing_texture(t_parser *parser, t_object *object)
{
	if (!ft_strcmp(parser->attribute, "sphere"))
		object->texture_func = texture_sphere;
	else if (!ft_strcmp(parser->attribute, "cone"))
		object->texture_func = texture_cone;
	else if (!ft_strcmp(parser->attribute, "cylinder"))
		object->texture_func = texture_cylinder;
	else if (!ft_strcmp(parser->attribute, "plane"))
		object->texture_func = texture_plane;
	else
		object->texture_func = NULL;
}

void		ft_process_parsing_object_attributes2(t_parser *parser,
		t_object *object)
{
	if (!ft_strcmp(parser->attribute, "piriform"))
		set_funcs(object, intersect_piriform, inside_goursat, normal_piriform);
	else if (!ft_strcmp(parser->attribute, "triangle"))
		set_funcs(object, intersect_triangle, inside_goursat, normal_triangle);
	else if (!ft_strcmp(parser->attribute, "paraboloid"))
		set_funcs(object, intersect_paraboloid, inside_paraboloid,
				normal_paraboloid);
	else if (!ft_strcmp(parser->attribute, "hyperboloid"))
		set_funcs(object, intersect_hyperboloid, inside_hyperboloid,
				normal_hyperboloid);
	else if (!ft_strcmp(parser->attribute, "mobius"))
		set_funcs(object, intersect_mobius, inside_goursat, normal_mobius);
	else
	{
		ft_dprintf(2, "line %d: attribute %s unknown\n", parser->nb_lines,
				parser->attribute);
		exit(1);
	}
}

void		ft_process_parsing_object_attributes(t_parser *parser,
		t_object *object)
{
	if (!ft_strcmp(parser->attribute, "sphere"))
		set_funcs(object, intersect_sphere, inside_sphere, normal_sphere);
	else if (!ft_strcmp(parser->attribute, "cone"))
		set_funcs(object, intersect_cone, inside_cone, normal_cone);
	else if (!ft_strcmp(parser->attribute, "cylinder"))
		set_funcs(object, intersect_cylinder, inside_cylinder,
				normal_cylinder);
	else if (!ft_strcmp(parser->attribute, "plane"))
		set_funcs(object, intersect_plane, inside_plane, normal_plane);
	else if (!ft_strcmp(parser->attribute, "ellipsoid"))
		set_funcs(object, intersect_ellipsoid, inside_ellipsoid,
				normal_ellipsoid);
	else if (!ft_strcmp(parser->attribute, "torus"))
		set_funcs(object, intersect_torus, inside_torus, normal_torus);
	else if (!ft_strcmp(parser->attribute, "goursat"))
		set_funcs(object, intersect_goursat, inside_goursat, normal_goursat);
	else if (!ft_strcmp(parser->attribute, "lemniscate"))
		set_funcs(object, intersect_lemniscate, inside_goursat,
				normal_lemniscate);
	else if (!ft_strcmp(parser->attribute, "roman"))
		set_funcs(object, intersect_roman, inside_goursat, normal_roman);
	else
		ft_process_parsing_object_attributes2(parser, object);
	ft_process_parsing_texture(parser, object);
	ft_process_parsing_object_caract(parser, object);
}
