/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:21:56 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/08 16:30:55 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**expand_env(t_cmd *cmd)
{
	int		size;
	char	**new_env;
	int		i;

	printf("Expand env\n");
	i = 0;
	size = ft_tablen(cmd->data->env);
	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (cmd->data->env[i] != NULL)
	{
		new_env[i] = ft_strdup(cmd->data->env[i]);
		if (new_env[i] == NULL)
		{
			ft_free_tab(new_env);
			printf("alloc faild");
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	put_line_in_env(t_cmd *cmd, int n)
{
	int		size;
	char	**new_env;

	printf("Put line in env\n");
	size = ft_tablen(cmd->data->env);
	new_env = expand_env(cmd);
	new_env[size] = ft_strdup(cmd->args[n]);
	if (!new_env[size])
	{
		printf("alloc failed");
		return ;
	}
	new_env[size + 1] = NULL;
	ft_free_tab(cmd->data->env);
	cmd->data->env = new_env;
	return ;
}

void	new_val_for_env(t_cmd *cmd, int n)
{
	int		i;
	char	*new_env;

	i = 0;
	new_env = ft_strdup(cmd->args[n]);
	if (new_env == NULL)
	{
		printf("alloc faild \n");
		return ;
	}
	while (cmd->data->env[i] != NULL)
	{
		if (ft_strncmp(cmd->data->env[i], new_env,
				ft_strchr(new_env, '=') - new_env) == 0)
		{
			free(cmd->data->env[i]);
			printf("non\n");
			cmd->data->env[i] = new_env;
			return ;
		}
		i++;
	}
	printf("ui\n");
	put_line_in_env(cmd, n);
}

void	add_val_env(t_cmd *cmd, int n)
{
	int		i;
	char	*new_value;
	char	*old_env;
	char	*combined_env;

	i = 0;
	new_value = ft_strchr(cmd->args[n], '=') + 1;
	old_env = NULL;
	combined_env = NULL;
	while (cmd->data->env[i] != NULL)
	{
		if (ft_strncmp(cmd->data->env[i], cmd->args[n],
				ft_strchr(cmd->args[n], '=') - cmd->args[n]) == 0)
		{
			old_env = cmd->data->env[i];
			combined_env = ft_strjoin(old_env, new_value);
			if (!combined_env)
				return ;
			free(cmd->data->env[i]);
			cmd->data->env[i] = combined_env;
			return ;
		}
		i++;
	}
}

void	ft_export(t_cmd *cmd)
{
	int	i;

	printf("args[0] = %s\n", cmd->args[0]);
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (!check_env_name(cmd->args[i]))
			return ;
		if (plus_in_name(cmd->args[i]))
		{
			remove_plus(cmd->args[i]);
			if (!already_in_env(cmd->args[i], cmd))
				put_line_in_env(cmd, i);
			else
				add_val_env(cmd, i);
		}
		else if (!already_in_env(cmd->args[i], cmd))
			put_line_in_env(cmd, i);
		else
			new_val_for_env(cmd, i);
		i++;
	}
}
// char    *get_env_var(char **env, const char *key)
// {
//     size_t key_len;
//     int i;

// 	i = 0;
// 	key_len = ft_strlen(key);
//     while (env[i])
// 	{
//         if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
//             return (env[i] + key_len + 1);
//         i++;
//     }
//     return (NULL);
// }

// char	*cpy_dat_env(char *new_entry, char *name, char *value)
// {
// 	ft_memcpy(new_entry, name, ft_strlen(name));
// 	new_entry[ft_strlen(name)] = '=';
// 	ft_memcpy(new_entry + ft_strlen(name) + 1, value,ft_strlen(value));
// 	new_entry[ft_strlen(name) + ft_strlen(value) + 2] = '\0';
// 	return (new_entry);
// }

// void	update_env(char **env, char *name, char *value, char **envp)
// {
// 	int		i;
// 	char	*new_entry;
// 	char	*env_value;

// 	printf("name = %s\n", name);
// 	printf("value = %s\n", value);
// 	if (value && value[0] == '$')
// 	{
// 		env_value = get_env_var(envp, value + 1);
// 		if (env_value)
// 			value = env_value;
// 	}
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], name, strlen(name)) == 0
// 			&& env[i][ft_strlen(name)] == '=')
// 		{
// 			free(env[i]);
// 			new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
// 			if (!new_entry)
// 			{
// 				perror("malloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			env[i] = cpy_dat_env(new_entry, name, value);
// 			return ;
// 		}
// 		i++;
// 	}
// 	new_entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
// 	if (!new_entry)
// 		exit(EXIT_FAILURE);
// 	env[i] = cpy_dat_env(new_entry, name, value);
// 	env[i + 1] = NULL;
// }

// void	p_update(char **value, char *p)
// {
// 	char	q;
	
// 	if (!*value)
// 		*value = "";
// 	if (**value == '"' || **value == '\'')
// 	{
// 		q = **value;
// 		(*value)++;
// 		p = *value + strlen(*value) - 1;
// 		if (*p == q)
// 			*p = '\0';
// 	}
// 	return ;
// }

// void parse_arg(char *arg, char **name, char **value)
// {
// 	int		in_squote;
// 	int		in_dquote;
// 	char	*p;

// 	*name = arg;
// 	*value = NULL;
// 	in_dquote = 0;
// 	in_squote = 0;
// 	p = arg;
// 	while (*p)
// 	{
// 		if (*p == '\'' && !in_dquote)
// 			in_squote = !in_squote;
// 		else if (*p == '"' && !in_squote)
// 			in_dquote = !in_dquote;
// 		else if (*p == '=' && !in_squote && !in_dquote)
// 		{
// 			*p = '\0';
// 			*value = p + 1;
// 			break;
// 		}
// 		p++;
// 	}
// 	p_update(value, p);
// }

// void	printf_sorted_env(char **envp)
// {
// 	int		i;
// 	int		sorted;
// 	char	*tmp;
// 	char	**sorted_env;
	
// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	sorted_env = malloc(sizeof(char *) * (i + 1));
// 	if (!sorted_env)
// 		exit(EXIT_FAILURE);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		sorted_env[i] = envp[i];
// 		i++;
// 	}
// 	sorted_env[i] = NULL;
// 	sorted = 0;
// 	while (!sorted)
// 	{
// 		sorted = 1;
// 		i = 0;
// 		while (sorted_env[i + 1])
// 		{
// 			if (ft_strcmp(sorted_env[i], sorted_env[i + 1]) > 0)
// 			{
// 				tmp = sorted_env[i];
// 				sorted_env[i] = sorted_env[i + 1];
// 				sorted_env[i + 1] = tmp;
// 				sorted = 0;
// 			}
// 			i++;
// 		}
// 	}
// 	i = 0;
// 	while (sorted_env[i])
// 	{
// 		printf("declare -x %s\n", sorted_env[i]);
// 		i++;
// 	}
// 	free(sorted_env);	
// }

// void ft_export(t_cmd *cmd)
// {
// 	int     i;
// 	char    *name;
// 	char    *value;
// 	char	**arg;

// 	arg = cmd->args;
// 	i = 1;
// 	if (!cmd->args[1])
// 		printf_sorted_env(cmd->data->env);
// 	else
// 	{
// 		while (arg[i])
// 		{
// 			parse_arg(arg[i], &name, &value);
// 			update_env(cmd->data->env, name, value, cmd->data->env);
// 			i++;
// 		}
// 	}
// }
