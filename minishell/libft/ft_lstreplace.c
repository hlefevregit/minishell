/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:15:52 by hlefevre          #+#    #+#             */
/*   Updated: 2022/09/01 15:30:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_lstreplace(t_list **v, char *name, char *val)
{
	t_list	*first;

	first = *v;
	while (v && ft_strcmp((*v)->name, name) != 0)
		*v = (*v)->next;
	if (ft_strcmp((*v)->name, name) == 0)
	{
		if ((*v)->value)
			free((*v)->value);
		(*v)->value = val;
	}
	*v = first;
	return (v);
}
