/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 22:58:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:19:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_f(t_pf *pf, va_list va, char c)
{
	(void)c;
	pf->var.flottant = va_arg(va, double);
	if (!pf->precised_precision)
		pf->flags.precision = 6;
	ft_putdbl(pf->var.flottant, pf->flags.precision);
	return (0);
}
