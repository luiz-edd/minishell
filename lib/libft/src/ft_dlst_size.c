/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:17:05 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/17 16:19:00 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlst_size(t_dlst	*list)
{
	int		count;
	t_dlst	*current;

	count = 0;
	current = list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
