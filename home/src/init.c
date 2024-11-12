/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:08:46 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/12 18:26:58 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	init_shell(char **envp)
{
	t_shell	shell;

	shell.envp = envp;
	shell.exit_status = 0;
	shell.data = malloc(sizeof(t_data));
	shell.line = NULL;
	return (shell);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_data	init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->cmd = malloc(sizeof(t_cmd));
	data->env = malloc(sizeof(t_env));
	data->token = malloc(sizeof(t_token));
	data->num_cmd = 0;
	return (*data);
}
