/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:10:23 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/01 07:32:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_list(t_objlist *lst)
{
	ft_putendl("LIST OF OBJECTS:");
	while (lst != NULL)
	{
		print_object(*lst->object);
		lst = lst->next;
	}
}

void	print_lights(t_world *world)
{
	int i;

	i = 0;
	ft_putendl("ARRAY OF LIGHTS:");
	while (i < world->nlights)
	{
		printf("light %i:\n"
				"intensity: %f\n"
				"pos: (%f, %f, %f)\n"
				"color: 0x%X\n", i,
				world->lights[i].intensity, world->lights[i].o.x,
				world->lights[i].o.y, world->lights[i].o.z,
				world->lights[i].c.col);
		fflush(stdout);
		i++;
	}
}
void	print_object(t_object obj)
{
	char	*shape;
/*
	if (obj.intersect_func == intersect_sphere)
		shape = "sphere";
	else if (obj.intersect_func == intersect_plane)
		shape = "plane";
	else if (obj.intersect_func == intersect_cone)
		shape = "cone";
	else if (obj.intersect_func == intersect_cylinder)
		shape = "cylinder";
	else*/
		shape = "UNKNOWN";
	printf("object: %s\n"
			"---origin: (%f, %f, %f)\n"
			"---scale: (%f, %f, %f)\n"
			"---direction: (%f, %f, %f)\n"
			"---col: 0x%X\n", shape,
			obj.o.x, obj.o.y, obj.o.z,
			obj.s.x, obj.s.y, obj.s.z,
			obj.r.x, obj.r.y, obj.r.z,
			obj.c.col);
	fflush(stdout);
}
