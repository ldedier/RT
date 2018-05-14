/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 22:44:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/15 00:29:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			read_hex(char **line, int *to)
{
	int scss;

	scss = 1;
	*to = ft_patoi_hex(line, &scss);
	return (scss);
}

int			read_double(char **line, double *to)
{
	int scss;

	scss = 1;
	*to = ft_patof(line, &scss);
	return (scss);
}
/*
   static int	read_param(char *line, t_world *world, int line_count)
   {
   if (line[0] == '#')
   ;
   else if (line[0] == 'a' && parse_ambient(line + 2, &(world->ambient)))
   ;
   else if (line[0] == 'f' && parse_fog(line + 2, &(world->fog)))
   ;
   else
   return (line_count);
   return (0);
   }

   static int	parse_line(char *line, t_world *world)
   {
   t_object	*obj;
   static int	line_count = 0;

   line_count++;
   obj = ft_memalloc(sizeof(t_object));
   if ((line[0] == 's' && parse_sphere(line + 2, obj)) ||
   (line[0] == 'p' && parse_plane(line + 2, obj)) ||
   (line[0] == 'y' && parse_cylinder(line + 2, obj)) ||
   (line[0] == 'c' && parse_cone(line + 2, obj)))
   {
   add_obj(&(world->objlist), obj);
   world->selected_object = obj;
   }
   else if (line[0] == 'l')
   {
   if (world->nlights >= MAX_LIGHTS ||
   !parse_light(line + 2, (world->lights + world->nlights)))
   {
   if (world->nlights >= MAX_LIGHTS)
   ft_putstr("Too many lights! => ");
   return (line_count);
   }
   world->nlights++;
   }
   else if (read_param(line, world, line_count))
   return (line_count);
   return (0);
   }
   */

t_cobject		*ft_new_cobject(void)
{
	t_cobject *res;

	if (!(res = ft_memalloc(sizeof(t_cobject))))
		return (NULL);
	res->objlist = NULL;
	return (res);
}

void	ft_add_obj_to_cobj(t_cobject *cobject, t_object *object)
{
	add_obj(&(cobject->objlist), object);
}

void		ft_init_cobject(t_cobject *cobject)
{
	cobject->o = ft_new_vec3(0, 0, 0);
	cobject->r = ft_new_vec3(0, 0, 0);
	cobject->s = ft_new_vec3(1, 1, 1);
	cobject->c = get_color(0xFF0000);
	cobject->transp = 0;
	cobject->refract = 0;
	cobject->reflect = 0;
	cobject->shine = 0;
	cobject->objlist = NULL;
}

void		ft_init_object(t_cobject cobject, t_object *object)
{
	object->o = ft_new_vec3(0, 0, 0);
	object->r = ft_new_vec3(0, 0, 0);
	object->s = ft_new_vec3(1, 1, 1);
	object->c = get_color(cobject.c.col);
	object->transp = cobject.transp;
	object->refract = cobject.refract;
	object->reflect = cobject.reflect;
	object->shine = cobject.shine;
}

void		ft_fake_objects(t_world *world)
{
	t_object *obj = ft_memalloc(sizeof(t_object));
	t_object *obj2 = ft_memalloc(sizeof(t_object));
	t_object *obj3 = ft_memalloc(sizeof(t_object));
	t_object *obj4 = ft_memalloc(sizeof(t_object));
	t_object *obj5 = ft_memalloc(sizeof(t_object));

	obj->intersect_func = intersect_sphere;
	obj2->intersect_func = intersect_cylinder;
	obj3->intersect_func = intersect_sphere;
	obj4->intersect_func = intersect_cylinder;
	obj5->intersect_func = intersect_sphere;

	obj->o = ft_new_vec3(0, 2, 0);
	obj2->o = ft_new_vec3(0, 0, 0);
	obj3->o = ft_new_vec3(0, -2, 0);

	obj4->o = ft_new_vec3(0,-10,0);
	obj5->o = ft_new_vec3(0,6,0);

	obj->c = get_color(0xFF0000);
	obj2->c = get_color(0xFF0000);
	obj3->c = get_color(0xFF0000);
	obj4->c = get_color(0xFF0000);
	obj5->c = get_color(0xFF0000);

	obj->r = ft_new_vec3(0,0,0);
	obj2->r = ft_new_vec3(0,0,0);
	obj3->r = ft_new_vec3(0,0,0);
	obj4->r = ft_new_vec3(0,0,0);
	obj5->r = ft_new_vec3(0,0,0);

	obj->s = ft_new_vec3(1,1,1);
	obj2->s = ft_new_vec3(1,1,1);
	obj3->s = ft_new_vec3(1,1,1);
	obj4->s = ft_new_vec3(1,1,1);
	obj5->s = ft_new_vec3(1,1,1);
	world->ambient.in = 0.2;

	obj->object_union.sphere.radius = 1;
	obj2->object_union.cylinder.radius = 1;
	obj3->object_union.sphere.radius = 1;
	obj4->object_union.cylinder.radius = 1;
	obj5->object_union.sphere.radius = 1;

	t_cobject *cobj = ft_new_cobject();
	t_cobject *cobj2 = ft_new_cobject();

	cobj->s = ft_new_vec3(1,1,1);
	cobj2->s = ft_new_vec3(1,1,1);

	cobj->o = ft_new_vec3(0,0,0);
	cobj2->o = ft_new_vec3(0,0,0);

	cobj->r = ft_new_vec3(0,0,0);
	cobj2->r = ft_new_vec3(0,0,0);

	ft_add_obj_to_cobj(cobj, obj);
	ft_add_obj_to_cobj(cobj, obj2);
	ft_add_obj_to_cobj(cobj, obj3);

	ft_add_obj_to_cobj(cobj2, obj4);
	ft_add_obj_to_cobj(cobj2, obj5);

	add_cobj(&(world->cobjlist), cobj);
	//	add_cobj(&(world->cobjlist), cobj2);
	world->selected_cobject = cobj;
}

int			read_world(t_world *world, char *file)
{
	char	*line;
	int		fd;
	int		gnl_ret;
	int		pl_ret;
	t_parser parser;

	ft_init_parser(&parser);
	ft_fake_objects(world);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	line = NULL;
	while ((gnl_ret = get_next_line(fd, &line)) == 1)
	{
		if ((pl_ret = parse_line_new(line, world, &parser)))
		{
			free(line);
			close(fd);
			return (pl_ret);
		}
	}
	close(fd);
	if (gnl_ret == -1)
		return (-2);
	free(line);
	return (0);
}
