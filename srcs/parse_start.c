/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:50:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 00:37:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_process_parsing_object_start(t_parser *parser, t_world *world)
{
	t_object *object;

	if (parser->parse_enum != e_parse_cobject
			|| !world->cobjlist->cobject->regular)
	{
		ft_dprintf(
			2, "line %d: can only declare objects inside regular cobjects\n",
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
	object->cobject = world->cobjlist->cobject;
	add_obj(&(world->cobjlist->cobject->objlist), object);
}

void	ft_process_parsing_cobject_start(t_parser *parser, t_world *world)
{
	t_cobject *cobject;

	if (!(cobject = ft_new_cobject()))
		ft_error("could not malloc cobject");
	world->selected_cobject = cobject;
	if (parser->attribute != NULL)
	{
		if (!ft_strcmp(parser->attribute, "adn") ||
			!ft_strcmp(parser->attribute, "sphere_torus") ||
			!ft_strcmp(parser->attribute, "obj"))
		{
			ft_give_default_characteristics_cobject(parser->attribute, cobject);
			cobject->regular = 0;
		}
		else
		{
			ft_dprintf(2,
			"line %d: cobjects can not have a %s attribute\n",
				parser->nb_lines, parser->attribute);
			exit(1);
		}
	}
	add_cobj(&(world->cobjlist), cobject);
	parser->parse_enum = e_parse_cobject;
}

void	ft_process_parsing_define_start(t_parser *parser, t_world *world)
{
	t_cobject *cobject;

	if (!(cobject = ft_new_cobject()))
		ft_error("could not malloc cobject");
	if (parser->attribute != NULL)
	{
		if (already_exists_defcobj(parser->attribute, world->defcobjlist))
		{
			ft_dprintf(2, "line %d: the define cobject \"%s\" already exist\n",
				parser->nb_lines, parser->attribute);
			exit(1);
		}
		else
			cobject->name = ft_strdup(parser->attribute);
	}
	else
	{
		ft_dprintf(2,
		"line %d: defining a cobject need a corresponding name\n",
			parser->nb_lines);
		exit(1);
	}
	cobject->defining = 1;
	add_cobj(&(world->cobjlist), cobject);
	parser->parse_enum = e_parse_cobject;
}

void	ft_process_parsing_def_cobject_start(t_parser *parser, t_world *world)
{
	if (parser->attribute != NULL)
	{
		if (!already_exists_defcobj(parser->attribute, world->defcobjlist))
		{
			ft_dprintf(2, "line %d: the define cobject \"%s\" does not exist\n",
				parser->nb_lines, parser->attribute);
			exit(1);
		}
		else
		{
			add_cobj_cpy(&(world->cobjlist),
				get_defcobject(parser->attribute, world->defcobjlist));
			world->selected_cobject = world->cobjlist->cobject;
		}
	}
	else
	{
		ft_dprintf(2,
		"line %d: defined cobject need a corresponding name\n",
			parser->nb_lines);
		exit(1);
	}
	parser->parse_enum = e_parse_cobject;
}
