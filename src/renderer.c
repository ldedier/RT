/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/22 17:16:42 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
** TODO: view plane pivot with camera rotation
*/
t_point3d	screen2world(t_pixel pix, t_world *world)
{
	t_point3d	p;

	p.x = world->cam->pd * pix.x - world->canvas->halved_win_size.x *
		world->cam->pd + world->cam->o.x;
	p.y = world->cam->pd * pix.y - world->canvas->halved_win_size.y *
		world->cam->pd + world->cam->o.y;
	p.z = world->cam->o.z + world->cam->fd;
	return (p);	
}
/*
**TODO: perspective (this is ortographic, we need to vector from camera to
**pixel and then normalize
*/
t_line	ray(t_point3d p, t_world *world)
{
	t_line	line;

	(void)world;
	line.o = p;
	line.v = (t_point3d){.x = 0, .y = 0, .z = 1};
	return (line);
}

t_color	render_pixel(t_world *world, t_pixel pix)
{
	t_color 	c;
	t_hit		hit;
	t_line		line;
	double		illum;

	c = BACKGROUND_COLOR;
	line = ray(screen2world(pix, world), world);
	hit = trace(line, world->objlist);
	if (dotprod(newvector(line.o, hit.point), line.v) > 0)
	{
		illum = dotprod(normalize(newvector(hit.obj.o,hit.point)),normalize(newvector(hit.point,world->lights[0].o))) * world->lights[0].intensity;
		illum = illum < 0.0 ? 0.0 : illum;
		illum = illum + AMBIENT_LIGHT > 1.0 ? 1.0 - AMBIENT_LIGHT : illum;
		c = interpole_color(AMBIENT_LIGHT + illum, BLACK_COLOR, hit.obj.c);
	}
	return (c);
}
