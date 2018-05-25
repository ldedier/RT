/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/23 03:49:01 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_line		newray(t_point3d p, t_point3d vec)
{
	t_line	line;

	line.o = p;
	if (PERSPECTIVE == 1)
		line.v = (t_point3d){.x = 0, .y = 0, .z = 1};
	else if (PERSPECTIVE == 2)
		line.v = normalize(vec);;
	return (line);
}

static t_color		freeret(t_color c, t_hit **hit, t_shadowsfree *aux)
{
	int	i;

	if (*hit)
	{
		free(*hit);
		*hit = NULL;
		i = -1;
		if (aux)
		{
			while (++i < aux->nlights)
				if (aux->srays[i])
					free(aux->srays[i]);
		}
	}
	return (c);
}

static t_color		ray_color(t_line ray, t_world *world, int bounce, int fast)
{
	t_hit			*hit;
	t_line			*srays[MAX_LIGHTS];
	t_shadowsfree	aux;
	t_color			reflect_c;
	t_color			refract_c;
	t_color			fogged_c;
	t_color			illuminated_c;
	double			fog;

	if ((hit = trace(ray, world->cobjlist)))
	{
		fog = magnitude(newvector(hit->point, world->cam->o)) * world->fog.in;
		fog = fog > 1.0 ? 1.0 : fog;
		castshadows(world, hit, srays);
		aux = (t_shadowsfree){.srays = srays, .nlights = world->nlights};
		if (world->shader == 1)
			illuminated_c = illuminate(world, hit, srays, fast);
		else
			illuminated_c = illuminate_toon(world, hit, srays, fast);
		fogged_c = interpole_color(fog, illuminated_c, world->fog.color);
		if (bounce < MAX_BOUNCE && hit->obj.reflect > EPSILON)
		{
			reflect_c = ray_color(newray(translate_vec(hit->point,
							hit->pertbounce, EPSILON), hit->pertbounce),
					world, bounce + 1, 0);
		}
		else
		{
			reflect_c = get_color(0x000000);
			hit->obj.reflect = 0;
		}
		if (bounce < MAX_BOUNCE && hit->obj.transp > EPSILON)
		{
			refract_c = ray_color(newray(translate_vec(hit->point,
							ray.v, EPSILON), refraction(hit->normal, ray.v, 1,
							   hit->obj.refract)),
					world, bounce + 1, 0);
		}
		else
		{
			hit->obj.transp = 0;
			refract_c = get_color(0x000000);
		}
			return (freeret(interpole_color(hit->obj.transp, interpole_color(hit->obj.reflect,
						fogged_c, reflect_c), refract_c), &hit, &aux));
		//return (freeret(fogged_c, &hit, &aux));
	}
	return (freeret(world->fog.color, &hit, NULL));
}

t_color				render_pixel(t_world *world, t_pixel pix, int fast)
{
	t_point3d	point;
	t_color		ret;
	t_line line;

	point = screen2world(pix, world);
	line = newray(point, newvector(world->cam->o, point));
	line.x = pix.x;
	line.y = pix.y;
	ret = ray_color(line, world, 0, fast);
	if (line.x == 0 && line.y == VRES/2)
		return get_color(0x00ff00);
	return (ret);
}
