/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/17 04:56:33 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_line	ray(t_point3d p, t_world *world)
{

}

t_color	render_pixel(t_world *world, t_pixel pix)
{
	t_color 	c;
	t_hit		hit;
	t_line		line;

	c = BACKGROUND_COLOR;
	line = ray(2dto3d(pix), world);
	hit = trace(line, world->objlist);
	if (dotprod(newvector(line.o, hit.point), line.v) > 0)
		c = hit.object.c;
	return (c);
}
