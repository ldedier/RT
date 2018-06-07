/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 05:33:22 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/06 20:33:20 by ldedier          ###   ########.fr       */
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
	(void)obj;
	t_point3d p =normalize(hit->unbumped_old_normal);
	float u = 0.5 + ((atan2(p.z, p.x)) / (2 * M_PI));
	float v = 0.5 - (asin(p.y) / M_PI);
	u = (int)(u * parser.width);
	v = (int)(v * parser.height);
	return (ft_get_pixel(u, v, parser));
}

int		texture_plane(t_object obj, t_hit *hit, t_bmp_parser parser)
{
	t_point3d m_UAxis;

	m_UAxis.x = hit->unbumped_old_normal.y;
	m_UAxis.y = hit->unbumped_old_normal.z;
	m_UAxis.z = hit->unbumped_old_normal.x;
	t_point3d m_VAxis = crossprod(m_UAxis, hit->unbumped_old_normal);
	float u = (int)(ft_dot_product(hit->old_point, m_UAxis) *
			(parser.width * obj.object_union.plane.texture_stretch_x) +
				obj.object_union.plane.texture_trans_x - 100000000) % (parser.width);
	float v = (int)(ft_dot_product(hit->old_point, m_VAxis) *
			(parser.height * obj.object_union.plane.texture_stretch_y)
			+ obj.object_union.plane.texture_trans_y + 100000000) % (parser.height);
	if (u < 0)
		u *= -1;
	if (v < 0)
		v *= -1;
	return (ft_get_pixel(u, v, parser));
}

int		texture_cylinder(t_object obj, t_hit *hit, t_bmp_parser parser)
{
	t_point3d d;

	(void)obj;
	d = hit->old_point;
	double u = (int)fabs(d.x * 100) % parser.width;
	double v = ((atan(d.z / d.y) + (M_PI / 2)) / (M_PI));
	v = (int)(v * parser.height);
	return (ft_get_pixel(u, v, parser));
}

int		texture_cone(t_object obj, t_hit *hit, t_bmp_parser parser)
{
	(void) obj;
	(void) hit;

	t_point3d d;
	d = hit->old_point;

	double u = (int)fabs(d.x * 100) % parser.width;
	double v = ((atan(d.z / d.y) + (M_PI / 2)) / (M_PI));
	v = (int)(v * parser.height);
	return (ft_get_pixel(u, v, parser));
}
