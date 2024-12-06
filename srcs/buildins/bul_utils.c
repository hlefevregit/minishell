
#include "../../inc/minishell.h"

int	plus_in_name(char *env_name)
{
	int	i;

	i = -1;
	while (env_name[++i] && env_name[i] != '=')
		if (env_name[i] == '+')
			return (1);
	return (0);
}

void	remove_plus(char *str)
{
	char	*plus;

	plus = ft_strchr(str, '+');
	if (plus)
		ft_memmove(plus, plus + 1, ft_strlen(plus));
}

int	already_in_env(char *env_name, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->data->env[i] != NULL)
	{
		if (ft_strncmp(cmd->data->env[i], env_name,
				ft_strchr(env_name, '=') - env_name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_env_name(char *env_name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(env_name[0]) && env_name[0] != '_')
		return (0);
	while (env_name[i] != '=')
	{
		if (env_name[i + 1] == '=' && env_name[i] == '+')
			return (1);
		if (!ft_isalpha(env_name[i]) && !ft_isdigit(env_name[i]))
		{
			if (env_name[i] != ' ' && env_name[i] != '_')
				return (0);
		}
		if (env_name[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

char	*find_in_env(char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], cmd, ft_strlen(cmd)) == 0
			&& envp[i][ft_strlen(cmd)] == '=')
			return (envp[i] + ft_strlen(cmd) + 1);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**split_path;
	char	*o_path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i])
	{
		part_path = ft_strjoin(split_path[i], "/");
		o_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(o_path, F_OK | X_OK) == 0)
		{
			free_double(split_path);
			return (o_path);
		}
		free(o_path);
		i++;
	}
	free_double(split_path);
	return (cmd);
}
