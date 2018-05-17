/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 04:57:37 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/17 04:46:05 by ldedier          ###   ########.fr       */
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

void	ft_compute_matrices(t_cobject *cobject)
{
	t_object *object;
	t_objlist *ptr;

	ptr = cobject->objlist;
	print_cobject(*cobject);
	while (ptr)
	{

	//	t_mat4 pivot = ft_mat4_translate_vec(cobject->o);
	//	t_mat4 pivot = ft_mat4_translate_vec(cobject->o);
		
		object = ptr->object;
		t_mat4 rotate = ft_mat4_mult(ft_mat4_rotate_x(object->r.x), ft_mat4_mult(ft_mat4_rotate_y(object->r.y), ft_mat4_rotate_z(object->r.z)));
		// ft_printf("rotate\n");
		// ft_print_mat4(rotate);
		
		t_mat4 translate = ft_mat4_translate_vec(ft_point3d_add(cobject->o,  ft_point3d_mult(cobject->s, object->o)));
		// ft_printf("translate\n");
		// ft_print_mat4(translate);
		t_mat4 scale = ft_mat4_scale_vec(
				ft_new_vec3(object->s.x * cobject->s.x,
					object->s.y * cobject->s.y, object->s.z * cobject->s.z));
		// ft_printf("scale\n");
		// ft_print_mat4(scale);

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

	//	transform = ft_mat4_mult(ft_mat4_rotate_vec(cobject->r), transform);
	//	invtransform = ft_mat4_mult(invtransform, ft_mat4_mult(ft_mat4_rotate_z(-cobject->r.z), ft_mat4_mult(ft_mat4_rotate_y(-cobject->r.y), ft_mat4_rotate_x(-cobject->r.x))));
		// ft_printf("TRANSFORM\n");
		// ft_print_mat4(transform);

		// ft_printf("INVERSE POS\n");
		// ft_print_mat4(invtransform);

	// ft_printf("TRANSFORM * INVERSE\n");
	// ft_print_mat4(ft_mat4_mult(invtransform, transform));
		t_mat4 rotate_inv_cobj = ft_mat4_mult(ft_mat4_rotate_z(-cobject->r.z), ft_mat4_mult(ft_mat4_rotate_y(-cobject->r.y), ft_mat4_rotate_x(-cobject->r.x)));
		t_mat4 rotate_cobj = ft_mat4_rotate_vec(cobject->r);
		//	ft_print_mat4(ft_mat4_mult(rotate_inv_cobj, rotate_obj));

		t_mat4 local_translate = ft_mat4_translate_vec(ft_point3d_mult(cobject->s, object->o));
		t_mat4 local_translate_inv = ft_mat4_inv_translate(local_translate);
		
		t_mat4 invpivot = ft_mat4_mult(local_translate, ft_mat4_mult(rotate_inv_cobj, local_translate_inv));
	//	t_mat4 invpivot = ft_mat4_mult(local_translate, rotate_inv_cobj);
		
		(void)invpivot;	
		t_mat4 transform_dir = ft_mat4_mult(rotate_cobj, ft_mat4_mult(rotate, scale2));
//		t_mat4 transform_dir =  ft_mat4_mult(rotate, scale2);
		
		t_mat4 transform = ft_mat4_mult(translate, ft_mat4_mult(local_translate_inv, ft_mat4_mult( rotate_cobj, ft_mat4_mult(local_translate,ft_mat4_mult(rotate, scale)))));

	// OUAAAAAI	
	
		t_mat4 transform_dir_inv = ft_mat4_mult(ft_mat4_mult(scale2, rotate2), rotate_inv_cobj);
		t_mat4 invtransform = ft_mat4_mult(scale2, ft_mat4_mult(rotate2,ft_mat4_mult(local_translate_inv,  ft_mat4_mult(rotate_inv_cobj,ft_mat4_mult(local_translate, translate2)))));
	
	//END OUAI
	
//		invtransform = ft_mat4_mult(invtransform, invpivot);
		// ft_printf("INVERSE DIR \n");
		// ft_print_mat4(transform_dir_inv);

		// ft_printf("TRANSORM DIR \n");
		// ft_print_mat4(transform_dir);

		object->transform_pos = transform;
		object->transform_dir = transform_dir;

		object->transform_pos_inv = invtransform;
		object->transform_dir_inv = transform_dir_inv;

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
