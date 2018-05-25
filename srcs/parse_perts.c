/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_perts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 01:16:54 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/24 07:18:19 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	read_pert_type(t_parser *parser, t_perturbations *pert)
{
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
