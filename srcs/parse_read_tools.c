/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 03:22:31 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/22 03:33:25 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				read_hex(char **line, int *to)
{
	int scss;

	scss = 1;
	*to = ft_patoi_hex(line, &scss);
	return (scss);
}

int				read_double(char **line, double *to)
{
	int scss;

	scss = 1;
	*to = ft_patof(line, &scss);
	return (scss);
}

int				read_int(char **line, int *to)
{
	int scss;

	scss = 1;
	if (!(ft_isdigit(**line)))
		scss = 0;
	*to = ft_patoi(line);
	if (!(ft_isspace(**line)) || **line != '<')
		scss = 0;
	return (scss);
}
