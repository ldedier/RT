/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/08 00:21:09 by ldedier          ###   ########.fr       */
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
/*
static float		distance(t_point3d a, t_point3d b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)));
*/

static t_color		ebloui(t_world *world, t_line ray, double t, double *ratio)
{
	int		i;
	float	coeff;
	float	sum;
	double dist;

	sum = 0.0f;
	i = 0;
	while (i < world->nlights)
	{
		if (world->lights[i].type == 'd')
			coeff = -ft_dot_product(ray.v, world->lights[i].v);
		else
			coeff = -ft_dot_product(ray.v, normalize(ft_point3d_cmp(ray.o, world->lights[i].o)));
		dist = magnitude(ft_point3d_cmp(ray.o, world->lights[i].o));
		coeff /= (dist * dist);
		if (coeff > 0 && (dist < t || t == -1))
		{
	//		printf("coeff %f\n", coeff);
			sum += coeff;
		}
		i++;
	}
	*ratio = ft_fclamp(0, sum, 1);
	sum = *ratio;
	return (interpole_color(sum, world->fog.color, get_color(0xffffff)));
}

double				ft_process_mod(t_color color, double old, t_mod mod)
{
	int take_old;

	if (!mod.enabled)
		return old;
	else
	{
		if (mod.color == 0xff0000)
			take_old = (mod.inequality((color.r / get_sum(color)), mod.value));
		else if (mod.color == 0x00ff00)
			take_old = (mod.inequality((color.g / get_sum(color)), mod.value));
		else
			take_old = (mod.inequality((color.b / get_sum(color)), mod.value));
		return (take_old ? mod.mod_value : old);
	}
}

void				ft_init_aux_render(t_aux_render *x, t_hit *hit)
{
	t_color color;

	color = get_color(get_object_color(hit));
	x->f_refract = ft_process_mod(color, hit->obj.refract, hit->obj.mod_refract);
	x->f_reflect = ft_process_mod(color, hit->obj.reflect, hit->obj.mod_reflect);
	x->f_transp = ft_process_mod(color, hit->obj.transp, hit->obj.mod_transp);
	//	x->f_reflect = hit->obj.reflect;
	//	x->f_refract = hit->obj.refract;
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
	t_color			ebloui_c;
	double fog;
	double			ebloui_ratio;
	t_aux_render 	x;

	if ((hit = trace(ray, world->cobjlist)))
	{
		ft_init_aux_render(&x, hit);
		fog = magnitude(newvector(hit->point, world->cam->o)) * world->fog.in;
		fog = fog > 1.0 ? 1.0 : fog;
		castshadows(world, hit, shadows);
		aux = (t_shadowsfree){.shadows = shadows, .nlights = world->nlights};
		if (world->shader == 1)
			illuminated_c = illuminate(world, hit, shadows, fast);
		else
			illuminated_c = illuminate_toon(world, hit, shadows, fast);
		fogged_c = interpole_color(fog, illuminated_c, world->fog.color);
		if (bounce < world->max_bounce && x.f_reflect > EPSILON && !fast)
			reflect_c = ray_color(newray(translate_vec(hit->point,
							hit->pertbounce, EPSILON2), hit->pertbounce),
					world, bounce + 1, 0);
		else
			reflect_c = pert_color(hit);
		if (bounce < world->max_bounce && x.f_transp > EPSILON && !fast)
		{
			if (fabs(x.f_refract - 1) > EPSILON)
				refract_c = ray_color(newray(translate_vec(hit->point,
								ray.v, EPSILON), refraction(hit, &ray, x.f_refract)),
						world, bounce + 1, 0);
			else
				refract_c = ray_color(newray(translate_vec(hit->point,
								ray.v, EPSILON), ray.v),
						world, bounce, 0);
		}
		else
			refract_c = pert_color(hit);

		ebloui_c = ebloui(world, ray, hit->t, &ebloui_ratio);
		return (freeret(interpole_color(x.f_transp,
						interpole_color(x.f_reflect,
							interpole_color(ebloui_ratio , fogged_c, WHITE_COLOR),
								reflect_c), refract_c), &hit, &aux));

	}
	ebloui_c = ebloui(world, ray, -1, &ebloui_ratio);
	return (freeret(ebloui_c, &hit, NULL));
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
