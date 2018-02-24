/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/24 03:04:08 by lcavalle         ###   ########.fr       */
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

	line.o = p;
	if (PERSPECTIVE == 1)
		line.v = (t_point3d){.x = 0, .y = 0, .z = 1};
	else if (PERSPECTIVE == 2)
		line.v = normalize(newvector(world->cam->o, p));
	else
	{
		ft_putendl("invalid perspective");
		exit(0);
	}
	return (line);
}
static t_color	freeret(t_color c, t_hit **hit)
{
	free (*hit);
	*hit = NULL;
	return (c);
}
t_color	render_pixel(t_world *world, t_pixel pix)
{
	t_hit		*hit;
	t_line		shadow;
	t_line		line;
	double		illu;
	t_hit		*aux;

	line = ray(screen2world(pix, world), world);
	if ((hit = trace(line, world->objlist)))
	{
		shadow.v = normalize(newvector(hit->point, world->lights[0].o));
		shadow.o = move(hit->point, shadow.v, EPSILON);
		if ((aux = trace(shadow, world->objlist)) &&
				magnitude(newvector(shadow.o, aux->point)) <
				magnitude(newvector(hit->point, world->lights[0].o)))
		{
			if (pix.x == 700 &&  pix.y == 20)
		printf("o %f %f %f v %f %f %f s %f %f %f\n", shadow.o.x, shadow.o.y, shadow.o.z, shadow.v.x, shadow.v.y, shadow.v.z, hit->point.x, hit->point.y, hit->point.z);fflush(stdout);
			return (freeret(interpole_color(AMBIENT_LIGHT, BLACK_COLOR,
							hit->obj.c), &hit));
		}
		illu = dotprod(hit->obj.normal_func(hit->obj, hit->point), shadow.v) *
				world->lights[0].intensity;
		illu = illu < 0.0 ? 0.0 : illu;
		if (illu + AMBIENT_LIGHT > 1.0)
			return (freeret(interpole_color(1.0 + (1.0 - illu) / AMBIENT_LIGHT,
							WHITE_COLOR, hit->obj.c), &hit));
		return (freeret(interpole_color(AMBIENT_LIGHT + illu, BLACK_COLOR,
						hit->obj.c), &hit));
	}
	return (freeret(BACKGROUND_COLOR, &hit));
}
