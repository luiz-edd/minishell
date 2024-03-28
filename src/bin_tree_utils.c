/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/28 16:50:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// transformar funções de search em search_token_type(t_token *token_list,
//	int type, ...)? Poderia procurar parenteses também no futuro
t_token	*search_and_or(t_token *token_list)
{
	t_token	*current;

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

	current = token_lst_get_last(token_list);
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		current = current->prev;
	}
	return (NULL);
}

// comando terminar com barra?
t_token	*get_cmd_path(t_token *cmd)
{
	t_token	*cmd_path;

	cmd_path = ft_dalloc(sizeof(t_token), 1);
	if (!cmd_path)
		handle_error("failed to allocate memory");
	//if (is_builtin(cmd))
	//{
	//	cmd->type = BUILTIN;
	//	cmd_path->value = cmd->value;
	//}
	else if (ft_strchr(cmd->value, '/'))
	{
		cmd_path->value = cmd->value;
		if (*(ft_strrchr(cmd->value, '/') + 1) != '\0')
			cmd->value = ft_strrchr(cmd->value, '/') + 1;
	}
	else
		cmd_path = search_in_path(cmd);
	return (cmd_path);
}

// verificar permissoes do arquivos
t_token	*search_in_path(t_token *cmd)
{
	t_token	*cmd_path;
	char	**paths;
	int		i;

	(void)cmd;
	cmd_path = ft_dalloc(sizeof(t_token), 1);
	if (!cmd_path)
		handle_error("failed to allocate memory");
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		handle_error("failed to allocate memory");
	i = 0;
	while (paths[i])
	{
		cmd_path->value = ft_strjoin(paths[i], "/");
		cmd_path->value = ft_strjoin(cmd_path->value, cmd->value);
		if (access(cmd_path->value, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	cmd_path->value = cmd->value;
	return (cmd_path);
}

int	is_builtin(t_token *cmd)
{
	if (!ft_strcmp(cmd->value, "echo") || !ft_strcmp(cmd->value, "cd")
		|| !ft_strcmp(cmd->value, "pwd") || !ft_strcmp(cmd->value,
			"export") || !ft_strcmp(cmd->value, "unset")
		|| !ft_strcmp(cmd->value, "env") || !ft_strcmp(cmd->value, "exit"))
		return (1);
	return (0);
}
