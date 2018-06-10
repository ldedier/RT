/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 04:25:27 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/10 06:05:40 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				get_object_color(t_hit *hit)
{
	int ret;

	if (hit->obj.parser.width == -1)
		ret = hit->obj.c.col;
	else
		ret = hit->obj.texture_func(hit->obj, hit, hit->obj.parser);
	return (ret);
}

int				get_object_color_normal(t_hit *hit)
{
	int ret;

	if (hit->obj.parser_normal.width == -1)
		ret = 0x0000ff;
	else
		ret = hit->obj.texture_func(hit->obj, hit, hit->obj.parser_normal);
	return (ret);
}

double			clamp_newillu(double newillu, t_world *world, double shilin)
{
	if (world->shader == 1)
	{
		newillu = newillu / world->nlights;
		newillu *= 1 - shilin;
		newillu = newillu > 0 ? newillu : 0;
		newillu = newillu > 1.0 ? 1.0 : newillu;
	}
	else
	{
		if (newillu < 0)
			newillu = 0;
		else if (newillu < 0.4 * world->nlights)
			newillu = 0.3 * world->nlights;
		else if (newillu < 0.7 * world->nlights)
			newillu = 0.55 * world->nlights;
		else
			newillu = 1;
		newillu /= world->nlights;
	}
	return (newillu);
}

double			getwhiteratio(t_color c, double bot, double top)
{
	double	min;
	double	res;

	min = c.r;
	min = c.g < min ? c.g : min;
	min = c.b < min ? c.b : min;
	res = min / 0xFF;
	if (res > bot)
	{
		if (res < top)
			return (res);
		else
			return (top);
	}
	else
		return (bot);
}
