/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:14:16 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/10 17:14:42 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	get_infile(t_mini mini)
{
	int	i;

	i = 0;
	while (mini.token[i].type != T_PIPE)
	{
		if (mini.token[i].type == T_I_FILE)
		{
			mini.infile = open(mini.token[i].value, O_RDONLY, 0777);
			if (mini.infile == -1)
			{
				perror(RED"Error"RESET" : file error\n");
				exit(EXIT_FAILURE);
			}
			dup2(mini.infile, STDIN_FILENO);
		}
	}	
}

int		get_outfile(t_mini mini)
{
	int	i;

	i = 0;
	while (mini.token[i].type && mini.token[i].type != T_AND && mini.token[i].type != T_OR)
	{
		
		if (mini.token[i].type == T_O_FILE)
		{
			mini.outfile = open(mini.token[i].value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (mini.outfile == -1)
			{
				perror(RED"Error"RESET" : file error\n");
				exit(EXIT_FAILURE);
			}
			return (mini.outfile);
		}
		i++;
	}
	return (mini.outfile);
}

void	ft_execute(t_mini)
{
	
}

void	ft_child_proc(t_mini mini)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("Error fork bonus \n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		mini.status = 0;
		ft_execute(mini);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	parse_cmd(t_mini mini)
{
	int	i;
	int num;

	i = 0;
	num = -1;
	mini.outfile = get_outfile(mini);
	while (mini.token[i].type && mini.token[i].type != T_AND && mini.token[i].type != T_OR)
	{
		if (mini.token[i].type == T_PIPE)
		{
			get_infile(mini);
			num = i;
			ft_child_proc(mini);
		}
		i++;
	}
	dup2(mini.outfile, STDOUT_FILENO);
	if (num != -1)
	{
		mini.status = 2;
		ft_execute(mini);
	}	
}*/
