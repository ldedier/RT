/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:04:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/11 22:04:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mod		ft_new_mod(void)
{
	t_mod res;

	res.enabled = 1;
	res.color = 0;
	res.inequality = bigger_than;
	res.value = 0.5;
	res.mod_value = 0.5;
	return (res);
}
