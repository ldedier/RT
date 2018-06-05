/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inequality.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 20:27:29 by ldedier           #+#    #+#             */
/*   Updated: 2018/05/26 20:30:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		less_than(double a, double b)
{
	return (a < b);
}

int		bigger_than(double a, double b)
{
	return (a > b);
}

int		less_than_or_equal(double a, double b)
{
	return (a <= b);
}

int		bigger_than_or_equal(double a, double b)
{
	return (a >= b);
}

int		equal(double a, double b)
{
	return (a == b);
}
