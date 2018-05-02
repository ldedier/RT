/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 21:04:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/02 19:05:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTS_H
# define FT_OBJECTS_H

typedef struct		s_sphere
{
	double			radius;
}					t_sphere;

typedef struct		s_cone
{
	double			angle;
}					t_cone;

typedef struct		s_plane
{
}					t_plane;

typedef struct		s_cylinder
{
	double			radius;
}					t_cylinder;
#endif
