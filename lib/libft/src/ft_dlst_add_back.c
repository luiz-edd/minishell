/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:15:10 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/17 17:55:00 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_add_back(t_dlst *list, t_dlst *new)
{
	t_dlst	*current;

	if (!list)
		list = new;
	else
	{
		current = list;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
}
