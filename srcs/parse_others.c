/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:27 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/08 07:55:04 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_refraction(t_parser *parser, t_world *world, char *line)
{
	double *refraction;

	if (parser->parse_enum == e_parse_object)
		refraction = &(world->cobjlist->cobject->objlist->object->refract);
	else if (parser->parse_enum == e_parse_cobject)
		refraction = &(world->cobjlist->cobject->refract);
	else
	{
		ft_dprintf(2, "line %d: current object does not have refraction tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_cdouble(&line, refraction, 0, 5);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_reflection(t_parser *parser, t_world *world, char *line)
{
	double *reflection;

	if (parser->parse_enum == e_parse_object)
		reflection = &(world->cobjlist->cobject->objlist->object->reflect);
	else if (parser->parse_enum == e_parse_cobject)
		reflection = &(world->cobjlist->cobject->reflect);
	else
	{
		ft_dprintf(2, "line %d: current object does not have reflexion tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_cdouble(&line, reflection, 0, 1);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
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
	read_cdouble(&line, transparency, 0, 1);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
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
		ft_dprintf(2, "line %d: current object does not have shine tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_cdouble(&line, shine, 0, 1000000);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}

void	ft_parse_intensity(t_parser *parser, t_world *world, char *line)
{
	double	*intensity;

	if (parser->parse_enum == e_parse_light)
		intensity = &(world->lights[world->nlights - 1].intensity);
	else if (parser->parse_enum == e_parse_ambient)
		intensity = &(world->ambient.in);
	else if (parser->parse_enum == e_parse_fog)
		intensity = &(world->fog.in);
	else
	{
		ft_dprintf(2, "line %d: current object does not have intensity tag\n",
				parser->nb_lines);
		exit(1);
	}
	read_cdouble(&line, intensity, 0, 100000);
	parser->op = ft_parse_tag(&line, parser);
	ft_process_tag_pop(parser);
}
