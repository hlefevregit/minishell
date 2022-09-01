/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:00:23 by hlefevre          #+#    #+#             */
/*   Updated: 2022/09/01 15:22:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **var, char *name)
{
	t_list	*first;
	t_list	*tmp;

	first = *var;
	tmp = *var;
	while (*var && ft_strcmp((*var)->name, name) != 0)
	{
		if (ft_strcmp((*var)->next->name, name) == 0)
			tmp = *var;
		*var = (*var)->next;
	}
	if (ft_strcmp((*var)->name, name) == 0)
	{
		tmp->next = (*var)->next;
		if ((*var)->name)
			free((*var)->name);
		if ((*var)->value)
			free((*var)->value);
		free((*var));
	}
	*var = first;
}
