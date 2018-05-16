/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:10:29 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/16 03:13:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_lol(char *line, char **tag, char **attribute, int *i)
{
	int		start;
	int		length;

	start = *i;
	while (line[*i] && (line[*i] != ' ' && line[*i] != '>'))
		*i += 1;
	length = *i - start;
	if (*tag != NULL)
		free(*tag);
	*tag = ft_strndup(&(line[start]), length);
	if (line[*i] == ' ')
	{
		while (line[*i] && line[*i] != '"')
			*i += 1;
		*i += 1;
		start = *i;
		while (line[*i] && line[*i] != '"')
			*i += 1;
		length = *i - start;
		if (*attribute != NULL)
			free(*attribute);
		*attribute = ft_strndup(&(line[start]), length);
	}
}

int			ft_parse_tag(char **line, char **tag, char **attribute)
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
		ft_lol(*line, tag, attribute, &i);
	}
	*(line) += i + 1;
	return (ret);
}

void		ft_process_tag_stack_stack(t_parser *parser)
{
	if (!parser->got_scene)
	{
		if (!ft_strcmp("scene", parser->tag))
			parser->got_scene = 1;
		else
		{
			ft_dprintf(2,
					"every config file must begin with a <scene> tag\n");
			exit(1);
		}
	}
	ft_lstadd(&(parser->tag_stack),
			ft_lstnew(parser->tag, sizeof(char) * ft_strlen(parser->tag) + 1));
}

void		ft_process_tag_stack(t_parser *parser)
{
	char	*str;

	if (parser->op == POP)
	{
		str = (char *)(ft_lstpop(&(parser->tag_stack)));
		if (str == NULL)
		{
			ft_dprintf(2, "line %d: no corresponding opening tag for %s\n",
					parser->nb_lines, parser->tag);
			exit(1);
		}
		else if (ft_strcmp(parser->tag, str))
		{
			ft_dprintf(2, "line %d: expected ending tag %s instead of %s\n",
					parser->nb_lines, str, parser->tag);
			exit(1);
		}
		free(str);
	}
	else if (parser->op == STACK)
		ft_process_tag_stack_stack(parser);
}
