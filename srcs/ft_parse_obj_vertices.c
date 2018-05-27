/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_obj_vertices.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 18:47:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/27 06:50:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_pow(int a, int b)
{
	int i;
	int res;

	res = 1;
	i = 0;
	if (b >= 0)
	{
		while (i < b)
		{
			res *= a;
			i++;
		}
	}
	else
	{
		while (i > b)
		{
			res /= a;
			i--;
		}
	}
	return (res);
}

void	ft_add_float(char const *s, int *i, double *coord)
{
	int point;

	point = *i;
	*i += 1;
	while (ft_isdigit(s[*i]))
	{
		*coord += (s[*i] - '0') / (double)(ft_pow(10, *i - point));
		*i += 1;
	}
}

void	ft_pow_coord(char const *s, int *i, double *coord)
{
	int	pow;
	int start;

	pow = 0;
	*i += 1;
	start = *i;
	if (s[*i] == '+' || s[*i] == '-')
		*i += 1;
	while (ft_isdigit(s[*i]))
	{
		pow = pow * 10 + s[*i] - '0';
		*i += 1;
	}
	if(s[start] == '-')
		pow *= -1;
	printf("%d\n", pow);
	*coord = *coord * ft_pow(10 , pow);
}

void	ft_obj_add_coord(int *i, char *s , double *coord)
{
	int start;

	*coord = 0;
	while (!ft_isdigit(s[*i]) && s[*i] != '-')
		*i += 1;
	start = *i;
	if (s[*i] == '+' || s[*i] == '-')
		*i += 1;
	while (ft_isdigit(s[*i]))
	{
		*coord = *coord * 10 + s[*i] - '0';
		*i += 1;
	}
	if (s[*i] == '.')
		ft_add_float(s, i, coord);
	if (s[*i] == 'E')
		ft_pow_coord(s, i, coord);
	if (s[start] == '-')
		*coord *= -1;
	if(*coord > 5)
	{
		//printf("%f\n", *coord);
	//	printf("%s\n", &(s[*i - 10]));
	//	exit(0);
	}
}

void	ft_obj_vertex(int *i, char *s, t_obj_parser *parser)
{
	t_point3d *vertex;

	vertex = (t_point3d *)(malloc(sizeof(t_point3d)));
	ft_obj_add_coord(i, s, &(vertex->x));
	ft_obj_add_coord(i, s, &(vertex->y));
	ft_obj_add_coord(i, s, &(vertex->z));
	while (s[*i] != '\0' && s[*i] != '\n')
		*i += 1;
	ft_lstpushback(&(parser->vertices_tmp), ft_lstnew_ptr(vertex, sizeof(t_point3d)));
	parser->nb_vertices++;
}
