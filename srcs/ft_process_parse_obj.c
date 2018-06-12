/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:10:27 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 01:33:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_process_obj_parsing(t_obj_parser *parser, char *s)
{
	if (!strcmp(s, "") || s[0] == '#')
		ft_obj_hashtag(s, parser);
	else if (!ft_strncmp("v ", s, 2))
		ft_obj_vertex(s, parser);
	else if (!ft_strncmp("f ", s, 2))
		ft_obj_face(s, parser);
	else if (!ft_strncmp("vt ", s, 3))
		ft_obj_hashtag(s, parser);
	else if (!ft_strncmp("vn ", s, 3))
		ft_obj_hashtag(s, parser);
	else if (!ft_strncmp("o ", s, 2))
		ft_obj_hashtag(s, parser);
	else if (!ft_strncmp("g ", s, 2))
		ft_obj_hashtag(s, parser);
	else if (!ft_strncmp("s ", s, 2))
		ft_obj_hashtag(s, parser);
	else if (!ft_strncmp("mtllib", s, 6))
		ft_obj_hashtag(s, parser);
	else if (!ft_strncmp("usemtl", s, 6))
		ft_obj_hashtag(s, parser);
	else
	{
		ft_printf("erreur de parsing d'obj: %s\n", s);
		exit(1);
	}
}

void			ft_convert_to_array_vertices(t_obj_parser *parser)
{
	int		i;
	t_list	*ptr;
	t_list	*tmp;

	ptr = parser->vertices_tmp;
	parser->vertices = (t_point3d *)(malloc(sizeof(t_point3d) *
		(parser->nb_vertices + 1)));
	i = 1;
	while (i <= parser->nb_vertices)
	{
		parser->vertices[i] = *(t_point3d *)(ptr->content);
		free(ptr->content);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
		i++;
	}
}

void			ft_convert_to_array_faces(t_obj_parser *parser)
{
	int			i;
	t_list		*ptr;
	t_list		*tmp;

	ptr = parser->faces_tmp;
	parser->faces = (t_ivec3 *)(malloc(sizeof(t_ivec3) * parser->nb_faces));
	i = 0;
	while (i < parser->nb_faces)
	{
		parser->faces[i] = *(t_ivec3 *)(ptr->content);
		free(ptr->content);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
		i++;
	}
}

void			ft_parse_obj_gnl(char *filename, t_obj_parser *parser)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "file %s can not be opened\n", filename);
		exit(1);
	}
	while (get_next_line(fd, &line) > 0)
	{
		ft_process_obj_parsing(parser, line);
		free(line);
	}
	free(line);
}

t_obj_parser	ft_parse_obj(char *filename)
{
	t_obj_parser parser;

	parser.nb_faces = 0;
	parser.nb_vertices = 0;
	parser.vertices_tmp = NULL;
	parser.faces_tmp = NULL;
	parser.vertices = NULL;
	parser.faces = NULL;
	ft_parse_obj_gnl(filename, &parser);
	ft_convert_to_array_vertices(&parser);
	ft_convert_to_array_faces(&parser);
	return (parser);
}
