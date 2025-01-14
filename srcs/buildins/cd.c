/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:20:55 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/14 20:09:36 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_pid;

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
	{
		printf("something went wrong\n");
		move_to_dir(env, get_var_from_env(env, "OLDPWD") + 7);
	}
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

// void ft_cd(t_cmd *cmd)
// {
// 	char	buffer[BUFSIZ];
// 	char	**av;

// 	av = cmd->args;
// 	if (av[1] == NULL)
// 	{
// 		if (chdir(find_in_env("HOME", envp)) != 0)
// 		{
// 			perror("cd");
// 		}
// 	}
// 	else if (ft_strcmp(av[1], "-") == 0)
// 	{
// 		if (chdir(find_in_env("OLDPWD", mini.envp)) != 0)
// 		{
// 			perror("cd");
// 		}
// 	}
// 	else if (chdir(av[1]) != 0)
// 	{
// 		perror("cd");
// 	}
// 	else if (getcwd(buffer, BUFSIZ) == 0)
// 	{
// 		printf("NIQUE TA MERE TOI\n");
// 		ft_cd(ft_split("cd ..", 32), mini);
// 	}
// 	else
// 		g_global.exit_status = EXIT_SUCCESS;
// }
