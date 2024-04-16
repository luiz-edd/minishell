/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:30:49 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/26 17:59:40 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_lst_new(char *value, int type)
{
	t_token	*new;

	new = ft_dalloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	token_lst_add_back(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (!(*token_list))
		*token_list = new;
	else
	{
		last = token_lst_get_last(*token_list);
		last->next = new;
		new->prev = last;
	}
}

void	token_lst_add_front(t_token **token_list, t_token *new)
{
	if (!(*token_list))
		*token_list = new;
	else
	{
		(*token_list)->prev = new;
		new->next = *token_list;
		*token_list = new;
	}
}

int	token_lst_get_size(t_token *token_list)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_token	*token_lst_get_last(t_token *token_list)
{
	t_token	*current;

	if (!token_list)
		return (NULL);
	current = token_list;
	while (current->next)
		current = current->next;
	return (current);
}
