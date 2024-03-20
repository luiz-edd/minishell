/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:04:17 by leduard2          #+#    #+#             */
/*   Updated: 2024/03/20 16:21:59 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_quote_split(char *str, char delimiter)
{
	char	**arr;
	int		i;
	int		words;

	i = -1;
	words = ft_countwords_quote(str, delimiter);
	arr = (char **)ft_dalloc((words + 1), sizeof(char *));
	while (++i < words)
	{
		arr[i] = (char *)ft_dalloc(ft_get_len(str, delimiter) + 1, 1);
		ft_add_word(str, delimiter, arr[i]);
		str = ft_move_next_word(str, delimiter);
	}
	arr[i] = NULL;
	return (arr);
}
