/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:47:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/16 18:37:22 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*search_redirect(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type >= REDIR_APPEND && current->type <= REDIR_OUT)
			return (current);
		current = current->next;
	}
	return (NULL);
}

// no bash, se o filename é uma variavel que contém spaces, o bash reclama
// com o erro "ambiguous redirect"
t_tree_node	*get_redir_filename(t_token *redir)
{
	t_tree_node	*filename;

	redir->value = expand_vars(redir->value);
	redir->value = remove_quotes(redir->value);
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
