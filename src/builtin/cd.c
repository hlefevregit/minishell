/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:51:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/23 12:11:55 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_cd(char **av, t_mini mini)
{
	char	buffer[BUFSIZ];

	if (av[1] == NULL)
	{
		if (chdir(find_in_env("HOME", mini.envp)) != 0)
		{
			perror("cd");
			g_global.exit_status = EXIT_FAILURE;
		}
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		if (chdir(find_in_env("OLDPWD", mini.envp)) != 0)
		{
			perror("cd");
			g_global.exit_status = EXIT_FAILURE;
		}
	}
	else if (chdir(av[1]) != 0)
	{
		perror("cd");
		g_global.exit_status = EXIT_FAILURE;
	}
	else if (getcwd(buffer, BUFSIZ) == 0)
	{
		printf("NIQUE TA MERE TOI\n");
		ft_cd(ft_split("cd ..", 32), mini);
	}
	else
		g_global.exit_status = EXIT_SUCCESS;
}
