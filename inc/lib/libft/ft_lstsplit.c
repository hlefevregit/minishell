/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:11:05 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/06 18:11:09 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_lists(t_list *lst, int (cmp)(void *))
{
	int	i;

	i = 0;
	while (lst)
	{
		while (lst && cmp(lst->content))
			lst = lst->next;
		if (!lst)
			break ;
		i++;
		while (lst && !cmp(lst->content))
			lst = lst->next;
	}
	return (i);
}

t_list	**ft_lstsplit(t_list *lst, int (*cmp)(void *), void (*del)(void *))
{
	t_list	**dest;
	int		i;

	i = 0;
	dest = ft_calloc(count_lists(lst, cmp) + 1, sizeof(t_list *));
	while (lst)
	{
		while (lst && cmp(lst->content))
		{
			lst = lst->next;
			ft_lstrmone(lst->prev, del);
			lst->prev->next = NULL;
			lst->prev = NULL;
		}
		if (!lst)
			break ;
		dest[i] = lst;
		i++;
		while (lst && !cmp(lst->content))
			lst = lst->next;
	}
	return (dest);
}
