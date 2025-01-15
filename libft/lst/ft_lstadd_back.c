/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:46:31 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:54:47 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*maillon;

	if (!alst || !new)
		return ;
	maillon = *alst;
	if (!maillon)
	{
		*alst = new;
		return ;
	}
	while (maillon->next != NULL)
		maillon = maillon->next;
	maillon->next = new;
	new->prev = maillon;
	new->next = NULL;
}
