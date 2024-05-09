/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:07:08 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/09 17:46:22 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define COUNT 10

void	print_list(t_token *list)
{
	t_token	*current;
	int		i;

	i = 0;
	current = list;
	while (current)
	{
		printf("%iº:%5s\t", i, current->value);
		i++;
		current = current->next;
	}
	printf("\n");
}

void	print_tree_util(t_tree_node *root, int space)
{
	int	i;

	if (root == NULL)
		return ;
	space += COUNT;
	print_tree_util(root->right, space);
	printf("\n");
	i = COUNT;
	while (i++ < space)
		printf(" ");
	if (root->cmd != NULL)
		printf("%d: %s\n", root->cmd->type, root->cmd->value);
	print_tree_util(root->left, space);
}

void	print_tree(t_tree_node *root)
{
	print_tree_util(root, 0);
}
