/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:51:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 14:49:32 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	isset_env(char *env, t_mini mini)
{
	int	i;

	i = -1;
	while (mini.envp[++i] != 0)
	{
		if (ft_strncmp(mini.envp[i], env, ft_strlen(env)) == 0)
			return (true);
	}
	return (false);
}

void	add_value(char **str, char *new_value)
{
	char	*tmp;

	tmp = ft_strjoin(*str, new_value);
	free(*str);
	*str = tmp;
}

void	update_env(char *env, char *new_value, t_mini mini)
{
	int		i;
	char	*tmp;

	i = 0;
	if (isset_env(env, mini))
	{
		tmp = ft_strdup(env);
		add_value(&tmp, "=");
		add_value(&tmp, new_value);
		while (mini.envp[i]
			&& ft_strncmp(mini.envp[i], env, ft_strlen(env)) != 0)
			i++;
		free(mini.envp[i]);
		mini.envp[i] = ft_strdup(tmp);
		free(tmp);
	}
}

bool	ft_streql(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (false);
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

size_t	ft_count_char(const char *str, char c)
{
	int	j;

	j = 0;
	while (*str)
	{
		if (*str == c)
			j++;
		str++;
	}
	return (j);
}

char	*get_pwd(t_mini mini)
{
	char	buffer[4096];
	char	*pwd;

	if (getcwd(buffer, 4096) == 0)
	{		
		pwd = find_in_env("PWD", mini.envp);
		return (pwd);
	}
	return (ft_strdup(buffer));
}

static int	try_chdir(char *tmp, char *saved_pwd, char **av, t_mini mini)
{
	struct stat	buffer;
	int			status;
	char		*pwd;

	if (chdir(tmp) == -1)
	{
		chdir(saved_pwd);
		status = stat(*av, &buffer);
		if (status == -1)
			ft_error2("cd", av[0], "No such file or directory");
		else if (status == 0)
			ft_strerror("cd Not a directory");
		return (1);
	}
	pwd = get_pwd(mini);
	update_env("PWD", pwd, mini);
	update_env("OLDPWD", saved_pwd, mini);
	free(pwd);
	return (0);
}

static void	go(char *env_name, char **av, t_mini mini)
{
	char	*saved_pwd;
	char	*env_value;

	saved_pwd = get_pwd(mini);
	env_value = find_in_env(env_name, mini.envp);
	try_chdir(env_value, saved_pwd, av, mini);
	free(saved_pwd);
	free(env_value);
}

static bool	is_arg_count_valid(char **av, t_mini mini)
{
	char	*pwd;

	if (count_array(av) > 1)
	{
		ft_strerror("too many arguments");
		return (false);
	}
	else if (count_array(av) == 1)
	{
		pwd = get_pwd(mini);
		if (ft_count_char(av[0], '/') == ft_strlen(av[0]))
			try_chdir("/", pwd, av, mini);
		else if (ft_streql(av[0], "-"))
		{
			go("OLDPWD", av, mini);
			printf("%s\n", pwd);
		}
		free(pwd);
		if (ft_count_char(av[0], '/') == ft_strlen(av[0])
			|| ft_streql(av[0], "-"))
			return (false);
	}
	return (true);
}

static void	add_prefix(char **str, char *prefix)
{
	char	*temp;

	temp = ft_strdup(prefix);
	add_value(&temp, *str);
	free(*str);
	*str = temp;
}

void	ft_cd(char **av, t_mini mini)
{
	char	**splitted;
	int		i;
	char	*saved_pwd;

	av++;
	i = -1;
	if (!is_arg_count_valid(av, mini))
		return ;
	splitted = ft_split(*av, '/');
	if (!splitted || count_array(splitted) == 0)
		go("HOME", av, mini);
	saved_pwd = get_pwd(mini);
	while (splitted[++i])
	{
		if (i == 0 && av[0][0] == '/')
			add_prefix(&splitted[i], "/");
		if (try_chdir(splitted[i], saved_pwd, av, mini))
			break ;
	}
	free(saved_pwd);
	free_double(splitted);
}