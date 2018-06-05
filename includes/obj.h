/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:50:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/27 06:44:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJ_H
# define FT_OBJ_H

typedef struct		s_material
{
	float			ambiant;
	float			diffuse;
	float			specular;
}					t_material;

typedef enum		e_enum_obj
{
	enum_obj_hashtag,
	enum_obj_v,
	enum_obj_f,
	enum_obj_s,
	enum_obj_o,
	enum_obj_g,
	enum_obj_usemtl,
	enum_obj_mtllib,
	enum_obj_vt,
	enum_obj_vn
}					t_enum_obj;

typedef struct		s_obj_parser
{
	t_list			*materials;
	t_list			*vertices_tmp;
	t_list			*faces_tmp;
	t_point3d			*vertices;
	t_ivec3			*faces;
	double			*draw_array;
	int				i;
	int				nb_vertices;
	int				nb_faces;
}					t_obj_parser;

typedef	void		(*t_obj_func)(int *, char *, t_obj_parser *);

t_obj_parser	ft_parse_obj(char *filename);
void			ft_obj_face(int *i,  char *s, t_obj_parser *parser);
void			ft_obj_vertex(int *i,  char *s, t_obj_parser *parser);
void			ft_obj_hashtag(int *i,  char *s, t_obj_parser *parser);
void			ft_print_draw_array(t_obj_parser parser);
#endif
