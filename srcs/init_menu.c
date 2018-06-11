/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 05:30:42 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/11 05:32:23 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_positions_5(t_world *world)
{
	world->menu.lights_rb[2] = ft_new_rangebar(0, 2,
			ft_new_pixel(world->canvas->win.w + 287, 630),
			&(world->lights[world->menu.active_light].v.x));
	world->menu.lights_rb[3] = ft_new_rangebar(0, 2,
			ft_new_pixel(world->canvas->win.w + 287, 665),
			&(world->lights[world->menu.active_light].v.y));
	world->menu.lights_rb[4] = ft_new_rangebar(0, 2,
			ft_new_pixel(world->canvas->win.w + 287, 700),
			&(world->lights[world->menu.active_light].v.z));
	world->menu.nb_lights_cp = 1;
	world->menu.lights_cp[0] =
		ft_new_colorpicker(ft_new_pixel(world->canvas->win.w + 111, 615),
				ft_color_pos(world, world->lights[world->menu.active_light].c),
				&(world->lights[world->menu.active_light].c));
}

void	set_positions_4(t_world *world)
{
	int			i;

	world->menu.active_light = 0;
	world->menu.first_light.x = 0;
	world->menu.first_light.y = 145;
	world->menu.nb_lights_rb = 5;
	world->menu.lights_rb[0] = ft_new_rangebar(0, M_PI / 2,
			ft_new_pixel(world->canvas->win.w + 210, 518),
			&(world->lights[world->menu.active_light].angle));
	world->menu.lights_rb[1] = ft_new_rangebar(0, 1,
			ft_new_pixel(world->canvas->win.w + 107, 580),
			&(world->lights[world->menu.active_light].intensity));
	i = 0;
	while (i < world->nlights)
	{
		world->lights[i].v = normalize(world->lights[i].v);
		i++;
	}
}

void	set_positions_3(t_world *world)
{
	world->menu.nb_others_cp = 2;
	world->menu.others_cp[0] =
	ft_new_colorpicker(ft_new_pixel(world->canvas->win.w + 95, 250),
			ft_color_pos(world, world->ambient.color), &(world->ambient.color));
	world->menu.others_cp[1] =
	ft_new_colorpicker(ft_new_pixel(world->canvas->win.w + 295, 250),
			ft_color_pos(world, world->fog.color), &(world->fog.color));
	world->menu.scroll_lights = ft_new_scrollbar(world, 265, 0);
	if (world->nlights > 0)
	{
		set_positions_4(world);
		set_positions_5(world);
	}
	else
	{
		world->menu.active_light = -1;
		world->menu.first_light.x = -1;
		world->menu.first_light.y = -1;
		world->menu.nb_lights_rb = 0;
		world->menu.nb_lights_cp = 0;
	}
	if (world->nlights <= 4)
		world->menu.nb_lights = world->nlights;
	else
		world->menu.nb_lights = 4;
}

void	set_positions_2(t_world *world)
{
	int			i;
	int			j;

	if (world->filters[0] == 1)
		world->menu.filters_list[0] = 0;
	else if (world->filters[1] == 1)
		world->menu.filters_list[0] = 1;
	else if (world->filters[2] == 1)
		world->menu.filters_list[0] = 2;
	else if (world->filters[3] == 1)
		world->menu.filters_list[0] = 3;
	else if (world->filters[4] == 1)
		world->menu.filters_list[0] = 4;
	else if (world->filters[5] == 1)
		world->menu.filters_list[0] = 5;
	else
		world->menu.filters_list[0] = 6;
	i = 0;
	j = 1;
	while (j < (e_nfilters + 1))
	{
		if (world->menu.filters_list[0] != i)
			world->menu.filters_list[j++] = i;
		i++;
	}
}

void	set_positions(t_world *world)
{
	t_cobjlist	*lst;

	ft_cobjlist_reverse(&(world->cobjlist));
	lst = world->cobjlist;
	while (lst != NULL)
	{
		ft_objlist_reverse(&(lst->cobject->objlist));
		lst = lst->next;
	}
	init_video(world, &(world->video));
	world->menu.others_rb[0] = ft_new_rangebar(0, 1,
			ft_new_pixel(world->canvas->win.w + 95, 220), &(world->ambient.in));
	world->menu.others_rb[1] = ft_new_rangebar(0, 0.7,
			ft_new_pixel(world->canvas->win.w + 295, 220), &(world->fog.in));
	world->menu.others_grb[0] = ft_new_grangebar(0, 10,
			ft_new_pixel(world->canvas->win.w + 97, 505), &(world->max_bounce));
	world->menu.others_grb[1] = ft_new_grangebar(1, 4,
		ft_new_pixel(world->canvas->win.w + 297, 505), &(world->aa_sq_size));
	world->menu.filters = ft_new_dropdown(ft_new_pixel(world->canvas->win.w
				+ 239, 383), ft_new_pixel(195, 34));
	world->menu.filter_active = 0;
	set_positions_2(world);
	ft_color_map(world);
	set_positions_3(world);
	set_positions_6(world);
}
