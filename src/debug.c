/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:07:08 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/17 18:28:32 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token *list)
{
	t_token	*current;
	int		i;

	current = list;
	i = 0;
	while (current)
	{
		printf("NODE %02i\t--->\tType: %02i\tValue: %s\t\tPrev: %p\tNext: \
		%p\n", i, current->type, current->value, current->prev, current->next);
		i++;
		current = current->next;
	}
}
