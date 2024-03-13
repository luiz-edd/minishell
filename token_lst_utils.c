/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:23:07 by leduard2          #+#    #+#             */
/*   Updated: 2024/03/13 15:26:14 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_token(char *value, int type)
{
	t_token	*node;

	node = (t_token *)ft_dalloc(sizeof(t_token), 1);
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*p;

	p = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (p)
	{
		if (p->next == NULL)
		{
			p->next = new;
			return ;
		}
		p = p->next;
	}
}