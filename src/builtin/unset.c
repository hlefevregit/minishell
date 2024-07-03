/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:10:30 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 14:49:56 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_var(int i_env, int i, char **av, t_mini mini)
{
	int		arg;
	char	**env;

	if (mini.envp[i_env]
		&& ft_strncmp(mini.envp[i_env], av[i], ft_strlen(av[i])) == 0)
	{
		env = ft_calloc(sizeof(char *), count_array(mini.envp));
		arg = 0;
		while (arg < i_env)
		{
			env[arg] = ft_strdup(mini.envp[arg]);
			arg++;
		}
		i_env++;
		while (mini.envp[i_env])
		{
			env[arg] = ft_strdup(mini.envp[i_env]);
			i_env++;
			arg++;
		}
		free_double(mini.envp);
		mini.envp = env;
	}
}

void	ft_unset(char **av, t_mini mini)
{
	int		i;
	int		i_env;
	int		ac;

	i = 0;
	ac = count_array(av);
	if (ac > 1)
	{
		while (av[++i])
		{
			i_env = 0;
			if (ft_strcheckunset(av[i]) == 0)
			{
				ft_error2("unset", av[i], "not a valid identifier");
				return ;
			}
			while (mini.envp[i_env]
				&& ft_strncmp(mini.envp[i_env], av[i],
					ft_strlen(av[i])) != 0)
				i_env++;
			clear_var(i_env, i, av, mini);
		}
	}
}