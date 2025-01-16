/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:20:55 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:04 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	move_to_dir(char **env, char *path)
{
	char	*oldpwd;
	char	*newpwd;
	char	buffer[BUFSIZ];

	oldpwd = get_var_from_env(env, "PWD") + 4;
	if (!oldpwd)
	{
		ft_printf("minishell: cd: OLDPWD not set\n");
		g_pid = 1;
		return ;
	}
	g_pid = -chdir(path);
	if (g_pid)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		return ;
	}
	if (getcwd(buffer, BUFSIZ) == 0)
		move_to_dir(env, "..");
	set_env_var(env, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	set_env_var(env, "PWD", newpwd);
	free(newpwd);
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		n_args;

	n_args = ft_tablen(cmd->args);
	if (n_args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		g_pid = 1;
		return ;
	}
	if (n_args == 1)
		path = get_var_from_env(cmd->data->env, "HOME") + 5;
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		path = get_var_from_env(cmd->data->env, "OLDPWD") + 7;
		ft_printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	move_to_dir(cmd->data->env, path);
}
