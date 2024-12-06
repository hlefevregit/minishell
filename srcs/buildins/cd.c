
#include "../../inc/minishell.h"

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		n_args;

	n_args = ft_tablen(cmd->args);
	if (n_args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		cmd->data->last_error = 1;
		return ;
	}
	if (n_args == 1)
		path = get_var_from_env(cmd->data->env, "HOME=");
	else
		path = cmd->args[1];
	cmd->data->last_error = chdir(path);
}
