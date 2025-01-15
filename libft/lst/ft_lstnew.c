/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:47:04 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:54:16 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*maillon;

	maillon = (t_list *)malloc(sizeof(t_list));
	if (!(maillon))
		return (0);
	maillon->content = content;
	maillon->next = NULL;
	maillon->prev = NULL;
	return (maillon);
}
