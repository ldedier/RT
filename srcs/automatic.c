/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:21:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 03:40:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_compute_automatic_sphere_torus(t_cobject *sphere_torus)
{
	int			i;
	double		angle;
	t_object	*sphere;

	i = 0;
	angle = 0;
	sphere = ft_new_object(*sphere_torus);
	sphere->cobject = sphere_torus;
	set_funcs(sphere, intersect_sphere, inside_sphere, normal_sphere);
	sphere->object_union.sphere.radius =
		sphere_torus->cobject_union.sphere_torus.spheres_radius;
	sphere->o.y = 0;
	while (i < sphere_torus->cobject_union.sphere_torus.nb_spheres)
	{
		sphere->o.x = cos(angle) *
			sphere_torus->cobject_union.sphere_torus.radius;
		sphere->o.z = sin(angle) *
			sphere_torus->cobject_union.sphere_torus.radius;
		add_obj_cpy(&(sphere_torus->objlist), sphere);
		angle += (2 * M_PI) / (double)
			sphere_torus->cobject_union.sphere_torus.nb_spheres;
		i++;
	}
	free(sphere);
}

void	ft_process_automatic(t_parser *parser, t_world *world)
{
	if (!ft_strcmp(parser->attribute, "sphere_torus"))
		ft_compute_automatic_sphere_torus(world->cobjlist->cobject);
	else if (!ft_strcmp(parser->attribute, "adn"))
		ft_compute_automatic_adn(world->cobjlist->cobject);
}
