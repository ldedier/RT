/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 17:09:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/09 07:27:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_H
# define FT_EXPORT_H
#include <stdio.h> // TO DELL
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

typedef struct	s_image
{
	int			width;
	int			height;
	int			*pix;
}				t_image;

typedef struct	s_video
{
	int			width;
	int			height;
	t_list		*images;
}				t_video;

typedef struct	s_argb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}				t_argb;

typedef union	u_color_l
{
	int			value;
	t_argb		argb;
}				t_color_l;			

typedef struct	s_rgb_to_y_cb_cr
{
	double		r;
	double		g;
	double		b;
}				t_rgb_to_y_cb_cr;

char 			*ft_get_name(char *extension);
t_image 		ft_new_image(int width, int height, int *pixels);
int	 			ft_export_bmp(char *name, t_image image);
int	 			ft_export_ppm(char *name, t_image image);
int				ft_export(t_image image, char *extension);
int				ft_export_y4m(t_video *video);
#endif
