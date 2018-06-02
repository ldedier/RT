/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_y4m.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:10:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/02 07:18:54 by ldedier          ###   ########.fr       */
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

//	y = (int)(0.299 * color.argb.r + 0.587 * color.argb.g + 0.114 * color.argb.b);
//	cb = (int)(-0.16874 * color.argb.r - 0.33126 * color.argb.g  + 0.5 * color.argb.b + 128);
//	cr = (int)(0.5 * color.argb.r - 0.41869 * color.argb.g - 0.08131 * color.argb.b + 128);



// 	y = 0.257 * color.argb.r + 0.504* color.argb.g + 0.098 * color.argb.b + 16;
//	cb = -0.148 * color.argb.r - 0.291 * color.argb.g + 0.439 * color.argb.b + 128;
//	cr = 0.439 * color.argb.r - 0.368 * color.argb.g - 0.071 * color.argb.b + 128;

	y = 16 + (65.481 * t.r + 128.553 * t.g  + 24.966 * t.b);
	cb = 128 + (-37.797 * t.r - 74.203 * t.g  + 112.0 * t.b);
	cr = 128 + (112.0 * t.r - 93.786 * t.g - 18.214 * t.b);
//	printf("red: %d\n",(int)(y + 1.402* (cr - 128)));
//	printf("green: %d\n",(int)(y - 0.34414* (cb - 128) - 0.71414 * (cr - 128)));
//	printf("blue: %d\n",(int)(y + 1.772 *(cb - 128)));
//	exit(1);

	if(cb < 0 || cb > 255 || cr < 0 || cr > 255 || y < 0 || y > 255 )
		exit(1);
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

//	y = (int)(0.299 * color.argb.r + 0.587 * color.argb.g + 0.114 * color.argb.b);
//	cb = (int)(-0.16874 * color.argb.r - 0.33126 * color.argb.g  + 0.5 * color.argb.b + 128);
//	cr = (int)(0.5 * color.argb.r - 0.41869 * color.argb.g - 0.08131 * color.argb.b + 128);



// 	y = 0.257 * color.argb.r + 0.504* color.argb.g + 0.098 * color.argb.b + 16;
//	cb = -0.148 * color.argb.r - 0.291 * color.argb.g + 0.439 * color.argb.b + 128;
//	cr = 0.439 * color.argb.r - 0.368 * color.argb.g - 0.071 * color.argb.b + 128;

	y = 16 + (65.481 * t.r + 128.553 * t.g  + 24.966 * t.b);
	cb = 128 + (-37.797 * t.r - 74.203 * t.g  + 112.0 * t.b);
	cr = 128 + (112.0 * t.r - 93.786 * t.g - 18.214 * t.b);
//	printf("red: %d\n",(int)(y + 1.402* (cr - 128)));
//	printf("green: %d\n",(int)(y - 0.34414* (cb - 128) - 0.71414 * (cr - 128)));
//	printf("blue: %d\n",(int)(y + 1.772 *(cb - 128)));
//	exit(1);

	if(cb < 0 || cb > 255 || cr < 0 || cr > 255 || y < 0 || y > 255 )
		exit(1);
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

//	y = (int)(0.299 * color.argb.r + 0.587 * color.argb.g + 0.114 * color.argb.b);
//	cb = (int)(-0.16874 * color.argb.r - 0.33126 * color.argb.g  + 0.5 * color.argb.b + 128);
//	cr = (int)(0.5 * color.argb.r - 0.41869 * color.argb.g - 0.08131 * color.argb.b + 128);



// 	y = 0.257 * color.argb.r + 0.504* color.argb.g + 0.098 * color.argb.b + 16;
//	cb = -0.148 * color.argb.r - 0.291 * color.argb.g + 0.439 * color.argb.b + 128;
//	cr = 0.439 * color.argb.r - 0.368 * color.argb.g - 0.071 * color.argb.b + 128;

	y = 16 + (65.481 * t.r + 128.553 * t.g  + 24.966 * t.b);
	cb = 128 + (-37.797 * t.r - 74.203 * t.g  + 112.0 * t.b);
	cr = 128 + (112.0 * t.r - 93.786 * t.g - 18.214 * t.b);
//	printf("red: %d\n",(int)(y + 1.402* (cr - 128)));
//	printf("green: %d\n",(int)(y - 0.34414* (cb - 128) - 0.71414 * (cr - 128)));
//	printf("blue: %d\n",(int)(y + 1.772 *(cb - 128)));
//	exit(1);

	if(cb < 0 || cb > 255 || cr < 0 || cr > 255 || y < 0 || y > 255 )
		exit(1);
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

void	ft_print_frames(t_video video, int fd)
{
	t_list *ptr;

	ptr = video.images;
	while (ptr)
	{
		ft_dprintf(fd,"FRAME\n");
		ft_print_frame((int *)(ptr->content), video.width * video.height, fd);
		ptr = ptr->next;
	}
}

int		ft_export_y4m(t_video video)
{
	char *name;
	int fd;

	(void) video;
//	ft_print_pixel_rgb_to_y_cb_cr(0x00FF00, 1);
	name = ft_get_name(".y4m");
	if ((fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
		return (-1);
	ft_dprintf(fd, "YUV4MPEG2 W%d H%d F10:1 C444\n", video.width,
					video.height);
	ft_print_frames(video, fd);
	close(fd);
	return (0);
}
