/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:15 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/26 13:24:28 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cpy_dat_env(char *new_entry, char *name, char *value)
{
	ft_memcpy(new_entry, name, ft_strlen(name));
	new_entry[ft_strlen(name)] = '=';
	ft_memcpy(new_entry + ft_strlen(name) + 1, value,ft_strlen(value));
	new_entry[ft_strlen(name) + ft_strlen(value) + 2] = '\0';
	return (new_entry);
}

void	update_env(char **env, char *name, char *value, char **envp)
{
	int		i;
	char	*new_entry;
	char	*env_value;

	if (value && value[0] == '$')
	{
		env_value = get_env_var(envp, value + 1);
		if (env_value)
			value = env_value;
	}
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
		{
			free(env[i]);
			new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
			if (!new_entry)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			env[i] = cpy_dat_env(new_entry, name, value);
			return ;
		}
		i++;
	}
	new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!new_entry)
		exit(EXIT_FAILURE);
	env[i] = cpy_dat_env(new_entry, name, value);
	env[i + 1] = NULL;
}

void	p_update(char **value, char *p)
{
	char	q;
	
	if (!*value)
		*value = "";
	if (**value == '"' || **value == '\'')
	{
		q = **value;
		(*value)++;
		p = *value + strlen(*value) - 1;
		if (*p == q)
			*p = '\0';
	}
	return ;
}

void parse_arg(char *arg, char **name, char **value)
{
	int		in_squote;
	int		in_dquote;
	char	*p;

	*name = arg;
	*value = NULL;
	in_dquote = 0;
	in_squote = 0;
	p = arg;
	while (*p)
	{
		if (*p == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (*p == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (*p == '=' && !in_squote && !in_dquote)
		{
			*p = '\0';
			*value = p + 1;
			break;
		}
		p++;
	}
	p_update(value, p);
}

void	printf_sorted_env(char **envp)
{
	int		i;
	int		sorted;
	char	*tmp;
	char	**sorted_env;
	
	i = 0;
	while (envp[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		sorted_env[i] = envp[i];
		i++;
	}
	sorted_env[i] = NULL;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (sorted_env[i + 1])
		{
			if (ft_strcmp(sorted_env[i], sorted_env[i + 1]) > 0)
			{
				tmp = sorted_env[i];
				sorted_env[i] = sorted_env[i + 1];
				sorted_env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);	
}

void ft_export(char **arg, t_mini mini)
{
	int     i;
	char    *name;
	char    *value;

	i = 1;
	if (!arg[1])
	{
		printf_sorted_env(mini.envp);
		g_global.exit_status = 0;
	}
	else
	{
		while (arg[i])
		{
			parse_arg(arg[i], &name, &value);
			update_env(mini.envp, name, value, mini.envp);
			i++;
		}
		g_global.exit_status = 0;
	}
}
