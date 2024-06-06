/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:56:04 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/06 13:02:56 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*d;
	t_list	*t;

	t = *lst;
	while (t)
	{
		d = t->next;
		ft_lstdelone(t, del);
		t = d;
	}
	*lst = NULL;
}
