/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/15 18:30:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to-do se o comando nao tiver pipe, executar sem dar fork
// to-do tratar mensagens de erro
// to-do algumas builtin mudam as variaveis de ambiente, como cd muda a HOME
// no momento todas as builtins estao retornando SUCCESS ou o o retorno de handle_error();
void	execute_command(t_tree_node *cmd_node)
{
	t_token	*current;
	char	**cmd_and_args;
	char	*cmd_path;

	current = cmd_node->cmd;
	while (current)
	{
		current->value = expand_vars(current->value);
		current->value = remove_quotes(current->value);
		current = current->next;
	}
	if (is_builtin(cmd_node->cmd))
		exit(execute_builtin(cmd_node->cmd));
	{
		cmd_path = get_cmd_path(cmd_node->cmd);
		cmd_and_args = get_cmd_and_args(cmd_node->cmd);
		if (execve(cmd_path, cmd_and_args, __environ) == -1)
			exit(handle_error(cmd_path));
	}
}

char	*expand(char *start, char *dollar, char *after_var)
{
	char	*expanded_var;
	char	*before_var;
	char	*str;

	expanded_var = getenv(ft_substr(dollar, 1, after_var - dollar - 1));
	before_var = ft_substr(start, 0, dollar - start);
	str = ft_strjoin(before_var, expanded_var);
	str = ft_strjoin(str, after_var);
	return (str);
}

char	*expand_vars(char *str)
{
	char	*start;
	char	*dollar;
	char	*after_var;

	start = str;
	dollar = NULL;
	after_var = NULL;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
		}
		if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
			{
				if (*str == '$')
				{
					dollar = str++;
					while (*str && *str != '\'' && *str != '\"' && *str != '$')
						str++;
					after_var = str;
					return (expand(start, dollar, after_var));
				}
				str++;
			}
		}
		if (*str == '$')
		{
			dollar = str++;
			while (*str && *str != '\'' && *str != '\"' && *str != '$')
				str++;
			after_var = str;
			return (expand(start, dollar, after_var));
		}
		dollar = NULL;
		after_var = NULL;
		str++;
	}
	return (start);
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
