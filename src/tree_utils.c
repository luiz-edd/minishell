/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/23 15:53:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// transformar funções em search_token_type(t_token *token_list, int type, ...)? Poderia procurar parenteses também no futuro
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

//colocar funções na libft junto com create_token (renomeado para dbl_lst_new) e append_token (dbl_lst_add_back) usando void* e dando cast durante o minishell?
void	dbl_lst_add_back(t_token *token_list, t_token *new)
{
	t_token	*current;

	if (!token_list)
	{
		token_list = new;
		return ;
	}
	current = token_list;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
}

void	dbl_lst_add_front(t_token *token_list, t_token *new)
{
	if (!token_list)
	{
		token_list = new;
		return ;
	}
	token_list->prev = new;
	new->next = token_list;
	token_list = new;
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
