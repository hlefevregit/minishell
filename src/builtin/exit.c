/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:32:49 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/25 15:07:56 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **av, t_mini mini)
{
	int	i;

	i = 0;
	if (av[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_global.exit_status = 1;
		return (-1);
	}
	if (av[1])
	{
		while (av[1][i])
		{
			if (!ft_isdigit(av[1][i]))
			{
				printf("minishell: exit: %s: numeric argument required\n", av[1]);
				mini.exit = 2;
				return (2);
			}
			i++;
		}
		return (ft_atoi(av[1]) % 256);
	}
	return (0);
}
