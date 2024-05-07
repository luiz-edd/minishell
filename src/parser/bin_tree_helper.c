/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/07 15:18:22 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*search_and_or(t_token *token_list)
{
	t_token	*current;
	int		parentesis;

	current = token_lst_get_last(token_list);
	while (current)
	{
		if (current->type == AND || current->type == OR)
			return (current);
		if (current->type == CLOSE_PAREN)
		{
			parentesis = 1;
			while (parentesis)
			{
				current = current->prev;
				if (current->type == CLOSE_PAREN)
					parentesis++;
				else if (current->type == OPEN_PAREN)
					parentesis--;
			}
		}
		current = current->prev;
	}
	return (NULL);
}

t_token	*search_pipe(t_token *token_list)
{
	t_token	*current;
	int		parentesis;

	current = token_lst_get_last(token_list);
	while (current)
	{
		if (current->type == PIPE)
			return (current);
		if (current->type == CLOSE_PAREN)
		{
			parentesis = 1;
			while (parentesis)
			{
				current = current->prev;
				if (current->type == CLOSE_PAREN)
					parentesis++;
				else if (current->type == OPEN_PAREN)
					parentesis--;
			}
		}
		current = current->prev;
	}
	return (NULL);
}

t_token	*search_redirect(t_token *token_list)
{
	t_token	*current;
	int		parentesis;

	current = token_list;
	while (current)
	{
		if (current->type >= REDIR_APPEND && current->type <= REDIR_OUT)
			return (current);
		if (current->type == OPEN_PAREN)
		{
			parentesis = 1;
			while (parentesis)
			{
				current = current->next;
				if (current->type == OPEN_PAREN)
					parentesis++;
				else if (current->type == CLOSE_PAREN)
					parentesis--;
			}
		}
		current = current->next;
	}
	return (NULL);
}

t_tree_node	*get_redir_filename(t_token *redir)
{
	t_tree_node	*filename;

	filename = ft_dalloc(1, sizeof(t_tree_node));
	if (!filename)
	{
		perror("failed to build execution tree");
		return (NULL);
	}
	else
	{
		filename->cmd = redir;
		filename->left = NULL;
		filename->right = NULL;
	}
	return (filename);
}
