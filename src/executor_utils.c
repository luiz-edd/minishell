/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/03 16:01:31 by leduard2         ###   ########.fr       */
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
			handle_error(cmd_path);
	}
}

void	expand_vars(t_token *cmd)
{
	t_token	*current;
	char	*dollar;
	char	*expanded;
	char	*before_dollar;
	char	*after_dollar;
	int		i;

	i = 1;
	current = cmd;
	while (current)
	{
		dollar = strchr(current->value, '$');
		while (dollar)
		{
			dollar = strchr(current->value, '$');
			if (dollar && dollar[1])
			{
				while (dollar[i] && dollar[i] != '$')
				{
					i++;
				}
				expanded = getenv(ft_substr(dollar, 1, i - 1));
				if (expanded)
				{
					before_dollar = ft_substr(current->value, 0, current->value
							- dollar);
					after_dollar = ft_substr(dollar, i, ft_strlen(dollar));
					current->value = ft_strjoin(before_dollar, expanded);
					current->value = ft_strjoin(current->value, after_dollar);
				}
			}
		}
		current = current->next;
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
		handle_error("failed to get PATH environment variable");
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
