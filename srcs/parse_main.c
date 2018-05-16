/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 03:48:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/16 03:52:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_init_parser(t_parser *parser)
{
	parser->nb_lines = 0;
	parser->tag_stack = NULL;
	parser->attribute = NULL;
	parser->tag = NULL;
	parser->parse_enum = e_parse_scene;
	parser->got_scene = 0;
}

void			ft_check_parser(t_parser parser)
{
	if (!parser.got_scene)
	{
		ft_dprintf(2, "every config file must begin with a <scene> tag\n");
		exit(1);
	}
}

void			ft_free_parser(t_parser *parser)
{
	int		i;
	t_list	**ptr;
	t_list	*tmp;

	i = 0;
	if (parser->attribute != NULL)
		free(parser->attribute);
	if (parser->tag != NULL)
		free(parser->tag);
	ptr = &(parser->tag_stack);
	while (*ptr)
	{
		tmp = *ptr;
		free(tmp->content);
		free(tmp);
		*ptr = (*ptr)->next;
		i++;
	}
	if (i)
	{
		ft_dprintf(2, "some opening tags are not closed\n");
		exit(1);
	}
	ft_check_parser(*parser);
}

int				read_world(t_world *world, char *file)
{
	char		*line;
	int			fd;
	int			ret;
	t_parser	parser;

	ft_init_parser(&parser);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	line = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if ((ret = parse_line_new(line, world, &parser)))
		{
			free(line);
			close(fd);
			return (ret);
		}
		free(line);
	}
	ft_free_parser(&parser);
	close(fd);
	if (ret == -1)
		return (-2);
	free(line);
	return (0);
}
