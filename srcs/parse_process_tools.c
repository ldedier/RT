/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 00:40:40 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 00:40:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_transfer_mod_parser(t_parser *parser, t_world *world)
{
	if (!ft_strcmp(parser->tag, "mod_transp"))
		world->cobjlist->cobject->objlist->object->mod_transp = parser->mod;
	else if (!ft_strcmp(parser->tag, "mod_refract"))
		world->cobjlist->cobject->objlist->object->mod_refract = parser->mod;
	else if (!ft_strcmp(parser->tag, "mod_reflect"))
		world->cobjlist->cobject->objlist->object->mod_reflect = parser->mod;
	else
	{
		ft_dprintf(2, "line %d: modification unknown\n", parser->nb_lines);
		exit(1);
	}
}

void		ft_give_object_name(t_object *object, char *name)
{
	object->descriptor = ft_strdup(name);
}
