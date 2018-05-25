/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:37:59 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/25 19:27:57 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	getwhiteratio(t_color c, double bot, double top)
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

static t_illum	getillum(t_world *world, t_hit *hit, t_line **srays)
{
	int		i;
	t_illum	illu;
	double	newillu;
	t_light	light;

	i = -1;
	illu.in = world->ambient.in;
	illu.color = interpole_color(illu.in, BLACK_COLOR, world->ambient.color);
	while (++i < world->nlights)
		if (srays[i])
		{
			light = world->lights[i];
			if (light.type != 'd')
				light.intensity = 1.0 * (1.0 - world->fog.in) /
					sqrt(magnitude(newvector(hit->point, light.o)));
			newillu = dotprod(hit->normal, srays[i]->v) *
				light.intensity / world->nlights;
			newillu = newillu > 0 ? newillu : newillu * -1;
			newillu = newillu > 1.0 ? 1.0 : newillu;
			illu.in += newillu;
			illu.color = add_colors(
					illu.color, scale_color(light.c, newillu));
		}
	illu.in = illu.in < world->ambient.in ? world->ambient.in : illu.in;
	illu.in = illu.in > 1.0 ? 1.0 : illu.in;
	return (illu);
}

static t_illum	getshine(t_world *world, t_hit *hit, t_line **srays, t_color lc)
{
	int		i;
	t_illum	shine;
	double	newsh;
	t_light	light;

	shine.color = lc;
	shine.in = 0;
	i = -1;
	while (++i < world->nlights)
		if (srays[i] && world->lights[i].type != 'd')
		{
			light = world->lights[i];
			light.intensity = magnitude(newvector(hit->point, light.o)) *
				(1.0 - world->fog.in);
			newsh = dotprod(hit->bounce, srays[i]->v);
			newsh = newsh > 0 ? pow(newsh, PHONG * light.intensity) : 0;
			shine.color = add_colors(
					shine.color, scale_color(light.c, newsh));
			shine.in = shine.in + newsh > 1.0 ? 1.0 : shine.in + newsh;
		}
	return (shine);
}






int		ft_get_pixel(int x, int y, unsigned char *img, int dim_X, int bpp)
{
	int		nb;
	char	color[4];

	nb = (x * (bpp / 8)) + (y * (bpp / 8) * dim_X);
	color[0] = img[nb];
	color[1] = img[nb + 1];
	color[2] = img[nb + 2];
	color[3] = 0;
	return (*(int *)color);
}

t_color			illuminate(t_world *world, t_hit *hit, t_line **srays, int fast)
{
	t_illum	illu;
	t_illum	shine;
	t_color	lightcol;
	t_color	color;

	illu = getillum(world, hit, srays);
	//lightcol = interpole_color(illu.in, BLACK_COLOR, interpole_color(
	//			getwhiteratio(illu.color, 0.3, 1), illu.color, hit->obj.c));

	if (0)
	{
		//sphere UV mapping
		t_point3d p = normalize(hit->old_normal);
		float u = 0.5 + ((atan2(p.z, p.x)) / (2 * M_PI));
		float v = 0.5 - (asin(p.y) / M_PI);
		u = (int)(u * world->bmp_parser.width);
		v = (int)(v * world->bmp_parser.height);
		int col = ft_get_pixel(u, v, world->bmp_parser.pixels, world->bmp_parser.width, world->bmp_parser.bpp);
		color = get_color(col);
	}
	else if (0)
	{
		t_point3d p = hit->old_point;
		float u = 0.5 + (atan2(p.y, p.x)) / (2 * M_PI);
		float v = fabs(p.z) / M_PI;
		//printf("%f %f\n", u, v);
		u = (int)(u * world->bmp_parser.width);
		v = (int)(v * world->bmp_parser.height);
		int col = ft_get_pixel(u, v, world->bmp_parser.pixels, world->bmp_parser.width, world->bmp_parser.bpp);
		color = get_color(col);
	}
	else if (1)
	{
		//plane UV mapping
		t_point3d m_UAxis;
		m_UAxis.x = hit->old_normal.y;
		m_UAxis.y = hit->old_normal.z;
		m_UAxis.z = -hit->old_normal.x;
		t_point3d m_VAxis = crossprod(m_UAxis, hit->old_normal);
		float u = (int)(ft_dot_product(hit->old_point, m_UAxis) * world->bmp_parser.width + 1000) % (world->bmp_parser.width);
		float v = (int)(ft_dot_product(hit->old_point, m_VAxis) * world->bmp_parser.height + 1000) % (world->bmp_parser.height);
		if (u < 0)
			u *= -1;
		if (v < 0)
			v *= -1;
		int col = ft_get_pixel(u, v, world->bmp_parser.pixels, world->bmp_parser.width, world->bmp_parser.bpp);
		color = get_color(col);
	}
	else
	{
		color = hit->obj.c;
	}

	lightcol = interpole_color(illu.in, BLACK_COLOR, interpole_color(
				getwhiteratio(illu.color, 0.3, 1), illu.color, color));
	if (fast)
		return (lightcol);
	shine = getshine(world, hit, srays, lightcol);
	return (interpole_color(shine.in, lightcol, shine.color));
}
