/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 02:57:41 by lcavalle          #+#    #+#             */
/*   Updated: 2018/04/13 09:29:02 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*getcontent(int fd, t_list **list)
{
	t_file	*file;
	t_list	*aux;

	aux = *list;
	while (aux && ((t_file *)aux->content)->fd != fd)
		aux = aux->next;
	if (!aux)
	{
		if (!(file = malloc(sizeof(t_file))))
			return (NULL);
		file->fd = fd;
		file->buff[BUFF_SIZE] = '\0';
		file->off = BUFF_SIZE;
		file->ret = -1;
		ft_lstadd(list, ft_lstnew((void *)file, sizeof(t_file)));
		free(file);
		return ((*list)->content);
	}
	else
		return (aux->content);
}

int		remove_file(int fd, t_list **files)
{
	t_list	*aux;
	t_list	*prev;

	prev = NULL;
	aux = *files;
	while (aux && ((t_file *)aux->content)->fd != fd)
	{
		prev = aux;
		aux = aux->next;
	}
	if (aux == *files)
		*files = (*files)->next;
	else
		prev->next = aux->next;
	free((t_file *)aux->content);
	free(aux);
	aux = NULL;
	return (0);
}

void	joincat(t_file *file, char **line, int offset)
{
	char	*aux;
	char	*tmp;

	aux = *line;
	tmp = ft_strndup(file->buff + file->off, offset);
	*line = ft_strjoin(aux, tmp);
	ft_strdel(&tmp);
	ft_strdel(&aux);
}

void	read_buff(t_file *file, char **line, int offset, int end_line)
{
	joincat(file, line, offset);
	if (!end_line)
	{
		file->ret = read(file->fd, &(file->buff), BUFF_SIZE);
		file->buff[file->ret] = '\0';
		file->off = 0;
	}
	else
	{
		if (ft_strchr(*line, '\n'))
			*(ft_strchr(*line, '\n')) = '\0';
		file->off += offset + 1;
		if (file->off == file->ret)
		{
			file->off = 0;
			file->ret = read(file->fd, &(file->buff), BUFF_SIZE);
			file->buff[file->ret] = '\0';
		}
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*files = NULL;
	t_file			*file;
	int				newoff;

	file = (t_file *)getcontent(fd, &files);
	if (!line || fd < 0 || read(fd, &(file->buff), 0) == -1 || fd > OPEN_MAX)
		return (-1);
	*line = ft_strnew(0);
	if (file->ret == -1)
		read_buff(file, line, 0, 0);
	newoff = ft_strchri(file->buff + file->off, '\n');
	if (file->ret == 0)
		return (remove_file(file->fd, &files));
	while (file->off + newoff == file->ret)
	{
		read_buff(file, line, newoff, 0);
		if (file->ret == 0)
			return (1);
		newoff = ft_strchri(file->buff + file->off, '\n');
	}
	read_buff(file, line, newoff, 1);
	return (1);
}
