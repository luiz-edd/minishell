/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:38:36 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/25 18:30:19 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*build_execution_tree(t_token *token_list)
{
	t_tree_node		*root;

	root = ft_dalloc(1, sizeof(t_tree_node));
	if (!root)
	{
		handle_error("failed to build execution tree");
		return (NULL);
	}
	split_tokens_into_tree(root, token_list);
	return (root);
}

void	split_tokens_into_tree(t_tree_node *tree_node, t_token *token_list)
{
	if (split_list(tree_node, token_list, search_and_or(token_list)))
		return ;
	if (split_list(tree_node, token_list, search_pipe(token_list)))
		return ;
	tree_node->cmd = token_list;
	parse_command(tree_node);
}

int	split_list(t_tree_node *tree_node, t_token *token_list,
	t_token *token_to_cut)
{
	t_token	*right;

	if (!tree_node || !token_list || !token_to_cut)
		return (0);
	tree_node->cmd = token_to_cut;
	right = cut_token_list(token_list, token_to_cut);
	if (!right)
	{
		handle_error("failed to build execution tree");
		return (-1);
	}
	tree_node->left = build_execution_tree(token_list);
	tree_node->right = build_execution_tree(right);
	return (1);
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

void	parse_command(t_tree_node *tree_node)
{
	t_token	*current;
	t_token	*cmd_path;

	cmd_path = get_cmd_path(tree_node->cmd);
	if (!cmd_path)
	{
		handle_error("command not found");
		return ;
	}
	token_lst_add_front(tree_node->cmd, cmd_path);
	current = tree_node->cmd;
	while (current)
	{
		// solve_expansions(current);
		if (current->type >= REDIR_APPEND && current->type <= REDIR_OUT)
		{
			current->prev->next = current->next->next;
			current->next->next->prev = current->prev;
			current->next->next = NULL;
			current->prev = NULL;
			token_lst_add_back(tree_node->redir, current);
		}
		current = current->next;
	}
}
