/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrmone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:47:18 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:54:11 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstrmone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		if (lst->prev)
			lst->prev->next = lst->next;
		if (lst->next)
			lst->next->prev = lst->prev;
		free(lst);
	}
}
