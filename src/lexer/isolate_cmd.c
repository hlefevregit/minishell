// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   isolate_cmd.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/16 16:33:55 by hulefevr          #+#    #+#             */
// /*   Updated: 2024/09/16 16:53:54 by hulefevr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// static	int count_commands(t_mini mini)
// {
//     int count;
//     int i;
    
// 	count = 1;
// 	i = 0;
//     while (i < mini.num_tokens)
// 	{
//         if (mini.token[i].type == T_PIPE)
//             count++;
//         i++;
//     }
//     return (count);
// }

// static char	*copy_command(t_token *token, int start, int end)
// {
//     char *cmd;
//     int i;
//     int j;

// 	i = start;
// 	j = 0;
//     cmd = malloc((end - start + 1) * sizeof(char));
//     if (!cmd)
//         return (NULL);
//     while (i < end)
// 	{
//         cmd[j] = ft_strdup(token[i].value);
//         j++;
//         i++;
//     }
//     cmd[j] = NULL;
//     return (cmd);
// }

// char	**isolate_cmd(t_mini mini)
// {
//     int i;
//     int cmd_start;
//     int cmd_index;
//     char **commands;
    
// 	i = 0;
// 	cmd_start = 0;
// 	cmd_index = 0;
//     commands = malloc((count_commands(mini) + 1) * sizeof(char **));
//     if (!commands)
//         return (NULL);
//     while (i < mini.num_tokens)
// 	{
//         if (mini.token[i].type == T_PIPE)
// 		{
//             commands[cmd_index] = copy_command(mini.token, cmd_start, i);
//             cmd_index++;
//             cmd_start = i + 1;
//         }
//         i++;
//     }
//     commands[cmd_index] = copy_command(mini.token, cmd_start, mini.num_tokens);
// 	if (!commands[cmd_index])
// 	{
// 		while (cmd_index-- > 0)
// 			free(commands[cmd_index]);
// 		free(commands);
// 		return (NULL);
// 	}
//     commands[cmd_index + 1] = NULL;
//     return (commands);
// }
