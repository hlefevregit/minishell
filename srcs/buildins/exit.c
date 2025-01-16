/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:21:30 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 15:21:49 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	int		ret;

	ret = 0;
	if (cmd->args[1])
	{
		if (!ft_strisint(cmd->args[1]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				cmd->args[1]);
			exit(2);
		}
		else if (cmd->args[2])
		{
			ft_printf("minishell: exit: too many arguments\n");
			return ;
		}
		ret = ft_atoi(cmd->args[1]) % 256;
	}
	free_data(cmd->data);
	exit(ret);
}
