/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:56:31 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/24 17:52:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_get_memory_lst(void)
{
	static t_list	*lst;

	return (&lst);
}

void	ft_collect_mem(void *content)
{
	ft_lstadd_back(ft_get_memory_lst(), ft_lstnew(content));
}

void	ft_collect_mem_arr(void **content)
{
	ft_lstadd_back_arr(ft_get_memory_lst(), content);
}

void	ft_free_memory(void)
{
	//get_next_line(-1);
	//ft_lstclear(ft_get_memory_lst(), &free);
}

void	*ft_dalloc(size_t nmemb, size_t size)
{
	void	*p;

	p = ft_calloc(nmemb, size);
	ft_collect_mem(p);
	return (p);
}
