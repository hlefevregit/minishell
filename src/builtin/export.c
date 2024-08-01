/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:15 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/01 17:47:10 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void update_env(char **env, const char *name, const char *value)
{
	int		i;
	char	*new_entry;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, strlen(name)) == 0 && env[i][ft_strlen(name)] == '=')
		{
			free(env[i]);
			new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
			if (!new_entry)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(new_entry, name, ft_strlen(name));
			new_entry[ft_strlen(name)] = '=';
			ft_memcpy(new_entry + ft_strlen(name) + 1, value,ft_strlen(value));
			new_entry[ft_strlen(name) + ft_strlen(value) + 1] = '\0';
			env[i] = new_entry;
			return;
		}
		i++;
	}
	new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!new_entry)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(new_entry, name, ft_strlen(name));
	new_entry[ft_strlen(name)] = '=';
	ft_memcpy(new_entry + ft_strlen(name) + 1, value,ft_strlen(value));
	new_entry[ft_strlen(name) + ft_strlen(value) + 2] = '\0';
	env[i] = new_entry;
	env[i + 1] = NULL;
}

void parse_arg(char *arg, char **name, char **value)
{
	int		in_squote;
	int		in_dquote;
	char	*p;
	char	q;

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
	if (!*value)
		*value = "";
	if (**value == '"' || **value == '\'')
	{
		q = **value;
		(*value)++;
		p = *value + strlen(*value) - 1;
		if (*p == q) *p = '\0';
	}
}

void ft_export(char **arg, t_mini mini)
{
	int     i;
	char    *name;
	char    *value;

	i = 1;
	while (arg[i])
	{
		parse_arg(arg[i], &name, &value);
		update_env(mini.envp, name, value);
		i++;
	}
	g_global.exit_status = 0;
}
