/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:17:49 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/16 15:42:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_tree_node *root)
{
	if (root->cmd->type == AND)
		execute_and(root->left, root->right);
	else if (root->cmd->type == OR)
		execute_or(root->left, root->right);
	else if (root->cmd->type == PIPE)
		execute_pipe(root->left, root->right);
	else if (root->cmd->type >= REDIR_APPEND && root->cmd->type <= REDIR_OUT)
		execute_redirect(root->left, root->right, root->cmd->type);
	else
		execute_command(root);
	return (SUCCESS);
}

void	execute_and(t_tree_node *left, t_tree_node *right)
{
	int	child_pid;
	int	exit_status;

	exit_status = SUCCESS;
	child_pid = fork();
	if (child_pid == 0)
		executor(left);
	else
		waitpid(child_pid, &exit_status, 0);
	if (exit_status == SUCCESS)
	{
		child_pid = fork();
		if (child_pid == 0)
			executor(right);
		else
			waitpid(child_pid, &exit_status, 0);
	}
	ft_free_memory();
	exit(WEXITSTATUS(exit_status));
}

void	execute_or(t_tree_node *left, t_tree_node *right)
{
	int	child_pid;
	int	exit_status;

	exit_status = SUCCESS;
	child_pid = fork();
	if (child_pid == 0)
		executor(left);
	else
		waitpid(child_pid, &exit_status, 0);
	if (exit_status != SUCCESS)
	{
		child_pid = fork();
		if (child_pid == 0)
			executor(right);
		else
			waitpid(child_pid, &exit_status, 0);
	}
	ft_free_memory();
	exit(WEXITSTATUS(exit_status));
}

void	execute_pipe(t_tree_node *left, t_tree_node *right)
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
		executor(left);
	}
	child_pid[1] = fork();
	if (child_pid[1] == 0)
	{
		dup2(pipe_fd[READ], STDIN_FILENO);
		close_pipe(pipe_fd);
		executor(right);
	}
	close_pipe(pipe_fd);
	waitpid(child_pid[0], &exit_status, 0);
	waitpid(child_pid[1], &exit_status, 0);
	ft_free_memory();
	exit(WEXITSTATUS(exit_status));
}

void	execute_redirect(t_tree_node *left, t_tree_node *right, int redir_type)
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
		handle_error(right->cmd->value);
	if (redir_type == REDIR_APPEND || redir_type == REDIR_OUT)
		exit_status = dup2(fd, STDOUT_FILENO);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		exit_status = dup2(fd, STDIN_FILENO);
	if (exit_status == -1)
		handle_error("dup2");
	executor(left);
}
