/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 17:09:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/08 18:43:12 by ldedier          ###   ########.fr       */
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

char 			*ft_get_name(char *extension);
t_image 		ft_new_image(int width, int height, int *pixels);
int	 			ft_export_bmp(char *name, t_image image);
int	 			ft_export_ppm(char *name, t_image image);
int				ft_export(t_image image, char *extension);
#endif
