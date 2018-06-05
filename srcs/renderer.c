/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/04 11:10:25 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_line		newray(t_point3d p, t_point3d vec)
{
	t_line	line;

	line.o = p;
	if (PERSPECTIVE == 1)
		line.v = (t_point3d){.x = 0, .y = 0, .z = 1};
	else if (PERSPECTIVE == 2)
		line.v = normalize(vec);
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
				if (aux->shadows[i])
					free(aux->shadows[i]);
		}
	}
	return (c);
}

static t_color		ray_color(t_line ray, t_world *world, int bounce, int fast)
{
	t_hit			*hit;
	t_shadow		*shadows[MAX_LIGHTS];
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
		castshadows(world, hit, shadows);
		aux = (t_shadowsfree){.shadows = shadows, .nlights = world->nlights};
		if (world->shader == 1)
			illuminated_c = illuminate(world, hit, shadows, fast);
		else
			illuminated_c = illuminate_toon(world, hit, shadows, fast);
		fogged_c = interpole_color(fog, illuminated_c, world->fog.color);
		if (bounce < MAX_BOUNCE && hit->obj.reflect > EPSILON2  && !fast)
			reflect_c = ray_color(newray(translate_vec(hit->point,
							hit->pertbounce, EPSILON2), hit->pertbounce),
					world, bounce + 1, 0);
		else
			reflect_c = pert_color(hit);
		if (bounce < MAX_BOUNCE && hit->obj.transp > EPSILON2 && !fast)
			refract_c = ray_color(newray(translate_vec(hit->point,
					ray.v, EPSILON2), refraction(hit, &ray)),
					world, bounce + 1, 0);
		else
			refract_c = pert_color(hit);
		return (freeret(interpole_color(hit->obj.transp,
						interpole_color(hit->obj.reflect,
							fogged_c, reflect_c), refract_c), &hit, &aux));
	}
	return (freeret(world->fog.color, &hit, NULL));
}

t_color				render_pixel(t_world *world, t_pixel pix, int fast)
{
	t_point3d	point;
	t_intcolor	ret;
	t_line		line;
	t_pixel		aapix;

	ret = new_intcolor();
	if (!fast)
	{
		aapix.x = -1;
		while (++aapix.x < world->aa_sq_size)
		{
			aapix.y = -1;
			while (++aapix.y < world->aa_sq_size)
			{
				point = screen2world(pix, world, aapix);
				line = newray(point, newvector(world->cam->o, point));
				line.x = pix.x;
				line.y = pix.y;
				ret = add_scale_intcolors(ret,
						get_intcolor(ray_color(line, world, 0, fast)),
						1.f / world->aa_sq_size / world->aa_sq_size);
			}
		}
	}
	else 
	{
		aapix.x = 0;
		aapix.y = 0;
		point = screen2world(pix, world, aapix);
		line = newray(point, newvector(world->cam->o, point));
		line.x = pix.x;
		line.y = pix.y;
		return (ray_color(line, world, 0, fast));
	}
	return (scale_convert_color(ret, 1));
}
