/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_obj_faces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 18:45:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/27 06:35:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_obj_hashtag(int *i, char *s, t_obj_parser *parser)
{
	(void)parser;
	while (s[*i] != '\0' && s[*i] != '\n')
		*i += 1;
}

void	ft_obj_add_index(int *i, char *s , int *index)
{
	*index = 0;
	while (!ft_isdigit(s[*i]) && s[*i] != '\n' && s[*i] != '\0')
		*i += 1;
	while (ft_isdigit(s[*i]))
	{
		*index = *index * 10 + s[*i] - '0';
		*i += 1;
	}
}

int	ft_obj_add_index_fourth(int *i, char *s , int *index)
{
	*index = 0;
	while (!ft_isdigit(s[*i]) && s[*i] != '\n' && s[*i] != '\0')
		*i += 1;
	if (!ft_isdigit(s[*i]))
		return (0);
	while (ft_isdigit(s[*i]))
	{
		*index = *index * 10 + s[*i] - '0';
		*i += 1;
	}
	return (1);
}

void	ft_obj_face(int *i, char *s, t_obj_parser *parser)
{
	t_ivec3 face;
	int z_tmp;

	ft_obj_add_index(i, s, &(face.x));
	ft_obj_add_index(i, s, &(face.y));
	ft_obj_add_index(i, s, &(face.z));

	ft_lstpushback(&(parser->faces_tmp), ft_lstnew(&face, sizeof(t_ivec3)));
	parser->nb_faces++;
	z_tmp = face.z;
	while (ft_obj_add_index_fourth(i, s, &(face.z)))
	{
		face.y = z_tmp;
		ft_lstpushback(&(parser->faces_tmp), ft_lstnew(&face, sizeof(t_ivec3)));
		parser->nb_faces++;
		z_tmp = face.z;
	}
	while (s[*i] != '\0' && s[*i] != '\n')
		*i += 1;
}
