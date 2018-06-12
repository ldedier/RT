/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 23:30:21 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/12 05:54:23 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		ft_process_mod(t_color color, double old, t_mod mod)
{
	int take_old;

	if (!mod.enabled)
		return (old);
	else
	{
		if (mod.color == 0xff0000)
			take_old = (mod.inequality((color.r / get_sum(color)), mod.value));
		else if (mod.color == 0x00ff00)
			take_old = (mod.inequality((color.g / get_sum(color)), mod.value));
		else
			take_old = (mod.inequality((color.b / get_sum(color)), mod.value));
		return (take_old ? mod.mod_value : old);
	}
}

void		ft_init_aux_render(t_aux_render *x, t_hit *hit)
{
	t_color color;

	color = get_color(get_object_color(hit));
	x->f_refract = ft_process_mod(color, hit->obj.refract,
			hit->obj.mod_refract);
	x->f_reflect = ft_process_mod(color, hit->obj.reflect,
			hit->obj.mod_reflect);
	x->f_transp = ft_process_mod(color, hit->obj.transp, hit->obj.mod_transp);
}

t_line		newray(t_point3d p, t_point3d vec)
{
	t_line	line;

	line.o = p;
	if (PERSPECTIVE == 1)
		line.v = (t_point3d){.x = 0, .y = 0, .z = 1};
	else if (PERSPECTIVE == 2)
		line.v = normalize(vec);
	return (line);
}

t_color		freeret_rend(t_color c, t_hit **hit, t_shadowsfree *aux)
{
	int	i;

	if (*hit)
	{
		free(*hit);
		*hit = NULL;
		i = -1;
		if (aux)
		{
			while (++i < aux->nlights)
				if (aux->shadows[i])
					free(aux->shadows[i]);
		}
	}
	return (c);
}
