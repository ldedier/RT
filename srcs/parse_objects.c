/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 23:52:56 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/02 00:38:13 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parse_sphere(char *line, t_object *rsphere)
{
	int			color;

	rsphere->intersect_func = intersect_sphere;
	rsphere->normal_func = normal_sphere;
	if (!(read_double(&line, &(rsphere->o.x))) ||
		!(read_double(&line, &(rsphere->o.y))) ||
		!(read_double(&line, &(rsphere->o.z))) ||
		!(read_double(&line, &(rsphere->s.x))) ||
		!(read_hex(&line, &(color))))
		return (0);
	rsphere->s.x = fabs(rsphere->s.x);
	rsphere->c = get_color(color);
	rsphere->shine = 30;
	rsphere->reflect = 0.1;
	rsphere->refract = 0.4;
	rsphere->transp = 0;
	return (1);
}

int		parse_plane(char *line, t_object *rplane)
{
	t_point3d	n;
	int			color;

	rplane->intersect_func = intersect_plane;
	rplane->normal_func = normal_plane;
	if (!(read_double(&line, &(rplane->o.x))) ||
		!(read_double(&line, &(rplane->o.y))) ||
		!(read_double(&line, &(rplane->o.z))) ||
		!(read_double(&line, &(n.x))) ||
		!(read_double(&line, &(n.y))) ||
		!(read_double(&line, &(n.z))) ||
		!(read_hex(&line, &color)))
		return (0);
	rplane->c = get_color(color);
	rplane->r = normalize(n);
	rplane->shine = 100;
	rplane->reflect = 0;
	rplane->refract = 0.2;
	rplane->transp = 0.6;
	return (1);
}

int		parse_cone(char *line, t_object *rcone)
{
	t_point3d	v;
	int			color;

	rcone->intersect_func = intersect_cone;
	rcone->normal_func = normal_cone;
	if (!(read_double(&line, &(rcone->o.x))) ||
		!(read_double(&line, &(rcone->o.y))) ||
		!(read_double(&line, &(rcone->o.z))) ||
		!(read_double(&line, &(v.x))) ||
		!(read_double(&line, &(v.y))) ||
		!(read_double(&line, &(v.z))) ||
		!(read_double(&line, &(rcone->s.x))) ||
		!(read_hex(&line, &color)))
		return (0);
	rcone->c = get_color(color);
	rcone->r = normalize(v);
	rcone->shine = 30;
	rcone->reflect = 1;
	rcone->refract = 0.4;
	rcone->transp = 0;
	return (1);
}

int		parse_cylinder(char *line, t_object *rcyl)
{
	t_point3d	v;
	int			color;

	rcyl->intersect_func = intersect_cylinder;
	rcyl->normal_func = normal_cylinder;
	if (!(read_double(&line, &(rcyl->o.x))) ||
		!(read_double(&line, &(rcyl->o.y))) ||
		!(read_double(&line, &(rcyl->o.z))) ||
		!(read_double(&line, &(v.x))) ||
		!(read_double(&line, &(v.y))) ||
		!(read_double(&line, &(v.z))) ||
		!(read_double(&line, &(rcyl->s.x))) ||
		!(read_hex(&line, &color)))
		return (0);
	rcyl->c = get_color(color);
	rcyl->r = normalize(v);
	rcyl->shine = 0;
	rcyl->reflect = 0;
	rcyl->refract = 0.7;
	rcyl->transp = 1;
	return (1);
}

int		parse_light(char *line, t_light *rlight)
{
	int			color;

	if (!(read_double(&line, &(rlight->o.x))) ||
		!(read_double(&line, &(rlight->o.y))) ||
		!(read_double(&line, &(rlight->o.z))) ||
		!(read_double(&line, &(rlight->intensity))) ||
		!(read_hex(&line, &color)))
		return (0);
	rlight->c = get_color(color);
	rlight->type = 'p';
	rlight->v = (t_point3d){.x = 0, .y = 1, .z = 0};
	rlight->angle = 0.8;
	return (1);
}
