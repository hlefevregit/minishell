#include "../../inc/minishell.h"

char	*lst_conv(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (ft_strdup(lexer->str));
}

int	is_pipe(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (lexer->token == PIPE);
}

int	is_arg(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (lexer->token == T_NONE);
}
