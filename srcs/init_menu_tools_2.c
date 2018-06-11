/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 05:00:24 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 06:06:14 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_dropdown	ft_new_dropdown(t_pixel pos, t_pixel size)
{
	t_dropdown	dd;

	dd.pos = pos;
	dd.size = size;
	return (dd);
}

float		ft_hue_to_rgb(float v1, float v2, float v_h)
{
	if (v_h < 0)
		v_h += 1.f;
	if (v_h > 1)
		v_h -= 1.f;
	if (6.f * v_h < 1)
		return (v1 + (v2 - v1) * 6.f * v_h);
	if (2.f * v_h < 1)
		return (v2);
	if (3.f * v_h < 2)
		return (v1 + (v2 - v1) * (0.666666f - v_h) * 6.f);
	return (v1);
}

void		ft_color_pix_2(t_color *color, float h, float s, float l)
{
	float		var_1;
	float		var_2;

	var_1 = 0;
	var_2 = 0;
	if (l < 0.5f)
		var_2 = l * (1.0f + s);
	else
		var_2 = (l + s) - (s * l);
	var_1 = 2.0f * l - var_2;
	color->r = ft_clamp(0, ft_hue_to_rgb(var_1, var_2, h + 0.333333f) * 255,
			255);
	color->g = ft_clamp(0, ft_hue_to_rgb(var_1, var_2, h) * 255, 255);
	color->b = ft_clamp(0, ft_hue_to_rgb(var_1, var_2, h - 0.333333f) * 255,
			255);
}

void		ft_color_pix(float x0, float y0, t_color *color)
{
	float		h;
	float		s;
	float		l;

	h = x0;
	s = 1.0f - y0;
	l = 1.0f - y0;
	if (s == 0)
	{
		color->r = ft_clamp(0, l * 255, 255);
		color->g = ft_clamp(0, l * 255, 255);
		color->b = ft_clamp(0, l * 255, 255);
	}
	else
		ft_color_pix_2(color, h, s, l);
	color->col = (color->r << 16) | (color->g << 8) | color->b;
}

void		ft_color_map(t_world *world)
{
	int			x;
	float		x0;
	int			y;
	float		y0;
	t_color		color;

	y = 0;
	y0 = 0;
	while (y < 100)
	{
		y0 = (float)y / 100;
		x = 0;
		while (x < 100)
		{
			x0 = (float)x / 100;
			ft_color_pix(x0, y0, &color);
			world->menu.color_map[y * 100 + x] = color;
			x++;
		}
		y++;
	}
}
