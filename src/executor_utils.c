/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/27 19:12:27 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 char	**get_cmd_and_args(t_token *cmd)
 {
 	t_token	*current;
 	char	**cmd_and_args;
 	int		i;

 	cmd_and_args = ft_dalloc(sizeof(char *), (token_lst_get_size(cmd) + 1));
 	if (!cmd_and_args)
 		handle_error("failed to allocate memory");
 	i = 0;
 	current = cmd;
 	while (current)
 	{
 		cmd_and_args[i] = current->value;
 		current = current->next;
 		i++;
 	}
 	cmd_and_args[i] = NULL;
 	return (cmd_and_args);
 }

 void	solve_redirections(t_token *redir)
 {
 	t_token	*current;
 	int		fd;

 	current = redir;
 	while (current)
 	{
 		if (current->type == REDIR_APPEND)
 			fd = open(current->next->value, O_CREAT | O_APPEND, 0666);
 		else if (current->type == REDIR_HEREDOC || current->type == REDIR_IN)
 			fd = open(current->next->value, O_RDONLY, 0666);
 		else if (current->type == REDIR_OUT)
 			fd = open(current->next->value, O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
            perror("open");
            return ;
        }
 		if (current->type == REDIR_APPEND || current->type == REDIR_OUT)
 			dup2(fd, STDOUT_FILENO);
 		else if (current->type == REDIR_HEREDOC || current->type == REDIR_IN)
 			dup2(fd, STDIN_FILENO);
 		current = current->next;
 	}
 }
