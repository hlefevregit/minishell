/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:20:43 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/15 15:09:30 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_lexer(void *ptr)
{
	t_lexer	*lexer;

	lexer = ptr;
	free(lexer->str);
	free(lexer);
}

void	free_cmd(void *ptr)
{
	t_cmd	*cmd;
	int		i;

	cmd = ptr;
	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	if (cmd->out)
		ft_lstclear(&cmd->out, &free_lexer);
	free(cmd->args);
	free(cmd);
}

t_data	*init_data(char **environ)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->env = ft_tabcpy(environ);
	if (ft_tablen(data->env) == 0)
	{
		printf("minishell: env is empty\n");
		free(data->env);
		free(data);
		exit (1);
	}
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	return (data);
}

void	free_data(t_data *data)
{
	if (data->cmds)
		ft_lstclear(&data->cmds, &free_cmd);
	ft_free_tab(data->env);
	free(data);
	rl_clear_history();
}
