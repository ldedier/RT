/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newtree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:48:29 by ldedier           #+#    #+#             */
/*   Updated: 2017/11/07 20:53:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*ft_newtree(void *content)
{
	t_tree *tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		return (NULL);
	tree->content = content;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}
