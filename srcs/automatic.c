/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:21:35 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/07 02:08:51 by ldedier          ###   ########.fr       */
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
	free(cut);
}

t_color		ft_sphere_color(t_cobject *adn, int i, int nb)
{
	if (adn->cobject_union.adn.style == e_plain)
		return (nb == 1 ? get_color(adn->cobject_union.adn.color1) :
				get_color(adn->cobject_union.adn.color2));
	else
		return
			((nb + i) % 2 == 0 ? get_color(adn->cobject_union.adn.color1) :
				get_color(adn->cobject_union.adn.color2));
}

void	ft_process_fill_adn(t_cobject *adn, t_object *cylinder,
		t_object *sphere, int i)
{
	double padding;
	double angle;

	padding = adn->cobject_union.adn.radius / 2.0 - 4 * cos(M_PI / 12.0);

	angle = i * M_PI / 12.0;
	sphere->c =ft_sphere_color(adn, i, 1);
	sphere->o.x = -cos(angle) * adn->cobject_union.adn.radius;
	sphere->o.z = -sin(angle) * adn->cobject_union.adn.radius;
	sphere->o.y = -i * padding +
		((adn->cobject_union.adn.length - 1) *
		(padding / 2));
	add_obj_cpy(&(adn->objlist), sphere);
	sphere->c = ft_sphere_color(adn, i, 2);
	sphere->o.x = cos(angle) * adn->cobject_union.adn.radius;
	sphere->o.z = sin(angle) * adn->cobject_union.adn.radius;
	add_obj_cpy(&(adn->objlist), sphere);
	cylinder->o.y = -i * padding +
		((adn->cobject_union.adn.length - 1) *
		(padding / 2));
	cylinder->r.y = -angle;
	add_obj_cpy(&(adn->objlist), cylinder);
}

void	ft_compute_automatic_adn(t_cobject *adn)
{
	int			i;
	double		angle;
	t_object	*sphere;
	t_object	*cylinder;
	double		padding;

	i = 0;
	angle = 0;
	sphere = ft_new_object(*adn);
	sphere->cobject = adn;
	set_funcs(sphere, intersect_sphere, inside_sphere, normal_sphere);
	sphere->object_union.sphere.radius = adn->cobject_union.adn.radius / 4.0;
	padding = adn->cobject_union.adn.radius / 2.0;
	cylinder = ft_new_object(*adn);
	set_funcs(cylinder, intersect_cylinder, inside_sphere, normal_cylinder);
	cylinder->object_union.cylinder.radius =
		adn->cobject_union.adn.radius / 12.0;
	cylinder->c = get_color(adn->cobject_union.adn.color3);
	ft_cut_cylinder_adn(cylinder, adn->cobject_union.adn.radius);
	while (i < adn->cobject_union.adn.length)
	{
		ft_process_fill_adn(adn, cylinder, sphere, i);
		i++;
	}
	free(sphere);
	free(cylinder);
}

void	ft_process_automatic(t_parser *parser, t_world *world)
{
	if (!ft_strcmp(parser->attribute, "sphere_torus"))
		ft_compute_automatic_sphere_torus(world->cobjlist->cobject);
	else if (!ft_strcmp(parser->attribute, "adn"))
		ft_compute_automatic_adn(world->cobjlist->cobject);
	else
	{
		ft_dprintf(2, "line %d: no automatic cobject named %s\n", 
				parser->nb_lines, parser->attribute);
	}
}
