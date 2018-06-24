/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_perts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 01:16:54 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 08:24:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_assign_pert(t_parser *parser, t_perturbations *pert)
{
	if (!ft_strcmp(parser->attribute, "waves"))
		*pert = e_waves;
	else if (!ft_strcmp(parser->attribute, "ripple"))
		*pert = e_ripple;
	else if (!ft_strcmp(parser->attribute, "noise"))
		*pert = e_noise;
	else if (!ft_strcmp(parser->attribute, "chess"))
		*pert = e_chess;
	else if (!ft_strcmp(parser->attribute, "perlin"))
		*pert = e_perlin;
	else if (!ft_strcmp(parser->attribute, "marble"))
		*pert = e_marble;
	else if (!ft_strcmp(parser->attribute, "none"))
		*pert = e_none;
	else
	{
		ft_dprintf(
				2, "line %d: perturbation %s does not exist", parser->nb_lines,
					parser->attribute);
		exit(1);
	}
}

void	read_pert_type(t_parser *parser, t_perturbations *pert)
{
	if (!parser->attribute)
	{
		ft_dprintf(2, "line %d: perturbation requires an attribute\n",
				parser->nb_lines);
		exit(1);
	}
	ft_assign_pert(parser, pert);
}
