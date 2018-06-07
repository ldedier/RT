/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 03:14:18 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/07 04:09:51 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_resolution(t_parser *parser, t_world *world, char *line)
{
	if (parser->parse_enum != e_parse_scene)
	{
		ft_dprintf(2, "line %d: current object can not have resolution\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, &(world->canvas->win_size.x));
	read_int(&line, &(world->canvas->win_size.y));
	world->cam->pd = ZOOM / world->canvas->win_size.x;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_fast_resolution(t_parser *parser, t_world *world, char *line)
{
	if (parser->parse_enum != e_parse_scene)
	{
		ft_dprintf(2, "line %d: current object can not have fast_resolution\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, &(world->canvas->fast_win_size.x));
	read_int(&line, &(world->canvas->fast_win_size.y));
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_filter(t_parser *parser, t_world *world, char *line)
{
	if (parser->parse_enum != e_parse_scene)
	{
		ft_dprintf(2, "line %d: current object can not have filter\n",
				parser->nb_lines);
		exit(1);
	}
	printf("attribute: %s| %i\n",parser->attribute, e_sharpen);fflush(stdout);
	if (!ft_strcmp(parser->attribute, "blur"))
		world->filters[e_gauss_blur] = 1;
	else if (!ft_strcmp(parser->attribute, "sharpen"))
		world->filters[e_sharpen] = 1;
	else if (!ft_strcmp(parser->attribute, "sobel"))
		world->filters[e_sobel] = 1;
	else if (!ft_strcmp(parser->attribute, "emboss"))
		world->filters[e_emboss] = 1;
	else if (!ft_strcmp(parser->attribute, "grey"))
		world->filters[e_grey] = 1;
	else if (!ft_strcmp(parser->attribute, "motion_blur"))
		world->filters[e_motion_blur] = 1;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}

void	ft_parse_shader(t_parser *parser, t_world *world, char *line)
{
	if (parser->parse_enum != e_parse_scene)
	{
		ft_dprintf(2, "line %d: current object can not have shader\n",
				parser->nb_lines);
		exit(1);
	}
	if (!ft_strcmp(parser->attribute, "normal"))
		world->shader = 1;
	else if (!ft_strcmp(parser->attribute, "cartoon"))
		world->shader = 2;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_process_tag_stack(parser);
}
