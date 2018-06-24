/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 09:43:30 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/12 09:48:48 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_torus_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<small_radius>%f</small_radius>\n",
			obj.object_union.torus.small_rad);
	dprintf(fd, "\t\t\t\t<big_radius>%f</big_radius>\n",
			obj.object_union.torus.big_rad);
}

void	ft_print_goursat_caracteristics(t_object obj, int fd)
{
	dprintf(fd, "\t\t\t\t<goursatAB>%f %f</goursatAB>\n",
			obj.object_union.goursat.a, obj.object_union.goursat.b);
}

void	ft_print_lemniscate_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}

void	ft_print_roman_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}

void	ft_print_piriform_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}
