/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:45:33 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/26 13:21:19 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_env_var(char **env, const char *key)
{
    size_t key_len;
    int i;

	i = 0;
	key_len = ft_strlen(key);
    while (env[i])
	{
        if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return (env[i] + key_len + 1);
        i++;
    }
    return (NULL);
}

void print_with_variables(char *str, char **env, int last_exit_status)
{
    int in_single_quote;
    int in_double_quote;

	in_double_quote = 0;
	in_single_quote = 0;
    while (*str)
	{
        if (*str == '\'' && !in_double_quote)
		{
            in_single_quote = !in_single_quote;
            str++;
        }
		else if (*str == '"' && !in_single_quote)
		{
            in_double_quote = !in_double_quote;
            str++;
        }
		else if (*str == '$' && !in_single_quote)
		{
            str++;
            if (*str == '?')
			{
                printf("%d", last_exit_status);
                str++;
            }
			else
			{
                char var_name[256] = {0};
                int i = 0;
                while (ft_isalnum(*str) || *str == '_')
                    var_name[i++] = *str++;
                var_name[i] = '\0';
                char *value = get_env_var(env, var_name);
                if (value)
                    printf("%s", value);
            }
        }
		else
		{
            putchar(*str);
            str++;
        }
    }
}

void ft_echo(char **arg, t_mini mini)
{
    int	i;
    int newline = 1;
	
	i = 1;
    if (arg[1] && ft_strncmp(arg[1], "-n\0", 3) == 0)
	{
        newline = 0;
        i++;
    }
    while (arg[i])
	{
        if (i > 1 || (i > 2 && newline == 0))
            putchar(' ');
        print_with_variables(arg[i], mini.envp, g_global.exit_status);
        i++;
    }
    if (newline)
        putchar('\n');
}
