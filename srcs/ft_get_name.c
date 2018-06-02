/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:14:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/06/02 02:08:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_get_name_iter(char *s, char *extension, int iter)
{
	char *res;
	char *tmp;
	char *tmp2;

	if (iter == 0)
		return ft_strjoin(s, extension);
	else
	{
		tmp2 = ft_itoa(iter);
		tmp = ft_strjoin_3(" (", tmp2, ")");
		free(tmp2);
		res = ft_strjoin_3(s, tmp, extension);
		free(tmp);
		return res;
	}
}

char	*ft_already_exists(char *s, char *extension, int iter)
{
	char *str;

	str = ft_get_name_iter(s, extension, iter);
	if (open(str, O_RDONLY) != -1)
	{
		free(str);
		str = NULL;
	}
	return (str);
}

void	ft_remove_backslash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

char	*ft_get_name(char *extension)
{
	time_t t;
	struct tm *tm;
	char *s;
	char *str;
	int i;

	t = time(NULL);
	tm = localtime(&t);
//	printf("now: %d-%d-%d %d:%d:%d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	s = ft_strjoin("RT export: ", asctime(tm));
	ft_remove_backslash(s);
	i = 0;
	while (!(str = ft_already_exists(s, extension, i)))
		i++;
	return (str);
}
