#include "../../inc/minishell.h"

int	found(char *env_line, char *env_name)
{
	int	i;

	i = 0;
	while (env_name[i])
	{
		if (env_line[i] != env_name[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_in_env(t_cmd *cmd, char *env_name)
{
	int	size;

	size = ft_tablen(cmd->data->env);
	while (size)
	{
		size--;
		if (found(cmd->data->env[size], env_name) == 1)
			return (size);
	}
	return (0);
}

void	ft_unset(t_cmd *cmd)
{
	int		i;
	int		k;
	char	**new_env;

	k = 1;
	i = 0;
	new_env = NULL;
	while (cmd->args[++i] != NULL)
	{
		k = is_in_env(cmd, cmd->args[i]);
		if (k != 0)
		{
			new_env = ft_tabrmi(cmd->data->env, k);
			if (new_env == NULL)
			{
				printf("alloc failed for new_env");
				return ;
			}
			ft_free_tab(cmd->data->env);
			cmd->data->env = new_env;
		}
		else
			printf("cant unset %s -> name is not valid\n", cmd->args[i]);
	}
}
