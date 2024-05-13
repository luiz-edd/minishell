/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/13 19:09:12 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// !!!!!! mudar __environ
int	execute_command(t_tree_node *cmd_node)
{
	int		pid;
	int		exit_status;

	exit_status = 0;
	expand_command(cmd_node);
	if (*(cmd_node->cmd->value) == '\0')
		return (exit_status);
	if (is_builtin(cmd_node->cmd))
		return (execute_builtin(cmd_node->cmd));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(handle_error("fork"));
		setup_fork_signal_handlers(pid);
		if (pid == 0)
			run_command_in_child_process(cmd_node->cmd);
		wait_child_status(pid, &exit_status);
		return (exit_status);
	}
}

void	run_command_in_child_process(t_token *cmd)
{
	char	**cmd_and_args;
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd);
	cmd_and_args = get_cmd_and_args(cmd);
	if (execve(cmd_path, cmd_and_args, __environ) == -1)
		exit(throw_error(cmd_path));
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
		exit(!!write(STDERR_FILENO, "minishell: PATH not set\n", 24));
	paths = ft_split(path_env, ':');
	if (!paths)
		exit(!!write(STDERR_FILENO, "minishell: failed to retrieve PATH\
 directories\n", 47));
	i = 0;
	while (paths[i])
	{
		ft_strlcat(paths[i], "/", ft_strlen(paths[i]) + 2);
		cmd_path = ft_strjoin(paths[i], cmd->value);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	ft_fprintf(STDERR_FILENO, "%s: command not found\n", cmd->value);
	exit(127);
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
		if (*(current->value) != '\0')
			cmd_and_args[i++] = current->value;
		current = current->next;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}
