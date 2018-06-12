/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:54:34 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 00:04:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_func(t_object *obj, void (*print_caracteristics)(t_object, int))
{
	obj->print_caracteristics = print_caracteristics;
}

void	set_funcs(t_object *obj,
		int (*intersect_func)(t_line, t_object, double[MAX_DEGREE]),
		int (*inside_func)(t_hit, t_object),
		t_point3d (*normal_func)(t_object, t_point3d, t_line))
{
	obj->intersect_func = intersect_func;
	obj->inside_func = inside_func;
	obj->normal_func = normal_func;
}
