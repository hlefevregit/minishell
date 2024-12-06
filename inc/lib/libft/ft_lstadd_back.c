/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:08:55 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/06 18:10:12 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*node;

	if (!alst || !new)
		return ;
	node = *alst;
	if (!node)
	{
		*alst = new;
		return ;
	}
	while (node->next != NULL)
		node = node->next;
	node->next = new;
	new->prev = node;
	new->next = NULL;
}
