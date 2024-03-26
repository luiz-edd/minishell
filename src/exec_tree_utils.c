/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/25 18:55:52 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// transformar funções de search em search_token_type(t_token *token_list,
	int type, ...)? Poderia procurar parenteses também no futuro
t_token	*search_and_or(t_token *token_list)
{
	t_token	*current;
	size_t	size;

	current = token_lst_get_last(token_list);
	while (current)
	{
		if (current->type == AND || current->type == OR)
			return (current);
		current = current->prev;
	}
	return (NULL);
}

t_token	*search_pipe(t_token *token_list)
{
	t_token	*current;

	current = current = token_lst_get_last(token_list);
	;
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->prev;
	}
	return (NULL);
}

// criar tipo novo de token BUILTIN para quando é builtin e possivelmente facilitar a execução?
t_token	*get_cmd_path(t_token *cmd)
{
	// colocar o type desse token como CMD_PATH, talvez numero 14
	t_token	*cmd_path;

	cmd_path = ft_dalloc(sizeof(t_token), 1);
	
	if (!cmd_path)
		handle_error("failed to allocate memory");
	if (is_builtin(cmd))
	{
		cmd->type = 13; // BUILTIN
		return (cmd);
	}
	else if (*(cmd->value) == '/')
		cmd_path = cmd;
	else if (ft_strchr(cmd->value, '/'))
		cmd_path = search_in_cur_dir(cmd);
	else
		cmd_path = search_in_path(cmd);
	return (cmd_path);
}

// to do
t_token	*search_in_cur_dir(t_token *cmd)
{
	t_token	*cmd_path;

	(void)cmd;
	cmd_path = ft_dalloc(sizeof(t_token), 1);
	if (!cmd_path)
		handle_error("failed to allocate memory");
	return (cmd_path);
}

// to do
t_token	*search_in_path(t_token *cmd)
{
	t_token	*cmd_path;

	(void)cmd;
	cmd_path = ft_dalloc(sizeof(t_token), 1);
	if (!cmd_path)
		handle_error("failed to allocate memory");
	return (cmd_path);
}

int	is_builtin(t_token *cmd)
{
	if (!ft_strncmp(cmd->value, "echo", 4) || !ft_strncmp(cmd->value, "cd", 2)
		|| !ft_strncmp(cmd->value, "pwd", 3) || !ft_strncmp(cmd->value,
			"export", 6) || !ft_strncmp(cmd->value, "unset", 5)
		|| !ft_strncmp(cmd->value, "env", 3) || !ft_strncmp(cmd->value, "exit",
			4))
		return (1);
	return (0);
}
