/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:50:13 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/09 01:13:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	cobject->pert = e_none;
	cobject->transp = 0;
	cobject->refract = 1;
	cobject->reflect = 0;
	cobject->shine = 30;
	cobject->objlist = NULL;
	cobject->negative = 0;
	cobject->regular = 1;
	cobject->name = NULL;
	cobject->defining = 0;
	return (cobject);
}

t_bmp_parser	new_bmp_parser(void)
{
	t_bmp_parser parser;

	parser.pixels = NULL;
	parser.width = -1;
	parser.height = -1;
	parser.bitmap_index = -1;
	parser.bpp = -1;
	return (parser);
}

t_object		*ft_new_object(t_cobject cobject)
{
	t_object *object;

	if (!(object = ft_memalloc(sizeof(t_object))))
		ft_error("malloc error\n");
	object->o = ft_new_vec3(0, 0, 0);
	object->r = ft_new_vec3(0, 0, 0);
	object->s = ft_new_vec3(1, 1, 1);
	object->c = get_color(cobject.c.col);
	object->transp = cobject.transp;
	object->pert = cobject.pert;
	object->refract = cobject.refract;
	object->reflect = cobject.reflect;
	object->shine = cobject.shine;
//	object->cuts = ft_lstdup(NULL);
	object->cuts = NULL;
	object->parser = new_bmp_parser();
	object->parser_normal = new_bmp_parser();
	object->negative = 0;
	object->mod_refract.enabled = 0;
	object->mod_reflect.enabled = 0;
	object->mod_transp.enabled = 0;
	return (object);
}

t_cut		*ft_new_cut(void)
{
	t_cut *cut;

	if (!(cut = ft_memalloc(sizeof(t_cut))))
		return (NULL);
	cut->value = 0;
	cut->cut_xyz = ft_new_vec3(1, 0, 0);
	cut->relative = 1;
	cut->circular = 0;
	cut->color = 0;
	cut->inequality = less_than;
	return (cut);
}

t_mod		ft_new_mod(void)
{
	t_mod res;

	res.enabled = 1;
	res.color = 0;
	res.inequality = bigger_than;
	res.value = 0.5;
	res.mod_value = 0.5;
	return (res);
}

void			ft_init_light(t_light *light)
{
	light->o = ft_new_vec3(0, 0, 0);
	light->v = ft_new_vec3(0, 1, 0);
	light->c = get_color(0xFFFFFF);
	light->intensity = 1;
	light->angle = M_PI / 4;
	light->ebloui = 0;
}
