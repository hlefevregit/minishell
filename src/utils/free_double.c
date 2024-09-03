/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:10:23 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/03 16:14:57 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	if (count_array(str) != 1)
	{
		while (str[++i])
		{
			if (str[i])
				free(str[i]);
			str[i] = NULL;
		}
	}
	free(str);
}

int	count_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}