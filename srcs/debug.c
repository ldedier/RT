/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:10:23 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/15 18:52:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_cobject(t_cobject cobj)
{
	printf("cobject: COMPOSED\n"
			"---origin: (%f, %f, %f)\n"
			"---scale: (%f, %f, %f)\n"
			"---direction: (%f, %f, %f)\n"
			"---col: 0x%X\n"
			"---transp: %f\n"
			"---reflect: %f\n"
			"---refract: %f\n"
			"---shine: %f\n",
			cobj.o.x, cobj.o.y, cobj.o.z,
			cobj.s.x, cobj.s.y, cobj.s.z,
			cobj.r.x, cobj.r.y, cobj.r.z,
			cobj.c.col, cobj.transp, cobj.reflect,
			cobj.refract, cobj.shine);
	fflush(stdout);
}

void	print_list(t_objlist *lst)
{
	while (lst != NULL)
	{
		print_object(*lst->object);
		lst = lst->next;
	}
}

void	print_camera(t_camera *cam)
{
	printf("camera: \n"
			"---pos: (%f, %f, %f)\n"
			"---rotation: (%f, %f, %f)\n"
			"---up: (%f, %f, %f)\n"
			"---look: (%f, %f, %f)\n"
			"---right: (%f, %f, %f)\n-----------------\n",
			cam->o.x, cam->o.y, cam->o.z,
			cam->rotation.x, cam->rotation.y, cam->rotation.z,
			cam->up.x, cam->up.y, cam->up.z,
			cam->look.x, cam->look.y, cam->look.z,
			cam->right.x, cam->right.y, cam->right.z);
	fflush(stdout);
}


void	print_clist(t_cobjlist *lst)
{
	ft_putendl("LIST OF COBJECTS:");
	while (lst != NULL)
	{
		print_cobject(*(lst->cobject));
		print_list(lst->cobject->objlist);
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

	if (obj.intersect_func == intersect_sphere)
		shape = "sphere";
	else if (obj.intersect_func == intersect_plane)
		shape = "plane";
	else if (obj.intersect_func == intersect_cone)
		shape = "cone";
	else if (obj.intersect_func == intersect_cylinder)
		shape = "cylinder";
	else
		shape = "UNKNOWN";
	printf("	object: %s\n"
			"	---origin: (%f, %f, %f)\n"
			"	---scale: (%f, %f, %f)\n"
			"	---direction: (%f, %f, %f)\n"
			"	---col: 0x%X\n"
			"	---transp: %f\n"
			"	---reflect: %f\n"
			"	---refract: %f\n"
			"	---shine: %f\n"
			, shape,
			obj.o.x, obj.o.y, obj.o.z,
			obj.s.x, obj.s.y, obj.s.z,
			obj.r.x, obj.r.y, obj.r.z,
			obj.c.col, obj.transp, obj.reflect,
			obj.refract, obj.shine);
	fflush(stdout);
}
