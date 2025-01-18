/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:21:56 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/17 17:38:33 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**realloc_env(t_cmd *cmd)
{
	int		size;
	char	**new_env;
	int		i;

	i = 0;
	size = ft_tablen(cmd->data->env);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (cmd->data->env[i] != NULL)
	{
		new_env[i] = ft_strdup(cmd->data->env[i]);
		if (new_env[i] == NULL)
		{
			ft_free_tab(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	put_line_in_env(t_cmd *cmd, int n)
{
	int		size;
	char	**new_env;

	size = ft_tablen(cmd->data->env);
	new_env = realloc_env(cmd);
	new_env[size] = ft_strdup(cmd->args[n]);
	if (!new_env[size])
		return ;
	new_env[size + 1] = NULL;
	ft_free_tab(cmd->data->env);
	cmd->data->env = new_env;
}

void	new_val_for_env(t_cmd *cmd, int n)
{
	int		i;
	char	*new_env;

	i = 0;
	new_env = ft_strdup(cmd->args[n]);
	if (new_env == NULL)
		return ;
	while (cmd->data->env[i] != NULL)
	{
		if (ft_strncmp(cmd->data->env[i], new_env, ft_strchr(new_env, '=')
				- new_env) == 0)
		{
			free(cmd->data->env[i]);
			cmd->data->env[i] = new_env;
			return ;
		}
		i++;
	}
}

void	add_val_env(t_cmd *cmd, int n)
{
	int		i;
	char	*new_value;
	char	*old_env;
	char	*combined_env;

	i = 0;
	new_value = ft_strchr(cmd->args[n], '=') + 1;
	old_env = NULL;
	combined_env = NULL;
	while (cmd->data->env[i] != NULL)
	{
		if (ft_strncmp(cmd->data->env[i], cmd->args[n], ft_strchr(cmd->args[n],
					'=') - cmd->args[n]) == 0)
		{
			old_env = cmd->data->env[i];
			combined_env = ft_strjoin(old_env, new_value);
			if (!combined_env)
				return ;
			free(cmd->data->env[i]);
			cmd->data->env[i] = combined_env;
			return ;
		}
		i++;
	}
}

void	ft_export(t_cmd *cmd)
{
	int	i;

	i = 0;
	g_pid = 0;
	while (cmd->args[++i] != NULL)
	{
		if (!check_env_name(cmd->args[i]))
			continue ;
		else if (plus_in_name(cmd->args[i]))
		{
			remove_plus(cmd->args[i]);
			if (!already_in_env(cmd->args[i], cmd))
				put_line_in_env(cmd, i);
			else
				add_val_env(cmd, i);
		}
		else if (!already_in_env(cmd->args[i], cmd))
			put_line_in_env(cmd, i);
		else
			new_val_for_env(cmd, i);
	}
	if (cmd->args[1] == NULL)
		export_oargs(cmd);
}
