/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_perts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 01:16:54 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/31 14:13:40 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	read_pert_type(t_parser *parser, t_perturbations *pert)
{
	if (!parser->attribute)
	{
		ft_dprintf(2, "line %d: perturbation requires an attribute\n",
				parser->nb_lines);
		exit(1);
	}
	if (!ft_strcmp(parser->attribute, "waves"))
		*pert = e_waves;
	else if (!ft_strcmp(parser->attribute, "ripple"))
		*pert = e_ripple;
	else if (!ft_strcmp(parser->attribute, "noise"))
		*pert = e_noise;
	else if (!ft_strcmp(parser->attribute, "chess"))
		*pert = e_chess;
	else if (!ft_strcmp(parser->attribute, "spiral"))
		*pert = e_spiral;
}
