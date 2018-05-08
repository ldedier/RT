/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/08 00:49:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_point3d	reflection(t_point3d n, t_point3d v)
{
	t_point3d	r;
	double		aux;

	aux = 2 * dotprod(v, n);
	r.x = v.x - n.x * aux;
	r.y = v.y - n.y * aux;
	r.z = v.z - n.z * aux;
	return (r);
}

t_hit				*retfree(int r, t_hit **hit)
{
	if (!r)
	{
		free(*hit);
		*hit = NULL;
	}
	return (*hit);
}

void				ft_transform_line(t_line *line, t_object object, t_line t)
{
	(void)t;
	line->o = ft_point3d_mat4_mult(line->o, object.transform_pos_inv);
	line->v = normalize(ft_point3d_mat4_mult(line->v,
				object.transform_dir_inv));
}

void				ft_transform_hit_back(t_hit *hit)
{
	t_hit tmp;
	tmp = *hit;
	hit->point = ft_point3d_mat4_mult(tmp.point, tmp.obj.transform_pos);
	hit->normal = normalize(ft_point3d_mat4_mult(tmp.normal, tmp.obj.transform_dir));
}

t_hit				*trace(t_line line, t_objlist *objlist, int bounce)
{
	t_hit		newhit;
	t_object	obj;
	t_hit		*hit;
	static int i = 0;
	//static int k;	
	hit = malloc(sizeof(t_hit));
	hit->t = -1;
	t_line tmp = line;
	while (objlist)
	{
		obj = *(objlist->object);
		line = tmp;
		ft_transform_line(&line, obj, tmp);
		if (obj.intersect_func(line, obj, &newhit) && (newhit.t < hit->t || (hit->t == -1 && newhit.t > 0)))
		{
				newhit.obj = obj;
				ft_transform_hit_back(&newhit);
			//	if (bounce == 1000)
			//	{
			//		//	printf("OKOKOK %d\n", k++);
			//	}
				*hit = newhit;
				//hit->normal = hit->obj.normal_func(hit->obj, hit->point);
				hit->bounce = reflection(hit->normal, tmp.v);
		}
		objlist = objlist->next;
	}
	if (hit->t > 0)
	{
		if (bounce == 1000)
		{
			if(hit->obj.intersect_func == intersect_sphere)
				printf("SPHERE %d\n", i++);
			else
				printf("PLANE %d\n", i++);
			
					printf("normal \n");
					ft_print_point3d(hit->normal);
					printf("point \n");
					ft_print_point3d(hit->point);
					printf("t: %f\n", hit->t);
					printf("bounce \n");
					ft_print_point3d(hit->bounce);
					printf("\n\n\n");
					printf("line o\n");
					ft_print_point3d(line.o);
					printf("line v\n");
					ft_print_point3d(line.v);

					printf("line o tmp\n");
					ft_print_point3d(tmp.o);
					printf("line v tmp\n");
					ft_print_point3d(tmp.v);

					printf("NORMAL\n");
					ft_print_point3d(hit->normal);
		}
		return (retfree(1, &hit));
	}
	return (retfree(0, &hit));
}

/*
t_hit				*trace(t_line line, t_objlist *objlist, int bounce)
{
	t_hit		newhit;
	t_object	obj;
	t_hit		*hit;
	t_line	tmp;
	int intersect;

	intersect = 0;
	hit = malloc(sizeof(t_hit));
	hit->point = translate_vec(line.o, line.v, -EPSILON);
	hit->t = -1;
	tmp = line;
	while (objlist)
	{
		obj = *(objlist->object);
	//	ft_transform_line(&line, obj, tmp);
		if (obj.intersect_func(line, obj, &newhit) && (newhit.t < hit->t || (
				newhit.t > 0 &&  hit->t < 0)))
		{

			intersect = 1;
			*hit = newhit;
		//	hit->point = newhit;
			hit->obj = *(objlist->object);
		//	hit->normal = hit->obj.normal_func(hit->obj, hit->point);
//			printf("AVANT LA TRANSFO\n");
//			ft_print_point3d(hit->point);
		//	ft_transform_hit_back(hit);
		//
		if (bounce > 0)
			ft_print_point3d(hit->normal);
			hit->bounce = reflection(hit->normal, tmp.v);
		//			printf("APRES LA TRANSFO\n");
//			ft_print_point3d(hit->point);
//			exit(0);
		}
		objlist = objlist->next;
	}
	if (intersect)
	{
		return (retfree(1, &hit));
	}
//	if (bounce > 0)
//		printf("Pas d'intersection !\n");

	return (retfree(0, &hit));
}
*/
