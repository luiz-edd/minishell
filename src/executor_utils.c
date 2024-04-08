/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/08 11:09:52 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// usar copia do environ no execve
// fazer expansao de variaveis
// verificar se é builtin só depois de fazer expansao de variaveis
//(variavel pode ser comando ex: var=echo)
void	execute_command(t_tree_node *cmd_node)
{
	t_token	*current;
	char	**cmd_and_args;
	char	*cmd_path;

	current = cmd_node->cmd;
	while (current)
	{
		current->value = expand_vars(current->value);
		current = current->next;
	}
	if (is_builtin(cmd_node->cmd))
		return ;
	// execute_builtin(cmd_node);
	else
	{
		cmd_path = get_cmd_path(cmd_node->cmd);
		cmd_and_args = get_cmd_and_args(cmd_node->cmd);
		if (execve(cmd_path, cmd_and_args, __environ) == -1)
			handle_error(cmd_path);
	}
}

//falta tratar $$ que vira um numero (provavelmente um processo)
char	*expand_vars(char *str)
{
	char	*dollar;
	char	*expanded_var;
	char	*before_var;
	char	*after_var;
	int		i;

	while (strchr(str, '$'))
	{
		dollar = strchr(str, '$');
		if (dollar && dollar[1])
		{
			i = 1;
			while (dollar[i] && dollar[i] != '$')
				i++;
			if (dollar[1] == '$')
				i++;
			expanded_var = getenv(ft_substr(dollar, 1, i - 1));
			before_var = ft_substr(str, 0, dollar - str);
			after_var = ft_substr(dollar, i, ft_strlen(dollar));
			str = ft_strjoin(before_var, expanded_var);
			str = ft_strjoin(str, after_var);
		}
		else
			break ;
	}
	return (str);
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
