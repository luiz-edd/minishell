/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:08:58 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/19 21:40:00 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	append_token(t_token *token, t_token **list)
{
	t_token	*current;

	if (*list == NULL)
		*list = token;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = token;
		token->prev = current;
	}
}

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
		return (handle_error("Invalid syntax, check input for open quotes or \
brackets."));
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
