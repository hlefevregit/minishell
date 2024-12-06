
#include "../../inc/minishell.h"

char	*get_var_from_env(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	return (env[i]);
}

char	*get_path(t_cmd *cmd)
{
	int		i;
	char	*dest;
	char	**path;
	char	*tmp;

	i = 0;
	tmp = get_var_from_env(cmd->data->env, "PATH=");
	path = ft_split(tmp + 5, ':');
	tmp = ft_strjoin("/", cmd->name);
	while (path && path[i])
	{
		dest = ft_strjoin(path[i], tmp);
		if (access(dest, F_OK | X_OK) == 0)
		{
			free(tmp);
			ft_free_tab(path);
			return (dest);
		}
		free(dest);
		i++;
	}
	ft_free_tab(path);
	free(tmp);
	return (NULL);
}

void	ft_execve(t_cmd *cmd)
{
	int		ret;
	int		pid;
	char	*tmp_name;

	ret = 0;
	tmp_name = get_path(cmd);
	pid = fork();
	if (pid == 0)
	{
		ret = execve(tmp_name, cmd->args, cmd->data->env) * -127;
		if (tmp_name != cmd->name)
			free(tmp_name);
		free_data(cmd->data);
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	free(tmp_name);
	cmd->data->last_error = WEXITSTATUS(ret);
	if (WEXITSTATUS(ret) == 127)
	{
		printf("%s: %s\n", strerror(errno) ,cmd->args[0]);
		ft_putstr("minishell: no such file or directory: ");
		ft_putendl(cmd->args[0]);
	}
	return ;
}
