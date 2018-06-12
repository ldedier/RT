/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 04:57:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 02:12:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mat4  ft_mat4_inv_scale(t_mat4 scale)
{
	int i;

	i = 0;
	while (i < 15)
	{
		if (scale.as_mat[i])
			scale.as_mat[i] = 1.f / scale.as_mat[i];
		i += 5;
	}
	return scale;
}

t_mat4  ft_mat4_inv_translate(t_mat4 scale)
{
	int i;

	i = 12;
	while (i < 15)
	{
		scale.as_mat[i] *= -1;
		i++;
	}
	return scale;
}

t_aux_compute	ft_get_aux_compute_matrix(t_object *object, t_cobject *cobject)
{
	t_aux_compute x;
	x.rotate = ft_mat4_mult(ft_mat4_rotate_x(object->r.x), ft_mat4_mult(
				ft_mat4_rotate_y(object->r.y), ft_mat4_rotate_z(object->r.z)));
	x.translate = ft_mat4_translate_vec(ft_point3d_add(cobject->o, 
				ft_point3d_mult(cobject->s, object->o)));
	x.scale = ft_mat4_scale_vec(
			ft_new_vec3(object->s.x * cobject->s.x,
				object->s.y * cobject->s.y, object->s.z * cobject->s.z));
	x.scale_inv = ft_mat4_inv_scale(x.scale);
	x.translate_inv = ft_mat4_inv_translate(x.translate);
	x.rotate_inv = ft_mat4_mult(ft_mat4_rotate_z(-object->r.z),
			ft_mat4_mult(ft_mat4_rotate_y(-object->r.y),
				ft_mat4_rotate_x(-object->r.x)));
	x.rotate_inv_cobj = ft_mat4_mult(ft_mat4_rotate_z(-cobject->r.z),
			ft_mat4_mult(ft_mat4_rotate_y(-cobject->r.y),
				ft_mat4_rotate_x(-cobject->r.x)));
	x.rotate_cobj = ft_mat4_rotate_vec(cobject->r);
	x.local_translate = ft_mat4_translate_vec(ft_point3d_mult(cobject->s,
				object->o));
	x.local_translate_inv = ft_mat4_inv_translate(x.local_translate);
	return (x);
}

void	ft_compute_matrices(t_cobject *cobject)
{
	t_object *object;
	t_objlist *ptr;
	t_aux_compute x;

	ptr = cobject->objlist;
	while (ptr)
	{
		object = ptr->object;
		x = ft_get_aux_compute_matrix(object, cobject);
		object->transform_dir = ft_mat4_mult(x.rotate_cobj,
				ft_mat4_mult(x.rotate, x.scale_inv));
		object->transform_pos = ft_mat4_mult(x.translate,
			ft_mat4_mult(x.local_translate_inv, ft_mat4_mult(x.rotate_cobj,
			ft_mat4_mult(x.local_translate,ft_mat4_mult(x.rotate, x.scale)))));

		object->transform_dir_inv = ft_mat4_mult(ft_mat4_mult(x.scale_inv,
				x.rotate_inv), x.rotate_inv_cobj);
		object->transform_pos_inv = ft_mat4_mult(x.scale_inv,
			ft_mat4_mult(x.rotate_inv,ft_mat4_mult(x.local_translate_inv,
				ft_mat4_mult(x.rotate_inv_cobj,ft_mat4_mult(x.local_translate,
					x.translate_inv)))));
		ptr = ptr->next;
	}
}

void	ft_compute_matrices_clist(t_cobjlist *cobjects)
{
	t_cobject *cobject;
	while (cobjects != NULL)
	{
		cobject = (cobjects->cobject);
		ft_compute_matrices(cobject);
		cobjects = cobjects->next;
	}
}
