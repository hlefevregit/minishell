/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:17:49 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/06 15:49:12 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdio.h>
#include <unistd.h>
# include "../libft/includes/libft.h"

# define RESET "\033[0m"

typedef enum e_token
{
	T_PIPE,
	T_OUT_TRUNCATE,
	T_OUT_APPEND,
	T_IN,
	T_HERE_DOC,
	T_WHITESPACE,
	T_NONE,
}	t_token;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				fd;
}					t_lexer;

typedef struct s_data
{
	t_list			*cmds;
	char			**env;
	int				std_in;
	int				std_out;
	int				last_error;
}					t_data;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	t_data			*data;
	t_list			*out;
	int				pipe[2];
	int				pid;
}					t_cmd;

typedef void	(*t_func_cmd)(t_cmd *cmd);


/*         Built-ins                       */
void	ft_cd(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	set_env_var(char **env, char *env_name, char *env_val);
void	set_env(char **env, char *env_name, char *env_val, int p);
void	ft_exit(t_cmd *cmd);
void	ft_export(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	ft_execve(t_cmd *cmd);

int		plus_in_name(char *env_name);
int		already_in_env(char *env_name, t_cmd *cmd);
int		check_env_name(char *env_name);
void	remove_plus(char *str);
char	*get_var_from_env(char **env, char *var);

/*         Utils/signal.c                   */
void	signals_main(void);
void	signals_pipe(void);

/*         Parsing                          */
int		parse_input(t_data *data, char *input);

/*        Parsing/lexer.c             */
t_list	*input_lexer(char *input);
char	*token_to_strs(t_token token);
t_token	get_token(char *str);
int		check_tokens(t_list **tokens);
int		skip_quotes(char *input);
void	swap_quote(char *quote, char c);
int		ft_isquote(char c);

/*        Parsing/lst.c                     */
char	*lst_conv(void *content);
int		is_pipe(void *content);
int		is_arg(void *content);

/*       Parsing/free.c                   */
void	free_cmd(void *ptr);
void	free_lexer(void *ptr);
t_data	*init_data(char **environ);
void	free_data(t_data *data);


void	here_doc(char *limiter);

#endif
