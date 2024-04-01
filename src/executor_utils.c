/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/01 17:06:09 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// usar copia do environ no execve
// fazer expansao de variaveis
// verificar se é builtin só depois de fazer expansao de variaveis 
//(variavel pode ser comando ex: var=echo)
void	execute_command(t_tree_node *cmd_node)
{
	char	**cmd_and_args;
	char	*cmd_path;

	// expand_vars(cmd_node->cmd);
	if (is_builtin(cmd_node->cmd))
		return ;
		//execute_builtin(cmd_node);
	else
	{
		cmd_path = get_cmd_path(cmd_node->cmd);
		cmd_and_args = get_cmd_and_args(cmd_node->cmd);
		if (execve(cmd_path, cmd_and_args, __environ) == -1)
		{
			perror(cmd_path);
			ft_free_memory();
			exit(FAILURE);
		}
	}
}

// mudei retorno para 0 só para não executar as builtins por enquanto
int	is_builtin(t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "cd")
		|| !ft_strcmp(cmd->value, "pwd") || !ft_strcmp(cmd->value, "export")
		|| !ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "env")
		|| !ft_strcmp(cmd->value, "exit"))
		return (0);
	return (0);
}

// comando terminar com barra dá problema?
char	*get_cmd_path(t_token *cmd)
{
	char	*cmd_path;

	if (ft_strchr(cmd->value, '/'))
	{
		cmd_path = cmd->value;
		cmd->value = ft_strrchr(cmd->value, '/') + 1;
	}
	else
		cmd_path = search_in_path(cmd);
	return (cmd_path);
}

// verificar permissoes do arquivos com access
// getenv retorna erro? Se der unset na variavel por exemplo?
char	*search_in_path(t_token *cmd)
{
	char	*cmd_path;
	char	**paths;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		handle_error("failed to allocate memory");
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd->value);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	cmd_path = cmd->value;
	return (cmd_path);
}

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
