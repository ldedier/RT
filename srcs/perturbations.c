/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:44:53 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 04:42:05 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3d	pert_normal(t_hit *hit)
{
	t_point3d	pert;
	t_point3d	rand_ang;
	double		angle;

	if (hit->obj.pert == e_ripple)
		angle = sin(magnitude(hit->point));
	else if (hit->obj.pert == e_waves)
		angle = sin(hit->point.x);
	else
		angle = 0;
	pert = normalize(rotate_axis(hit->normal,
				normalize(crossprod(hit->normal, hit->point)), angle * 0.2));
	if (hit->obj.pert == e_noise)
	{
		angle = 0.12;
		rand_ang.x = (double)(rand() % 100) / 100 * angle - angle / 2;
		rand_ang.y = (double)(rand() % 100) / 100 * angle - angle / 2;
		rand_ang.z = (double)(rand() % 100) / 100 * angle - angle / 2;
		pert = rotate_vec(pert, rand_ang);
	}
	return (pert);
}

t_color		get_perlin_color(t_hit *hit)
{
	double	noisecoef;
	int		i;
	t_color	ret;
	t_color	inv;

	noisecoef = 0;
	i = 1;
	while (i < 5)
	{
		noisecoef += (1.0f / i) * fabs((perlin(i * 10 * hit->old_point.x,
						i * 10 * hit->old_point.y,
						i * 10 * hit->old_point.z)));
		i++;
	}
	ret = get_color(get_object_color(hit));
	inv = scale_convert_color(add_scale_intcolors(get_intcolor(WHITE_COLOR),
				get_intcolor(ret), -1), 1);
	return (interpole_color(ft_fclamp(0, noisecoef, 1),
				ret, inv));
}

t_color		get_marbre_color(t_hit *hit)
{
	double	noisecoef;
	int		i;
	t_color	ret;
	t_color	inv;

	noisecoef = 0;
	i = 1;
	while (i < 5)
	{
		noisecoef += (1.0f / i) * fabs((perlin(i * 10 * hit->old_point.x,
						i * 10 * hit->old_point.y,
						i * 10 * hit->old_point.z)));
		i++;
	}
	noisecoef = 0.5f * sin((hit->old_point.x + hit->old_point.y) *
			5 + noisecoef) + 0.5f;
	ret = get_color(get_object_color(hit));
	inv = scale_convert_color(add_scale_intcolors(get_intcolor(WHITE_COLOR),
				get_intcolor(ret), -1), 1);
	return (interpole_color(ft_fclamp(0, noisecoef, 1),
				ret, inv));
}

t_color		pert_color(t_hit *hit)
{
	t_color	ret;
	t_color	inv;

	if (hit->obj.pert == e_perlin)
		return (get_perlin_color(hit));
	if (hit->obj.pert == e_marble)
		return (get_marbre_color(hit));
	ret = get_color(get_object_color(hit));
	inv = scale_convert_color(add_scale_intcolors(get_intcolor(WHITE_COLOR),
				get_intcolor(ret), -1), 1);
	if (hit->obj.pert == e_chess &&
			(((sin(hit->old_point.x) > 0 ? 1 : -1) *
			(sin(hit->old_point.z) > 0 ? 1 : -1)) > 0))
		return (inv);
	return (ret);
}
