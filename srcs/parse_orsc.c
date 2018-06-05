/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_orsc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:49:18 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/06 00:09:57 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	else if (parser->parse_enum == e_parse_fog)
		color = &(world->fog.color);
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

void	ft_parse_pert(t_parser *parser, t_world *world, char *line)
{
	t_perturbations	*pert;

	if (parser->parse_enum == e_parse_object)
		pert = &(world->cobjlist->cobject->objlist->object->pert);
	else if (parser->parse_enum == e_parse_cobject)
		pert = &(world->cobjlist->cobject->pert);
	else
	{
		ft_dprintf(2, "line %d: current object can not have perturbation\n",
				parser->nb_lines);
		exit(1);
	}
	read_pert_type(parser, pert);
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}
