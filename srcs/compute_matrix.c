/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 04:57:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/10 00:49:33 by ldedier          ###   ########.fr       */
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

void	ft_compute_matrix(t_object *object)
{
//	object->s = ft_new_vec3(1,1,1);
//	object->r = ft_new_vec3(0, 0, 0);

	t_mat4 rotate = ft_mat4_mult(ft_mat4_rotate_x(object->r.x), ft_mat4_mult(ft_mat4_rotate_y(object->r.y), ft_mat4_rotate_z(object->r.z)));
	// ft_printf("rotate\n");
	// ft_print_mat4(rotate);

	t_mat4 translate = ft_mat4_translate_vec(object->o);
	// ft_printf("translate\n");
	// ft_print_mat4(translate);
	t_mat4 scale = ft_mat4_scale_vec(object->s);
	// ft_printf("scale\n");
	// ft_print_mat4(scale);

	t_mat4 transform = ft_mat4_model_view_matrix_mat(translate, rotate, scale);

	// ft_printf("TRANSFORM\n");
	// ft_print_mat4(transform);

	t_mat4 scale2 = ft_mat4_inv_scale(scale);
	t_mat4 translate2 = ft_mat4_inv_translate(translate);
	t_mat4 rotate2 = ft_mat4_mult(ft_mat4_rotate_z(-object->r.z), ft_mat4_mult(ft_mat4_rotate_y(-object->r.y), ft_mat4_rotate_x(-object->r.x)));

	// ft_printf("rotate inv\n");
	// ft_print_mat4(rotate2);

	// ft_printf("translate inv\n");
	// ft_print_mat4(translate2);

	// ft_printf("scale inv\n");
	// ft_print_mat4(scale2);

	// ft_printf("IDENTITIES\n");
	// ft_print_mat4(ft_mat4_mult(rotate, rotate2));
	// ft_print_mat4(ft_mat4_mult(scale, scale2));
	// ft_print_mat4(ft_mat4_mult(translate, translate2));

	t_mat4 invtransform = ft_mat4_model_view_matrix_mat(scale2, rotate2, translate2);

	// ft_printf("TRANSFORM\n");
	// ft_print_mat4(transform);

	// ft_printf("INVERSE POS\n");
	// ft_print_mat4(invtransform);

	// ft_printf("TRANSFORM * INVERSE\n");
	// ft_print_mat4(ft_mat4_mult(invtransform, transform));

	t_mat4 transform_dir = ft_mat4_mult(rotate, scale2);
	t_mat4 transform_dir_inv = ft_mat4_mult(scale2, rotate2);

	// ft_printf("INVERSE DIR \n");
	// ft_print_mat4(transform_dir_inv);

	// ft_printf("TRANSORM DIR \n");
	// ft_print_mat4(transform_dir);
	
	// ft_printf("TRANSFORM * INVERSE\n");
	// ft_print_mat4(ft_mat4_mult(transform_dir_inv, transform_dir));

	object->transform_pos = transform;
	object->transform_dir = transform_dir;

	object->transform_pos_inv = invtransform;
	object->transform_dir_inv = transform_dir_inv;
}

void	ft_compute_matrices_list(t_objlist *objects)
{
	t_object *object;

	while (objects != NULL)
	{
		object = (objects->object);
		ft_compute_matrix(object);
		objects = objects->next;
	}
}
