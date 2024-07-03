/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:05:40 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 14:49:12 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_checkunset(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	ft_strcheckunset(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_checkunset(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}


void	ft_error2(char *msg, char *msg2, char *error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
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
