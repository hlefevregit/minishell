/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:36:41 by hlefevre          #+#    #+#             */
/*   Updated: 2022/09/01 15:28:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *name, char *value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}
