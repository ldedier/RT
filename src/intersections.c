/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 01:01:52 by lcavalle          #+#    #+#             */
/*   Updated: 2018/02/22 18:33:15 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*quadratic equation. a would always be 1 (as it is the square of the unit vec)
**  so we simplify it by dividing b by 2 and removing the 4 from the radicand
** (so now it is b*b - ac)(wikipedia line-sphere intersection)
*/
int		intersect_sphere(t_line line, t_object obj, t_point3d *hitpoint)
{
	t_point3d	tmpvec;
	t_quadratic	equa;
	t_quadsol	sols;
	double		t;
	double		radic;

	(*hitpoint) = POINT_BEHIND_CAMERA;
	tmpvec = newvector(obj.o, line.o);
	equa = (t_quadratic){.a = 1, .b = dotprod(tmpvec, line.v),
		.c = dotprod(tmpvec, tmpvec) - obj.s.x * obj.s.x};
	radic = equa.b * equa.b - equa.c;
	if (radic < 0.0)
		return (0);
	sols.t1 = -equa.b + sqrt(radic);
	sols.t2 = -equa.b - sqrt(radic);
	if (sols.t1 < sols.t2 && sols.t1 > 0.0) 
		t = sols.t1;
	else
		t = sols.t2;
	(*hitpoint).x = line.o.x + line.v.x * t;
	(*hitpoint).y = line.o.y + line.v.y * t;
	(*hitpoint).z = line.o.z + line.v.z * t;
	return (1);
}

int		intersect_cone(t_line line, t_object obj, t_point3d *hitpoint)
{
	(void)line;
	(void)obj;
	(void)hitpoint;
	return (0);
}

int		intersect_plane(t_line line, t_object obj, t_point3d *hitpoint)
{
	(void)line;
	(void)obj;
	(void)hitpoint;
	return (0);
}

int		intersect_cylinder(t_line line, t_object obj, t_point3d *hitpoint)
{
	(void)line;
	(void)obj;
	(void)hitpoint;
	return (0);
}
