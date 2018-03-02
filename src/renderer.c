/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/03/02 20:34:55 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_point3d	screen2world(t_pixel pix, t_world *world)
{
	t_camera	*cam;
	t_point3d	p;
	t_point3d	vec;
	t_point3d	scale;

	cam = world->cam;
	vec = crossprod(cam->up, cam->look);
	scale.x = -world->canvas->halved_win_size.x * cam->pd + cam->pd * pix.x;
	scale.y = -world->canvas->halved_win_size.y * cam->pd + cam->pd * pix.y;
	scale.z = cam->fd;
	p = translate_vec(translate_vec(translate_vec(cam->o, cam->look, scale.z),
				vec, scale.x), cam->up, scale.y);
	return (p);
}

static t_line		ray(t_point3d p, t_world *world)
{
	t_line	line;

	line.o = p;
	if (PERSPECTIVE == 1)
		line.v = (t_point3d){.x = 0, .y = 0, .z = 1};
	else if (PERSPECTIVE == 2)
		line.v = normalize(newvector(world->cam->o, p));
	return (line);
}

static t_color		freeret(t_color c, t_hit **hit)
{
	if (hit)
	{
		free(*hit);
		*hit = NULL;
	}
	return (c);
}

/*
** sray = shadow ray, so for shadow hit...
*/

static int			shadowhit(t_world *world, t_hit *hit, t_line *sray)
{
	t_hit	*shit;

	sray->v = normalize(newvector(hit->point, world->lights[0].o));
	sray->o = translate_vec(hit->point, sray->v, EPSILON);
	if ((shit = trace(*sray, world->objlist)) &&
			magnitude(newvector(sray->o, shit->point)) <
			magnitude(newvector(hit->point, world->lights[0].o)))
		return (1);
	return (0);
}

t_color				render_pixel(t_world *world, t_pixel pix)
{
	t_hit		*hit;
	t_line		line;
	double		illu;
	t_line		sray;
	double		shine;

	line = ray(screen2world(pix, world), world);
	if ((hit = trace(line, world->objlist)))
	{
		if (shadowhit(world, hit, &sray))
			return (freeret(interpole_color(AMBIENT_LIGHT, BLACK_COLOR,
							hit->obj.c), &hit));
			illu = dotprod(hit->normal, sray.v) * world->lights[0].intensity;
		illu = illu < 0.0 ? 0.0 : illu;
		illu = illu > 1.0 - AMBIENT_LIGHT ? 1.0 - AMBIENT_LIGHT : illu;
		shine = dotprod(hit->bounce, sray.v) - SHINE;
		if (shine > 0)
			return (freeret(interpole_color(shine, interpole_color(
								AMBIENT_LIGHT + illu, BLACK_COLOR, hit->obj.c),
							WHITE_COLOR), &hit));
			return (freeret(interpole_color(AMBIENT_LIGHT + illu, BLACK_COLOR,
					hit->obj.c), &hit));
	}
	return (freeret(BACKGROUND_COLOR, &hit));
}
/*
**if (illu + AMBIENT_LIGHT > 1.0)
**	return (freeret(interpole_color(1.0 - (illu + AMBIENT_LIGHT - 1.0) /
**	(world->lights[0].intensity + AMBIENT_LIGHT - 1.0), interpole_color(SHINE,
**	hit->obj.c, WHITE_COLOR), hit->obj.c), &hit));
*/
