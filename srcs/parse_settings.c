/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 22:01:34 by lcavalle          #+#    #+#             */
/*   Updated: 2018/04/22 15:30:26 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	parse_ambient(char *line, t_illum *rillum)
{
	int	color;

	if (!(read_double(&line, &(rillum->in))) ||
			!(read_hex(&line, &color)))
		return (0);
	rillum->color = get_color(color);
	return (1);
}

int	parse_fog(char *line, t_illum *rillum)
{
	return (parse_ambient(line, rillum));
}
