/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 05:33:22 by ldedier           #+#    #+#             */
/*   Updated: 2020/02/06 20:46:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_get_pixel(int x, int y, t_bmp_parser parser)
{
	int		nb;
	char	color[4];

	nb = (x * (parser.bpp / 8)) + (y * (parser.bpp / 8) * parser.width);
	color[0] = parser.pixels[nb];
	color[1] = parser.pixels[nb + 1];
	color[2] = parser.pixels[nb + 2];
	color[3] = 0;
	return (*(int *)color);
}

int		texture_sphere(t_object obj, t_hit *hit, t_bmp_parser parser)
{
	float		u;
	float		v;
	t_point3d	p;

	(void)obj;
	p = normalize(hit->unbumped_old_normal);
	u = 0.5 + ((atan2(p.z, p.x)) / (2 * M_PI));
	v = 0.5 - (asin(p.y) / M_PI);
	u = (int)(u * parser.width);
	v = (int)(v * parser.height);
	return (ft_get_pixel(u, v, parser));
}

int		texture_plane(t_object obj, t_hit *hit, t_bmp_parser parser)
{
	t_point3d	u_axis;
	t_point3d	v_axis;
	float		u;
	float		v;

	u_axis.x = hit->unbumped_old_normal.y;
	u_axis.y = hit->unbumped_old_normal.z;
	u_axis.z = hit->unbumped_old_normal.x;
	v_axis = crossprod(u_axis, hit->unbumped_old_normal);
	u = (int)(ft_dot_product(hit->old_point, u_axis) *
			(parser.width * obj.object_union.plane.texture_stretch_x) +
				obj.object_union.plane.texture_trans_x - 100000000)
					% (parser.width);
	v = (int)(ft_dot_product(hit->old_point, v_axis) *
			(parser.height * obj.object_union.plane.texture_stretch_y)
			+ obj.object_union.plane.texture_trans_y + 100000000) %
				(parser.height);
	if (u < 0)
		u *= -1;
	if (v < 0)
		v *= -1;
	if (hit->unbumped_old_normal.y == -1.0)
		return (ft_get_pixel(u, v, parser));
	else
		return (ft_get_pixel(parser.width - u, v, parser));

}

int		texture_cylinder(t_object obj, t_hit *hit, t_bmp_parser parser)
{
	t_point3d	d;
	float		u;
	float		v;

	(void)obj;
	d = hit->old_point;
	u = (int)fabs(d.x * 100) % parser.width;
	v = ((atan(d.z / d.y) + (M_PI / 2)) / (M_PI));
	v = (int)(v * parser.height);
	return (ft_get_pixel(u, v, parser));
}

int		texture_cone(t_object obj, t_hit *hit, t_bmp_parser parser)
{
	float		u;
	float		v;
	t_point3d	d;

	(void)obj;
	d = hit->old_point;
	u = (int)fabs(d.x * 100) % parser.width;
	v = ((atan(d.z / d.y) + (M_PI / 2)) / (M_PI));
	v = (int)(v * parser.height);
	return (ft_get_pixel(u, v, parser));
}
