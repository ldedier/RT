/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_perts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 01:16:54 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/23 01:47:50 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	read_pert_dir(t_perturbation *pert, char *line)
{
	read_double(&line, &(pert->v.x));
	pert->v.y = 0;
	read_double(&line, &(pert->v.z));
	ft_point3d_normalize(&(pert->v));
}
/*
static void	read_pert_col(t_perturbation *pert, char *line)
{
	(void)pert;
	(void)line;
}
*/
void		read_pert_type(t_parser *parser, t_perturbation *pert, char *line)
{
	if (!ft_strcmp(parser->attribute, "mattress"))
		pert->type = e_mattress;
	else if (!ft_strcmp(parser->attribute, "sonar"))
		pert->type = e_sonar;
	else if (!ft_strcmp(parser->attribute, "ripple"))
		pert->type = e_ripple;
	else if (!ft_strcmp(parser->attribute, "noise"))
		pert->type = e_noise;
	else if (!ft_strcmp(parser->attribute, "chess"))
		pert->type = e_chess;
	read_pert_dir(pert, line);
}
