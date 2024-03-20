/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:57:01 by leduard2          #+#    #+#             */
/*   Updated: 2024/02/19 11:20:29 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_arr(t_list **lst, void **cont)
{
	int	i;

	i = 0;
	ft_lstadd_back(lst, ft_lstnew((void *)(cont)));
	while (cont[i] != NULL)
		ft_lstadd_back(lst, ft_lstnew(cont[i++]));
}
