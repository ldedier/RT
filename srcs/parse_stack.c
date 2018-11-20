/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:10:29 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/12 18:15:00 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_lol(char *line, t_parser *parser, int *i)
{
	int		start;
	int		length;

	start = *i;
	while (line[*i] && (line[*i] != ' ' && line[*i] != '>'))
		*i += 1;
	length = *i - start;
	if (parser->tag != NULL)
		free(parser->tag);
	parser->tag = ft_strndup(&(line[start]), length);
	if (line[*i] == ' ')
	{
		while (line[*i] && line[*i] != '"')
			*i += 1;
		*i += 1;
		start = *i;
		while (line[*i] && line[*i] != '"')
			*i += 1;
		length = *i - start;
		if (parser->attribute != NULL)
			free(parser->attribute);
		parser->attribute = ft_strndup(&(line[start]), length);
		parser->got_attribute = 1;
	}
}

int			ft_parse_tag(char **line, t_parser *parser)
{
	int		i;
	char	*str;
	int		ret;

	ret = -1;
	str = *line;
	i = 0;
	while (str[i] && str[i] != '<')
		i++;
	if (str[i])
	{
		ret = STACK;
		i++;
		if (str[i] == '/')
		{
			i++;
			ret = POP;
		}
		ft_lol(*line, parser, &i);
	}
	*(line) += i + 1;
	return (ret);
}

void		ft_add_tag_stack(t_parser *parser)
{
	t_tag *xml_tag;

	if (!(xml_tag = malloc(sizeof(t_tag))))
		ft_error("error malloc");
	xml_tag->tag = ft_strdup(parser->tag);
	xml_tag->has_attribute = parser->got_attribute;
	ft_lstadd(&(parser->tag_stack), ft_lstnew_ptr(xml_tag, sizeof(t_tag)));
	if (parser->got_attribute)
	{
		ft_lstadd(&(parser->attribute_stack),
				ft_lstnew(parser->attribute, sizeof(char) *
					ft_strlen(parser->attribute) + 1));
	}
	parser->got_attribute = 0;
}

void		ft_process_tag_stack_stack(t_parser *parser)
{
	if (!parser->got_scene)
	{
		if (!ft_strcmp("scene", parser->tag))
			parser->got_scene = 1;
		else
		{
			ft_dprintf(
					2, "every config file must begin with a <scene> tag\n");
			exit(1);
		}
	}
	ft_add_tag_stack(parser);
}

void		ft_process_tag_pop(t_parser *parser)
{
	t_tag	*xml_tag;

	xml_tag = (t_tag *)(ft_lstpop(&(parser->tag_stack)));
	if (xml_tag == NULL)
	{
		ft_dprintf(2, "line %d: no corresponding opening tag for %s\n",
				parser->nb_lines, parser->tag);
		exit(1);
	}
	else if (ft_strcmp(parser->tag, xml_tag->tag))
	{
		ft_dprintf(2, "line %d: expected ending tag %s instead of %s\n",
				parser->nb_lines, xml_tag->tag, parser->tag);
		exit(1);
	}
	if (xml_tag->has_attribute)
	{
		free(ft_lstpop(&(parser->attribute_stack)));
		if (parser->attribute != NULL)
			free(parser->attribute);
		parser->attribute = ft_strdup((char *)parser->attribute_stack->content);
	}
	free(xml_tag->tag);
	free(xml_tag);
}
