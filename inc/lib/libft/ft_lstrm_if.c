/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:10:49 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/06 18:10:51 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrm_if(t_list **lst, int (*cmp)(void *), void (*del)(void*))
{
	t_list	*node;
	t_list	*next;

	node = *lst;
	while (node)
	{
		if (cmp(node->content))
		{
			next = node->next;
			if (node == *lst)
				*lst = next;
			ft_lstrmone(node, del);
			node = next;
		}
		else
			node = node->next;
	}
}
