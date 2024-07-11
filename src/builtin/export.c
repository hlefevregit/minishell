/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:15 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/10 15:32:00 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_char(char **str, char c)
{
	char	*tmp;
	char	*tmp_c;

	tmp_c = ft_calloc(sizeof(char), 2);
	tmp_c[0] = c;
	tmp = ft_strjoin(*str, tmp_c);
	free(*str);
	free(tmp_c);
	*str = tmp;
}

static void	print_var(t_mini mini)
{
	int		i;
	char	*name;
	char	*content;
	int		i_tmp;

	i = 0;
	while (mini.envp[i])
	{
		i_tmp = 0;
		while (mini.envp[i][i_tmp] != '=')
			i_tmp++;
		name = ft_calloc(sizeof(char), i_tmp + 2);
		content = ft_calloc(sizeof(char),
				ft_strlen(mini.envp[i]) - i_tmp + 1);
		ft_strlcpy(name, mini.envp[i], i_tmp + 2);
		ft_strlcpy(content, mini.envp[i] + i_tmp + 1,
			ft_strlen(mini.envp[i]) - i_tmp);
		printf("declare -x %s\"%s\"\n", name, content);
		free(name);
		free(content);
		i++;
	}
}

static void	send_update(t_export var, char **av, t_mini mini)
{
	char	**env;

	if (mini.envp[var.i_env] && ft_strncmp(mini.envp[var.i_env], av[var.arg], var.i) == 0)
	{
		free(mini.envp[var.i_env]);
		mini.envp[var.i_env] = ft_strdup(av[var.arg]);
	}
	else
	{
		var.i_env = count_array(mini.envp) + 1;
		env = ft_calloc(sizeof(char *), var.i_env + 1);
		var.i_env = 0;
		while (mini.envp[var.i_env])
		{
			env[var.i_env] = ft_strdup(mini.envp[var.i_env]);
			free(mini.envp[var.i_env]);
			var.i_env++;
		}
		env[var.i_env] = ft_strdup(av[var.arg]);
		free(mini.envp);
		mini.envp = env;
	}
}

static void	reset_var(t_export *var)
{
	var->i = 0;
	var->i_env = 0;
	var->tmp = 0;
}

static int	update_var(char **av, t_mini mini)
{
	t_export	var;

	var = (t_export){0};
	while (++var.arg < count_array(av))
	{
		if (av[var.arg][var.i] == 0)
			break ;
		reset_var(&var);
		while (av[var.arg][var.i] && av[var.arg][var.i] != '=')
			add_char(&var.tmp, av[var.arg][var.i++]);
		if (av[var.arg][var.i] != '=' || !ft_strcheckunset(var.tmp))
		{
			if (!ft_strcheckunset(var.tmp))
				ft_error2("export", av[var.arg], "not a valid identifier");
			free(var.tmp);
			return (1);
		}
		free(var.tmp);
		while (mini.envp[var.i_env]
			&& ft_strncmp(mini.envp[var.i_env], av[var.arg], var.i) != 0)
			var.i_env++;
		send_update(var, av, mini);
	}
	return (0);
}

void	ft_export(char **av, t_mini mini)
{
	if (count_array(av) == 1)
		print_var(mini);
	else if (count_array(av) >= 2)
	{
		if (!update_var(av, mini))
		{
			mini.exit_status = EXIT_FAILURE;
			return ;
		}
	}
}