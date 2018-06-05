/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 03:14:18 by lcavalle          #+#    #+#             */
/*   Updated: 2018/06/05 12:13:16 by lcavalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_resolution(t_parser *parser, t_world *world, char *line)
{
	t_pixel	div;
	if (parser->parse_enum != e_parse_scene)
	{
		ft_dprintf(2, "line %d: current object can not have resolution\n",
				parser->nb_lines);
		exit(1);
	}
	read_int(&line, &(world->canvas->win_size.x));
	read_int(&line, &(world->canvas->win_size.y));
	if (world->canvas->win_size.y < 1000)
	{
		ft_dprintf(2, "line %d: minimum vertical resolution is 1000\n",
				parser->nb_lines);
		exit(1);
	}
	world->canvas->halved_win_size.x = world->canvas->win_size.x / 2;
	world->canvas->halved_win_size.y = world->canvas->win_size.y / 2;
	div = fast_div(world->canvas);
	world->canvas->fast_win_size.x = world->canvas->win_size.x / div.x / FAST_RATIO;
	world->canvas->fast_win_size.y = world->canvas->win_size.y / div.y / FAST_RATIO;
	world->canvas->ratio = (double)world->canvas->win_size.x /
		(double)world->canvas->win_size.y;
	world->canvas->pb_rect.y = world->canvas->win_size.y;
	world->cam->pd = ZOOM / world->canvas->win_size.x;
	world->canvas->npixels = world->canvas->win_size.x *
		world->canvas->win_size.y;
	world->canvas->screen.w = world->canvas->win_size.x;
	world->canvas->screen.h = world->canvas->win_size.y;
	parser->op = ft_parse_tag(&line, &(parser->tag), &(parser->attribute));
	ft_init_all(world->canvas);
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
