/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/25 18:40:11 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// transformar funções de search em search_token_type(t_token *token_list, int type, ...)? Poderia procurar parenteses também no futuro
t_token	*search_and_or(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == AND || current->type == OR)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_token	*search_pipe(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (NULL);
}

//criar tipo novo de token BUILTIN para quando é builtin e possivelmente facilitar a execução?
t_token	*get_cmd_path(t_token *cmd)
{
	t_token	*cmd_path;

	cmd_path = ft_dalloc(sizeof(t_token), 1);
	if (!cmd_path)
		handle_error("failed to allocate memory");
	if (is_builtin(cmd))
	{
		cmd->type = 13; //BUILTIN
		return (cmd);
	}
	else if (*(cmd->value) == '/')
		cmd_path = cmd;
	else if (ft_strchr(cmd->value, '/'))
		cmd_path = search_in_cur_dir();
	else
		cmd_path = search_in_path();
	return (cmd_path);
}

char	*search_in_cur_dir(t_token *cmd)
{

}

char	*search_in_path(t_token *cmd)
{
	
}

int	is_builtin(t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "cd") || !ft_strcmp(cmd->value, "pwd") || !ft_strcmp(cmd->value, "export") || !ft_strcmp(cmd->value, "unset") || !ft_strcmp(cmd->value, "env") || !ft_strcmp(cmd->value, "exit"))
		return (1);
	return (0);
}
