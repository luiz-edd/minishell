/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/23 21:42:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to-do se o comando nao tiver pipe, executar sem dar fork
// to-do tratar mensagens de erro
// to-do algumas builtin mudam as variaveis de ambiente, como cd muda a HOME
// no momento todas as builtins estao retornando SUCCESS ou o o retorno de
// handle_error();
// !!!!!! mudar __environ
int	execute_command(t_tree_node *cmd_node)
{
	t_token	*current;
	char	**cmd_and_args;
	char	*cmd_path;
	int		pid;
	int		exit_status;

	exit_status = SUCCESS;
	current = cmd_node->cmd;
	while (current)
	{
		current->value = expand_vars(current->value);
		current->value = remove_quotes(current->value);
		if (ft_strchr(current->value, ' '))
			retokenize(&current);
		current = current->next;
	}
	if (is_builtin(cmd_node->cmd))
	{
		exit_status = execute_builtin(cmd_node->cmd);
		return (exit_status);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			exit(handle_error("fork"));
		if (pid == 0)
		{
			cmd_path = get_cmd_path(cmd_node->cmd);
			cmd_and_args = get_cmd_and_args(cmd_node->cmd);
			if (execve(cmd_path, cmd_and_args, __environ) == -1)
				exit(throw_error(cmd_path));
		}
		else
			waitpid(pid, &exit_status, 0);
	}
	return (exit_status);
}

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

char	*search_in_path(t_token *cmd)
{
	char	*cmd_path;
	char	*path_env;
	char	**paths;
	int		i;

	path_env = getenv("PATH");
	if (!path_env)
		handle_error("getenv");
	paths = ft_split(path_env, ':');
	if (!paths)
		handle_error("failed to allocate memory");
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd->value);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
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
