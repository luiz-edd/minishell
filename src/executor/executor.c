/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:17:49 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/24 17:25:10 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//verificar se temos permissao de acessar o binario
int	execute(t_tree_node *root)
{
	if (root->cmd->type == AND)
		return (execute_and(root->left, root->right));
	else if (root->cmd->type == OR)
		return (execute_or(root->left, root->right));
	else if (root->cmd->type == PIPE)
		return (execute_pipe(root->left, root->right));
	else if (root->cmd->type >= REDIR_APPEND && root->cmd->type <= REDIR_OUT)
		return (execute_redirect(root->left, root->right, root->cmd->type));
	else
		return (execute_command(root));
}

int	execute_and(t_tree_node *left, t_tree_node *right)
{
	int	exit_status;

	exit_status = set_exit_status(execute(left));
	revert_fds();
	if (exit_status == SUCCESS)
		return (set_exit_status(execute(right)));
	return (exit_status);
}

int	execute_or(t_tree_node *left, t_tree_node *right)
{
	int	exit_status;

	exit_status = set_exit_status(execute(left));
	revert_fds();
	if (exit_status != SUCCESS)
		return (set_exit_status(execute(right)));
	return (exit_status);
}

int	execute_pipe(t_tree_node *left, t_tree_node *right)
{
	int	child_pid[2];
	int	pipe_fd[2];
	int	exit_status;

	pipe(pipe_fd);
	child_pid[0] = fork();
	if (child_pid[0] == 0)
	{
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close_pipe(pipe_fd);
		exit_status = execute(left);
		ft_free_memory();
		exit(exit_status);
	}
	child_pid[1] = fork();
	if (child_pid[1] == 0)
	{
		dup2(pipe_fd[READ], STDIN_FILENO);
		close_pipe(pipe_fd);
		exit_status = execute(right);
		ft_free_memory();
		exit(exit_status);
	}
	close_pipe(pipe_fd);
	waitpid(child_pid[0], &exit_status, 0);
	waitpid(child_pid[1], &exit_status, 0);
	return (exit_status);
}

int	execute_redirect(t_tree_node *left, t_tree_node *right, int redir_type)
{
	int	fd;
	int	exit_status;

	exit_status = -1;
	fd = -1;
	right->cmd->value = expand_vars(right->cmd->value);
	right->cmd->value = remove_quotes(right->cmd->value);
	if (redir_type == REDIR_APPEND)
		fd = open(right->cmd->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		fd = open(right->cmd->value, O_RDONLY, 0644);
	else if (redir_type == REDIR_OUT)
		fd = open(right->cmd->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (handle_error(right->cmd->value));
	if (redir_type == REDIR_APPEND || redir_type == REDIR_OUT)
		exit_status = dup2(fd, STDOUT_FILENO);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		exit_status = dup2(fd, STDIN_FILENO);
	if (exit_status == -1)
		return (handle_error("dup2"));
	close(fd);
	if (!left->cmd)
		return (0);
	return (execute(left));
}
