/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:02:36 by hulefevr          #+#    #+#             */
/*   Updated: 2024/04/22 13:02:39 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*new;

	if (!lst || !del)
		return (0);
	t = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			while (t)
			{
				new = t->next;
				(*del)(t->content);
				free(t);
				t = new;
			}
		}
		lst = lst->next;
		ft_lstadd_back(&t, new);
	}
	return (t);
}
