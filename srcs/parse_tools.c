/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:50:13 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/16 16:25:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				read_hex(char **line, int *to)
{
	int scss;

	scss = 1;
	*to = ft_patoi_hex(line, &scss);
	return (scss);
}

int				read_double(char **line, double *to)
{
	int scss;

	scss = 1;
	*to = ft_patof(line, &scss);
	return (scss);
}

t_cobject		*ft_new_cobject(void)
{
	t_cobject *cobject;

	if (!(cobject = ft_memalloc(sizeof(t_cobject))))
		return (NULL);
	cobject->objlist = NULL;
	cobject->o = ft_new_vec3(0, 0, 0);
	cobject->r = ft_new_vec3(0, 0, 0);
	cobject->s = ft_new_vec3(1, 1, 1);
	cobject->c = get_color(0xFFFFFF);
	cobject->transp = 0;
	cobject->refract = 0;
	cobject->reflect = 0.1;
	cobject->shine = 0;
	cobject->objlist = NULL;
	return (cobject);
}

t_object		*ft_new_object(t_cobject cobject)
{
	t_object *object;

	if (!(object = ft_memalloc(sizeof(t_object))))
		return (NULL);
	object->o = ft_new_vec3(0, 0, 0);
	object->r = ft_new_vec3(0, 0, 0);
	object->s = ft_new_vec3(1, 1, 1);
	object->c = get_color(cobject.c.col);
	object->transp = cobject.transp;
	object->refract = cobject.refract;
	object->reflect = cobject.reflect;
	object->shine = cobject.shine;
	return (object);
}

void			ft_init_light(t_light *light)
{
	light->o = ft_new_vec3(0, 0, 0);
	light->v = ft_new_vec3(0, 1, 0);
	light->c = get_color(0xFFFFFF);
	light->intensity = 1;
	light->angle = M_PI / 4;
}
