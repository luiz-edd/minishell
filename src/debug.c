/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:07:08 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/21 17:08:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define COUNT 10

void	print_list(t_token *list)
{
	t_token	*current;


	current = list;
	while (current)
	{
		printf("%5s\t", current->value);
		current = current->next;
	}
}

void print2DUtil(t_tree_node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    if (root->cmd != NULL)
        printf("%d: %s\n", root->cmd->type, root->cmd->value);

    // Process left child
    print2DUtil(root->left, space);
}

void print2D(t_tree_node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}