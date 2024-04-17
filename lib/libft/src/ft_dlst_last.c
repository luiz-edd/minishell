/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:17:22 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/25 18:17:28 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlst	*ft_dlst_last(t_dlst *list)
{
	t_dlst	*current;

	if (!list)
		return (NULL);
	current = list;
	while (current->next)
		current = current->next;
	return (current);
}
