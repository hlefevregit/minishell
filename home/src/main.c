/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:43:05 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/12 18:27:28 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global g_global;

char	*find_in_env(char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], cmd, ft_strlen(cmd)) == 0
			&& envp[i][ft_strlen(cmd)] == '=')
			return (envp[i] + ft_strlen(cmd) + 1);
		i++;
	}
	return (NULL);
}

void	ft_free_all(t_data *data)
{
	t_cmd	*tmp;

	while (data->cmd)
	{
		tmp = data->cmd;
		data->cmd = data->cmd->next;
		free(tmp->cmd);
		free(tmp->args);
		free(tmp);
	}
	free(data->env);
	free(data->token);
	free(data);
}

void	shell_loop(t_shell *shell)
{
	while (1)
	{
		shell->line = readline("minishell$ ");
		if (!shell->line)
			exit(0);
		if (shell->line[0] != '\0')
			add_history(shell->line);
		*shell->data = get_lex(shell);
		if (shell->data)
		{
			if (ft_strcmp(shell->data->cmd->cmd, "exit") == 0)
			{
				exit(ft_exit(shell->data->cmd->args));
			}
			shell->exit_status = ft_exec(shell->data->cmd);
			ft_free_all(shell->data);
		}
		free(shell->line);
	}
}



int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell = init_shell(envp);
	shell_loop(&shell);
	return (0);
}