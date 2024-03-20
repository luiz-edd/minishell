/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:38:36 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/19 19:01:28 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_to_tree(t_token *list, t_tree_node **root)
{
	t_token		*current;
	t_tree_node	*node;

	current = list;
	while (current)
	{
		node = create_node(current);
		if (node == NULL)
			return (FAILURE);
		append_node(node, root);
		current = current->next;
	}
	return (SUCCESS);
}