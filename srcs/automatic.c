/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:21:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/30 03:26:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_compute_automatic_sphere_torus(t_cobject *sphere_torus)
{
	int i;
	double angle;
	int nb_spheres;
	t_object *sphere;

	i = 0;
	angle = 0;
	nb_spheres = sphere_torus->cobject_union.sphere_torus.nb_spheres;
	sphere = ft_new_object(*sphere_torus);
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
		angle += (2 * M_PI) / (double)nb_spheres;
		i++;
	}
	free(sphere);
}

void	ft_cut_cylinder_adn(t_object *object, double radius)
{
	t_cut *cut;

	if (!(cut = ft_new_cut()))
	{
		ft_dprintf(2, "malloc error\n");
		exit(1);
	}
	cut->relative = 1;
	cut->cut_xyz = ft_new_vec3(1, 0, 0);
	cut->value = radius;
	cut->inequality = bigger_than;
	ft_lstadd(&(object->cuts), ft_lstnew(cut, sizeof(t_cut)));
	cut->cut_xyz = ft_new_vec3(-1, 0, 0);
	ft_lstadd(&(object->cuts), ft_lstnew(cut, sizeof(t_cut)));
}

void	ft_compute_automatic_adn(t_cobject *adn)
{
	int i;
	double angle;
	t_object *sphere;
	t_object *cylinder;
	double  curve = M_PI / 16.0;
	double padding = 1.8;
	int radius = 5;

	i = 0;
	angle = 0;
	sphere = ft_new_object(*adn);
	set_funcs(sphere, intersect_sphere, inside_sphere, normal_sphere);
	sphere->object_union.sphere.radius = 1;
	
	cylinder = ft_new_object(*adn);
	set_funcs(cylinder, intersect_cylinder, inside_sphere, normal_cylinder);
	cylinder->object_union.cylinder.radius = 0.2;
	cylinder->c = get_color(0x00FFFF);
	ft_cut_cylinder_adn(cylinder, radius);
	while (i < adn->cobject_union.adn.length)
	{
		sphere->c = get_color(0xff0000);	
		sphere->o.x = -cos(angle) * radius;
		sphere->o.z = -sin(angle) * radius;
		sphere->o.y = -i * padding;
		add_obj_cpy(&(adn->objlist), sphere);
		sphere->c = get_color(0x0000ff);	
		sphere->o.x = cos(angle) * radius;
		sphere->o.z = sin(angle) * radius;
		add_obj_cpy(&(adn->objlist), sphere);
		cylinder->o.y = -i * padding;
		cylinder->r.y = -angle;
		add_obj_cpy(&(adn->objlist), cylinder);
		angle += curve;
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
