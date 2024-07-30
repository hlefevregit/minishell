/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:15 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/29 15:24:22 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	add_char(char **str, char c)
// {
// 	char	*tmp;
// 	char	*tmp_c;

// 	tmp_c = ft_calloc(sizeof(char), 2);
// 	tmp_c[0] = c;
// 	tmp = ft_strjoin(*str, tmp_c);
// 	free(*str);
// 	free(tmp_c);
// 	*str = tmp;
// }

// static void	print_var(t_mini mini)
// {
// 	int		i;
// 	char	*name;
// 	char	*content;
// 	int		i_tmp;

// 	i = 0;
// 	while (mini.envp[i])
// 	{
// 		i_tmp = 0;
// 		while (mini.envp[i][i_tmp] != '=')
// 			i_tmp++;
// 		name = ft_calloc(sizeof(char), i_tmp + 2);
// 		content = ft_calloc(sizeof(char),
// 				ft_strlen(mini.envp[i]) - i_tmp + 1);
// 		ft_strlcpy(name, mini.envp[i], i_tmp + 2);
// 		ft_strlcpy(content, mini.envp[i] + i_tmp + 1,
// 			ft_strlen(mini.envp[i]) - i_tmp);
// 		printf("declare -x %s\"%s\"\n", name, content);
// 		free(name);
// 		free(content);
// 		i++;
// 	}
// }

// static void	send_update(t_export var, char **av, t_mini mini)
// {
// 	char	**env;

// 	if (mini.envp[var.i_env] && ft_strncmp(mini.envp[var.i_env], av[var.arg], var.i) == 0)
// 	{
// 		free(mini.envp[var.i_env]);
// 		mini.envp[var.i_env] = ft_strdup(av[var.arg]);
// 	}
// 	else
// 	{
// 		var.i_env = count_array(mini.envp) + 1;
// 		env = ft_calloc(sizeof(char *), var.i_env + 1);
// 		var.i_env = 0;
// 		while (mini.envp[var.i_env])
// 		{
// 			env[var.i_env] = ft_strdup(mini.envp[var.i_env]);
// 			free(mini.envp[var.i_env]);
// 			var.i_env++;
// 		}
// 		env[var.i_env] = ft_strdup(av[var.arg]);
// 		free(mini.envp);
// 		mini.envp = env;
// 	}
// }

// static void	reset_var(t_export *var)
// {
// 	var->i = 0;
// 	var->i_env = 0;
// 	var->tmp = 0;
// }

// static int	update_var(char **av, t_mini mini)
// {
// 	t_export	var;

// 	var = (t_export){0};
// 	while (++var.arg < count_array(av))
// 	{
// 		if (av[var.arg][var.i] == 0)
// 			break ;
// 		reset_var(&var);
// 		while (av[var.arg][var.i] && av[var.arg][var.i] != '=')
// 			add_char(&var.tmp, av[var.arg][var.i++]);
// 		if (av[var.arg][var.i] != '=' || !ft_strcheckunset(var.tmp))
// 		{
// 			if (!ft_strcheckunset(var.tmp))
// 				ft_error2("export", av[var.arg], "not a valid identifier");
// 			free(var.tmp);
// 			return (1);
// 		}
// 		free(var.tmp);
// 		while (mini.envp[var.i_env]
// 			&& ft_strncmp(mini.envp[var.i_env], av[var.arg], var.i) != 0)
// 			var.i_env++;
// 		send_update(var, av, mini);
// 	}
// 	return (0);
// }

// void	ft_export(char **av, t_mini mini)
// {
// 	if (count_array(av) == 1)
// 		print_var(mini);
// 	else if (count_array(av) >= 2)
// 	{
// 		if (!update_var(av, mini))
// 		{
// 			mini.exit_status = EXIT_FAILURE;
// 			return ;
// 		}
// 	}
// }

void update_env_var(char **env, const char *name, const char *value)
{
    int name_len = strlen(name);
    int value_len = strlen(value);
    int entry_len = name_len + value_len + 2; // +1 for '=' and +1 for '\0'
    char *entry = malloc(entry_len);
    if (entry == NULL)
	{
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Construct the environment variable entry
    strcpy(entry, name);
    entry[name_len] = '=';
    strcpy(entry + name_len + 1, value);
    entry[entry_len - 1] = '\0';

    // Find and update the environment variable
    int i = 0;
    while (env[i] != NULL)
	{
        if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
            free(env[i]);
            env[i] = entry;
            return;
        }
        i++;
    }

    // If not found, add the environment variable
    env[i] = entry;
    env[i + 1] = NULL;
}

// Function to parse and export environment variables
void ft_export(char **arg, t_mini mini)
{
	int		i;
	char	*name;
	char	*value;
	char	*p;
	int		in_single_quote;
	int		in_double_quote;
	char	**env = mini.envp;

	i = 1;
	in_single_quote = 0;
	in_double_quote = 0;
    while (arg[i] != NULL)
	{
        p = arg[i];
        while (*p)
		{
            if (*p == '\'' && !in_double_quote)
			{
                in_single_quote = !in_single_quote;
                p++;
            }
			else if (*p == '"' && !in_single_quote)
			{
                in_double_quote = !in_double_quote;
                p++;
            }
			else if (*p == '=' && !in_single_quote && !in_double_quote)
			{
                *p = '\0';
                name = arg[i];
                value = p + 1;
                break;
            }
			else
                p++;
        }

		
        if (name == NULL)
		{
            name = arg[i];
            value = "";
        }
        if (value[0] == '\'' || value[0] == '"')
		{
            char quote = value[0];
            value++;
            char *end = value + strlen(value) - 1;
            if (*end == quote)
                *end = '\0';
        }
        update_env_var(env, name, value);
        i++;
    }
}
