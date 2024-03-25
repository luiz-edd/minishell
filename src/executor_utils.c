/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/25 18:39:26 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_and_args(t_tree_node *cmd_node)
{
	t_token	*current;
	char	**cmd_and_args;
	int		i;

	cmd_and_args = ft_dalloc(sizeof(char *), (token_lst_size(current) + 1));
	if (!cmd_and_args)
		handle_error("failed to allocate memory");
	i = 0;
	current = cmd_node->cmd;
	while (current)
	{
		cmd_and_args[i] = current->value;
		current = current->next;
		i++;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}

//colocar handle_heredoc (se tiver heredoc) antes de chamar o executor a primeira vez
//para deixar os arquivos criados e escritos e só abrir para ler aqui nessa parte com open_here_doc()
void	solve_redirections(t_tree_node *cmd_node)
{
	t_token	*current;
	int		fd;

	current = cmd_node->redir;
	while (current)
	{
		if (current->type == REDIR_APPEND)
			fd = open(current->next->value, O_CREAT | O_APPEND, 0644);
		else if (current->type == REDIR_HEREDOC)
			fd = open_here_doc();
		else if (current->type == REDIR_IN)
			fd = open(current->next->value, O_RDONLY, 0644);
		else if (current->type == REDIR_OUT)
			fd = open(current->next->value, O_CREAT | O_TRUNC, 0644);
		if (current->type == REDIR_APPEND || current->type == REDIR_OUT)
			dup2(fd, STDOUT_FILENO);
		else if (current->type == REDIR_HEREDOC || current->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		current = current->next;
	}
}
