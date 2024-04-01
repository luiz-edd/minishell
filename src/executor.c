/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:17:49 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/01 17:14:27 by pehenri2         ###   ########.fr       */
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

// criar funcao variadica de fechar fds para diminuir linhas?
void	execute_pipe(t_tree_node *left, t_tree_node *right)
{
	int	child_pid[2];
	int	pipe_fd[2];
	int	exit_status;

	pipe(pipe_fd);
	child_pid[0] = fork();
	if (child_pid[0] == 0)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		executor(left);
	}
	child_pid[1] = fork();
	if (child_pid[1] == 0)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
		executor(right);
	}
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	waitpid(child_pid[0], &exit_status, 0);
	waitpid(child_pid[1], &exit_status, 0);
	ft_free_memory();
	exit(WEXITSTATUS(exit_status));
}

//se der algum erro não deve executar o comando
void	execute_redirect(t_tree_node *left, t_tree_node *right, int redir_type)
{
	int	fd;

	fd = -1;
	if (redir_type == REDIR_APPEND)
		fd = open(right->cmd->value, O_CREAT | O_APPEND | O_WRONLY, 0666);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		fd = open(right->cmd->value, O_RDONLY, 0666);
	else if (redir_type == REDIR_OUT)
		fd = open(right->cmd->value, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd == -1)
	{
		perror(right->cmd->value);
		exit(FAILURE);
	}
	if (redir_type == REDIR_APPEND || redir_type == REDIR_OUT)
		dup2(fd, STDOUT_FILENO);
	else if (redir_type == REDIR_HEREDOC || redir_type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	executor(left);
}
