/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:12:33 by hlefevre          #+#    #+#             */
/*   Updated: 2022/09/01 15:21:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_varclear(t_list **v)
{
	t_list	*tmp;

	if (!v || !(*v))
		return ;
	tmp = *v;
	*v = (*v)->next;
	if (tmp->name)
		free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}