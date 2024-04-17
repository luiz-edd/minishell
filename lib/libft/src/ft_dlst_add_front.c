/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:16:29 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/25 18:16:35 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_add_front(t_dlst *list, t_dlst *new)
{
	if (!list)
		list = new;
	else
	{
		list->prev = new;
		new->next = list;
		list = new;
	}
}
