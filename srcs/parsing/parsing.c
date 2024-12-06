#include "../../inc/minishell.h"


void	remove_quotes(void *content)
{
	t_lexer	*token;
	int		i;
	char	quote;

	quote = 0;
	token = content;
	if (token->token != T_NONE)
		return ;
	i = 0;
	while (token->str[i])
	{
		if (ft_isquote(token->str[i]) && (!quote || quote == token->str[i]))
		{
			swap_quote(&quote, token->str[i]);
			ft_memmove(token->str + i, token->str + i + 1,
				ft_strlen(token->str + i + 1) + 1);
			continue ;
		}
		i++;
	}
}

void	create_cmd(t_data *data, t_list *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	ft_lstiter(tokens, &remove_quotes);
	cmd->args = ft_lsttotab_if(tokens, &is_arg, &lst_conv);
	ft_lstrm_if(&tokens, &is_arg, &free_lexer);
	cmd->out = tokens;
	cmd->name = cmd->args[0];
	cmd->data = data;
	ft_lstadd_back(&data->cmds, ft_lstnew(cmd));
}

int	parse_input(t_data *data, char *input)
{
	t_list	*tokens;
	t_list	**splitted_tokens;
	int		i;

	if (!input[0])
		return (1);
	tokens = input_lexer(input);
	if (check_tokens(&tokens) == 0)
		return (0);
	splitted_tokens = ft_lstsplit(tokens, &is_pipe, &free_lexer);
	i = 0;
	while (splitted_tokens[i])
	{
		create_cmd(data, splitted_tokens[i]);
		i++;
	}
	free(splitted_tokens);
	return (1);
}
