/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:08:58 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/24 17:08:35 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_syntax(char *str)
{
	int		index;
	int		brackets;
	int		single_quote;
	int		double_quote;

	index = 0;
	brackets = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			move_to_next_quote(str, &index, &single_quote, &double_quote);
		if (str[index] == '(')
			brackets++;
		if (str[index] == ')')
			brackets--;
		index++;
	}
	if (brackets != 0 || single_quote != 0 || double_quote != 0)
		return (write(STDERR_FILENO, "Invalid syntax, check input for open \
quotes or brackets.\n", 58));
	return (SUCCESS);
}

void	move_to_next_quote(char *str, int *index, int *single_quote,
	int *double_quote)
{
	if (str[*index] == '\'')
	{
		(*single_quote)++;
		(*index)++;
		while (str[*index] && str[*index] != '\'')
			(*index)++;
		if (str[*index] == '\'')
			(*single_quote)--;
	}
	if (str[*index] == '\"')
	{
		(*double_quote)++;
		(*index)++;
		while (str[*index] && str[*index] != '\"')
			(*index)++;
		if (str[*index] == '\"')
			(*double_quote)--;
	}
}
