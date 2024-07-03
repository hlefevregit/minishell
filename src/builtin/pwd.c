/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:53:27 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 13:55:22 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_mini mini)
{
	char	buffer[BUFSIZ];
	char	*pwd;

	if (getcwd(buffer, BUFSIZ) == 0)
	{
		pwd = find_in_env("PWD", mini.envp);
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", buffer);
}