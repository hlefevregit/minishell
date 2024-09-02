/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:51:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/07 16:39:37 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_cd(char **av, t_mini mini)
{
	char	buffer[BUFSIZ];

	if (av[1] == NULL)
	{
		if (chdir("/home") != 0)
		{
			perror("cd");
			g_global.exit_status = EXIT_FAILURE;
		}
	}
	if (ft_strcmp(av[1], "-") == 0)
	{
		if (chdir(find_in_env("OLDPWD", mini.envp)) != 0)
		{
			perror("cd");
			g_global.exit_status = EXIT_FAILURE;
		}
	}
	if (chdir(av[1]) != 0)
	{
		perror("cd");
		g_global.exit_status = EXIT_FAILURE;
	}
	else
		g_global.exit_status = EXIT_SUCCESS;
	if (getcwd(buffer, BUFSIZ) == 0)
	{
		printf("NIQUE TA MERE TOI\n");
		ft_cd(ft_split("cd ..", 32), mini);
	}
}

// void			change_dir(char *path)
// {
// 	printf("cd: ");
// 	if (access(path, F_OK) == -1)
// 		printf("no such file or directory: ");
// 	else if (access(path, R_OK) == -1)
// 		printf("permission denied: ");
// 	else
// 		printf("not a directory: ");
// 	ft_putendl_fd(path, 0);
// }


// void	ft_cd(char **av, t_mini mini)
// {
// 	char	*home_path;

// 	home_path = find_in_env("HOME", mini.envp);
// 	if (!av[1])
// 	{
// 		change_dir(home_path);
// 		return ;
// 	}
// 	else
// 	{
// 		if (av[1][0] == '-' && !av[1][2])
// 		{
// 			change_dir(find_in_env("OLDPWD", mini.envp));
// 			return ;
// 		}
// 		change_dir(av[0]);
// 	}
// }