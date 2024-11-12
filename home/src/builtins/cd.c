/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:51:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/12 18:00:56 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **av)
{
	char	buffer[BUFSIZ];

	if (av[1] == NULL)
	{
		if (chdir(find_in_env("HOME", g_global.envp)) != 0)
		{
			perror("cd");
			g_global.exit_status = EXIT_FAILURE;
		}
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		if (chdir(find_in_env("OLDPWD", g_global.envp)) != 0)
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
		ft_cd(ft_split("cd ..", 32));
	}
	else
		g_global.exit_status = EXIT_SUCCESS;
	return (0);
}
