/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:22:06 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/14 19:54:04 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_pid;

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("%s\n", "pwd: error retrieving current directory: "\
			"getcwd: cannot access parent "\
			"directories: No such file or directory");
		g_pid = 1;
		return ;
	}
	ft_putstr(pwd);
	ft_putchar('\n');
	free(pwd);
	g_pid = 0;
}
