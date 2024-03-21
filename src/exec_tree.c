/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:38:36 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/21 16:50:40 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node *build_execution_tree(t_token *token_list)
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
	//parse_command(tree_node);
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
