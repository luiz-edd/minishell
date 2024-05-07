/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:35:23 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/07 14:48:41 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//mudar para dar restore no fim
int	execute_redirect(t_tree_node *left, t_tree_node *right, int redir_type)
{
	int		fd;
	int		std_fd[2];
	int		exit_status;
	char	*before_expansion;

	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	fd = -1;
	before_expansion = right->cmd->value;
	expand_command(right);
	if (right->cmd->next || *(right->cmd->value) == '\0')
		return (!!ft_fprintf(STDERR_FILENO, "%s: ambiguous redirect\n",
				before_expansion));
	if (open_redir_file(right, redir_type, &fd) != SUCCESS)
		return (FAILURE);
	if (dup2_redir_file(redir_type, &fd) != SUCCESS)
		return (FAILURE);
	if (!left->cmd)
		return (SUCCESS);
	exit_status = executor(left);
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
	return (exit_status);
}

int	open_redir_file(t_tree_node *right, int redir_type, int *fd)
{
	if (redir_type == REDIR_APPEND)
		*fd = open(right->cmd->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		*fd = open(right->cmd->value, O_RDONLY, 0644);
	else if (redir_type == REDIR_OUT)
		*fd = open(right->cmd->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*fd == -1)
		return (handle_error(right->cmd->value));
	return (SUCCESS);
}

int	dup2_redir_file(int redir_type, int *fd)
{
	int	exit_status;

	exit_status = -1;
	if (redir_type == REDIR_APPEND || redir_type == REDIR_OUT)
		exit_status = dup2(*fd, STDOUT_FILENO);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		exit_status = dup2(*fd, STDIN_FILENO);
	if (exit_status == -1)
		return (handle_error("dup2"));
	close(*fd);
	return (SUCCESS);
}
