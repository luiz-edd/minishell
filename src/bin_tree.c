/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:38:36 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/01 17:17:02 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*build_execution_tree(t_token *token_list)
{
	t_tree_node	*root;

	root = ft_dalloc(1, sizeof(t_tree_node));
	if (!root)
	{
		handle_error("failed to build execution tree");
		return (NULL);
	}
	split_tokens_into_tree(root, token_list);
	return (root);
}

// voltar para o modelo antigo?
void	split_tokens_into_tree(t_tree_node *tree_node, t_token *token_list)
{
	t_token	*is_and_or;
	t_token	*is_pipe;
	t_token	*is_redirect;

	is_and_or = search_and_or(token_list);
	is_pipe = search_pipe(token_list);
	is_redirect = search_redirect(token_list);
	if (is_and_or)
		split_list(tree_node, token_list, is_and_or);
	else if (is_pipe)
		split_list(tree_node, token_list, is_pipe);
	else if (is_redirect)
		split_redirect(tree_node, token_list, is_redirect);
	else
		tree_node->cmd = token_list;
}

void	split_list(t_tree_node *tree_node, t_token *token_list,
		t_token *token_to_cut)
{
	t_token	*right;

	if (!tree_node || !token_list || !token_to_cut)
		return ;
	tree_node->cmd = token_to_cut;
	right = cut_token_list(token_list, token_to_cut);
	if (!right)
	{
		handle_error("failed to build execution tree");
		return ;
	}
	tree_node->left = build_execution_tree(token_list);
	tree_node->right = build_execution_tree(right);
}

t_token	*cut_token_list(t_token *token_list, t_token *token_to_cut)
{
	t_token	*right;

	if (!token_list || !token_to_cut)
		return (NULL);
	right = token_to_cut->next;
	right->prev = NULL;
	if (token_to_cut->prev)
		token_to_cut->prev->next = NULL;
	token_to_cut->prev = NULL;
	token_to_cut->next = NULL;
	return (right);
}

void	split_redirect(t_tree_node *tree_node, t_token *token_list,
		t_token *token_to_cut)
{
	if (!tree_node || !token_list || !token_to_cut)
		return ;
	tree_node->cmd = token_to_cut;
	//segfault aqui
	tree_node->right->cmd = token_to_cut->next;
	if (token_list == token_to_cut)
	{
		token_list = token_list->next->next;
		token_list->prev = NULL;
		token_to_cut->next->next = NULL;
		token_to_cut->prev = NULL;
	}
	else
	{
		token_to_cut->prev->next = token_to_cut->next->next;
		if (token_to_cut->next->next)
			token_to_cut->next->next->prev = token_to_cut->prev;
		token_to_cut->next->next = NULL;
		token_to_cut->prev = NULL;
	}
	tree_node->left = build_execution_tree(token_list);
}
