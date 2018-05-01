/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 03:33:38 by lcavalle          #+#    #+#             */
/*   Updated: 2017/12/10 19:39:10 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 512

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

typedef struct	s_file
{
	int		fd;
	char	buff[BUFF_SIZE + 1];
	int		off;
	int		ret;
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
