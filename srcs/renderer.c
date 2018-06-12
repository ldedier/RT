/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:03:07 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 04:11:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double		ebloui_coeff(t_line ray, t_light light)
{
	if (light.type == 'd')
		return (-ft_dot_product(ray.v, light.v));
	else
		return (-ft_dot_product(ray.v,
					normalize(ft_point3d_cmp(ray.o, light.o))));
}

t_color				get_ebloui(t_world *world, t_line ray,
		double t, double *ratio)
{
	int		i;
	double	coeff;
	double	sum;
	double	dist;

	sum = 0.0f;
	i = 0;
	while (i < world->nlights)
	{
		if (!world->lights[i].ebloui)
		{
			i++;
			continue;
		}
		coeff = ebloui_coeff(ray, world->lights[i]);
		dist = magnitude(ft_point3d_cmp(ray.o, world->lights[i].o));
		coeff /= (dist * dist);
		if (coeff > 0 && (dist < t || t == -1))
			sum += coeff;
		i++;
	}
	*ratio = ft_fclamp(0, sum, 1);
	sum = *ratio;
	return (interpole_color(sum, world->fog.color, get_color(0xffffff)));
}

static t_color		render_fast(t_world *world, t_pixel pix)
{
	t_pixel		aapix;
	t_line		line;
	t_point3d	point;

	aapix.x = 0;
	aapix.y = 0;
	point = screen2world(pix, world, aapix);
	line = newray(point, newvector(world->cam->o, point));
	line.x = pix.x;
	line.y = pix.y;
	return (ray_color(line, world, 0, 1));
}

static t_color		render_slow(t_world *world, t_pixel pix)
{
	t_pixel		aapix;
	t_line		line;
	t_intcolor	ret;
	t_point3d	point;

	aapix.x = -1;
	ret = new_intcolor();
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
					get_intcolor(ray_color(line, world, 0, 0)),
					1.f / world->aa_sq_size / world->aa_sq_size);
		}
	}
	return (scale_convert_color(ret, 1));
}

t_color				render_pixel(t_world *world, t_pixel pix, int fast)
{
	if (!fast)
		return (render_slow(world, pix));
	else
		return (render_fast(world, pix));
}
