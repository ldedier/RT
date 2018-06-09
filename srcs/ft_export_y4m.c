/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_y4m.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:10:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/09 07:46:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_print_pixel_rgb_to_y_cb_cr(int pixel, int fd)
{
	t_color_l color;
	t_rgb_to_y_cb_cr t;
	int y;
	int cb;
	int cr;
	
	color.value = pixel;
	t.r = color.argb.r / 255.0;
	t.g = color.argb.g / 255.0;
	t.b = color.argb.b / 255.0;
	y = 16 + (65.481 * t.r + 128.553 * t.g  + 24.966 * t.b);
	cb = 128 + (-37.797 * t.r - 74.203 * t.g  + 112.0 * t.b);
	cr = 128 + (112.0 * t.r - 93.786 * t.g - 18.214 * t.b);
	ft_dprintf(fd, "%c", y);
}
void	ft_print_pixel_rgb_to_y_cb_cr1(int pixel, int fd)
{
	t_color_l color;
	t_rgb_to_y_cb_cr t;
	int y;
	int cb;
	int cr;

	color.value = pixel;
	t.r = color.argb.r / 255.0;
	t.g = color.argb.g / 255.0;
	t.b = color.argb.b / 255.0;
	y = 16 + (65.481 * t.r + 128.553 * t.g  + 24.966 * t.b);
	cb = 128 + (-37.797 * t.r - 74.203 * t.g  + 112.0 * t.b);
	cr = 128 + (112.0 * t.r - 93.786 * t.g - 18.214 * t.b);
	ft_dprintf(fd, "%c", cb);
}

void	ft_print_pixel_rgb_to_y_cb_cr2(int pixel, int fd)
{
	t_color_l color;
	t_rgb_to_y_cb_cr t;
	int y;
	int cb;
	int cr;

	color.value = pixel;
	t.r = color.argb.r / 255.0;
	t.g = color.argb.g / 255.0;
	t.b = color.argb.b / 255.0;
	y = 16 + (65.481 * t.r + 128.553 * t.g  + 24.966 * t.b);
	cb = 128 + (-37.797 * t.r - 74.203 * t.g  + 112.0 * t.b);
	cr = 128 + (112.0 * t.r - 93.786 * t.g - 18.214 * t.b);
	ft_dprintf(fd, "%c", cr);
}

void	ft_print_frame(int *frame, int length, int fd)
{
	int i;

	i = 0;
	while (i < length)
	{
		ft_print_pixel_rgb_to_y_cb_cr(frame[i], fd);
		i++;
	}
	i = 0;
	while (i < length)
	{
		ft_print_pixel_rgb_to_y_cb_cr1(frame[i], fd);
		i++;
	}
	i = 0;
	while (i < length)
	{
		ft_print_pixel_rgb_to_y_cb_cr2(frame[i], fd);
		i++;
	}
}

void	ft_print_frames(t_video *video, t_list **list, int fd)
{
	t_list *tmp;

	while (*list)
	{
		ft_dprintf(fd, "FRAME\n");
		ft_print_frame((int *)((*list)->content), video->width * video->height, fd);
		tmp = *list;
		*list = (*list)->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
}

int		ft_export_y4m(t_video *video)
{
	char *name;
	int fd;

	name = ft_get_name(".y4m");
	if ((fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
		return (-1);
	ft_dprintf(fd, "YUV4MPEG2 W%d H%d F10:1 C444\n", video->width,
			video->height);
	ft_print_frames(video, &(video->images), fd);
	free(name);
	close(fd);
	return (0);
}
