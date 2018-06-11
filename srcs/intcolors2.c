/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intcolors2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 08:33:10 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/11 08:34:04 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_intcolor	greyscale(t_intcolor c)
{
	double	grey;

	grey = (c.r + c.g + c.b) / 3;
	c.r = grey;
	c.g = grey;
	c.b = grey;
	return (c);
}

t_intcolor	cyanscale(t_intcolor c)
{
	double	cyan;

	cyan = (c.r + c.g + c.b) / 3;
	c.r = 0;
	c.g = ft_clamp(0, cyan, 255);
	c.b = ft_clamp(0, cyan, 255);
	return (c);
}

t_intcolor	redscale(t_intcolor c)
{
	double red;

	red = (c.r + c.g + c.b) / 3;
	c.r = ft_clamp(0, red, 255);
	c.g = 0;
	c.b = 0;
	return (c);
}
