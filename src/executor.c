/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:17:49 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/23 15:47:55 by pehenri2         ###   ########.fr       */
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
}

int	execute_and(t_tree_node *left, t_tree_node *right)
{
	//fork
	//executor(left);
	//wait return
	//if return is 0 (SUCCESS)
		//fork
		//executor(right);
}

int	execute_or(t_tree_node *left, t_tree_node *right)
{
	//fork
	//executor(left);
	//wait return
	//if return is != 0 (FAILURE)
		//fork
		//executor(right);
}

int	execute_pipe(t_tree_node *left, t_tree_node *right)
{
	//pipe
	//fork
	//left:
		//close pipe[READ], dup2(STDOUT, pipe[WRITE])
		//executor(left);
	//fork
	//right:
		//close pipe[WRITE], dup2(STDIN, pipe[READ])
		//executor(right);
}

//colocar funcao de get_path para ser chamada direto aqui em vez de colocar na linked list?
int	execute_command(t_tree_node *cmd_node)
{
	char	**cmd_and_args;
	char	*cmd_path;

	cmd_path = cmd_node->cmd->value;
	cmd_node->cmd = cmd_node->cmd->next;
	cmd_and_args = get_cmd_and_args(cmd_node);
	if (cmd_node->redir)
		solve_redirections(cmd_node->redir);
	execve(cmd_path, cmd_and_args, environ);
}
