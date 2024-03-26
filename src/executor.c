/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:17:49 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/26 18:09:05 by pehenri2         ###   ########.fr       */
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
	else
	 	execute_command(root);
	return (SUCCESS);
}

int	execute_and(t_tree_node *left, t_tree_node *right)
{
	int	pid;
	int	exit_status;

	exit_status = SUCCESS;
	pid = fork();
	if (pid == 0)
		executor(left);
	else
		waitpid(pid, &exit_status, 0);
	if (exit_status == SUCCESS)
	{
		pid = fork();
		if (pid == 0)
			executor(right);
		else
			waitpid(pid, &exit_status, 0);
	}
	return (exit_status);
}

int	execute_or(t_tree_node *left, t_tree_node *right)
{
	int	pid;
	int	exit_status;

	exit_status = SUCCESS;
	pid = fork();
	if (pid == 0)
		executor(left);
	else
		waitpid(pid, &exit_status, 0);
	if (exit_status != SUCCESS)
	{
		pid = fork();
		if (pid == 0)
			executor(right);
		else
			waitpid(pid, &exit_status, 0);
	}
	return (exit_status);
}

int	execute_pipe(t_tree_node *left, t_tree_node *right)
{
	int	pid;
	int	pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		executor(left);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		executor(right);
	}
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	return (SUCCESS);
}

// colocar funcao de get_path para ser chamada direto aqui em vez de colocar na linked list?
// usar copia do environ no execve
 void	execute_command(t_tree_node *cmd_node)
 {
 	char	**cmd_and_args;
 	char	*cmd_path;

 	//if (cmd_node->redir)
 	//	solve_redirections(cmd_node->redir);
 	cmd_path = cmd_node->cmd->value;
 	cmd_and_args = get_cmd_and_args(cmd_node->cmd->next);
 	execve(cmd_path, cmd_and_args, __environ);
 }
