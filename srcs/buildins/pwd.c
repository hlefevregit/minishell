
#include "../../inc/minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = get_var_from_env(cmd->data->env, "PWD");
	printf("%s\n", pwd + 4);
}
