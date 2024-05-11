/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:28:22 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/11 16:13:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// readdir não devolve em ordem alfabetica, seria bom criar uma função de
// ordenação para ficar igual ao bash
void	expand_wildcards(t_token **token, t_token **cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*matched;

	dir = opendir(".");
	if (!dir)
		return ;
	matched = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (*(entry->d_name) != '.' && is_match(entry->d_name, (*token)->value))
			token_lst_add_back(&matched, token_lst_new(entry->d_name, WORD));
		entry = readdir(dir);
	}
	closedir(dir);
	if (!matched)
		return ;
	if ((*token)->prev == NULL)
		*cmd = matched;
	update_token_list(token, matched);
}

int	is_match(char *text, char *pattern)
{
	int	text_length;
	int	pattern_length;
	int	row;
	int	col;
	int	**lookup;

	lookup = init_lookup_table(text, &text_length, pattern, &pattern_length);
	row = 1;
	while (row <= text_length)
	{
		col = 1;
		while (col <= pattern_length)
		{
			if (pattern[col - 1] == '*')
				lookup[row][col] = lookup[row][col - 1] || lookup[row - 1][col];
			else if (text[row - 1] == pattern[col - 1])
				lookup[row][col] = lookup[row - 1][col - 1];
			col++;
		}
		row++;
	}
	return (match_result_and_free(lookup, text_length, pattern_length));
}

int	**init_lookup_table(char *text, int *text_length, char *pattern,
		int *pattern_length)
{
	int	**lookup;
	int	row;
	int	col;

	*text_length = ft_strlen(text);
	*pattern_length = ft_strlen(pattern);
	lookup = (int **)ft_calloc((*text_length + 1), sizeof(int *));
	row = 0;
	while (row <= *text_length)
	{
		lookup[row] = (int *)ft_calloc((*pattern_length + 1), sizeof(int));
		row++;
	}
	lookup[0][0] = 1;
	col = 1;
	while (col <= *pattern_length)
	{
		if (pattern[col - 1] == '*')
			lookup[0][col] = lookup[0][col - 1];
		col++;
	}
	return (lookup);
}

int	match_result_and_free(int **lookup, int text_length, int pattern_length)
{
	int	result;
	int	row;

	result = lookup[text_length][pattern_length];
	row = 0;
	while (row <= text_length)
	{
		free(lookup[row]);
		row++;
	}
	free(lookup);
	return (result);
}

void	update_token_list(t_token **token, t_token *matched)
{
	t_token	*last;

	last = token_lst_get_last(matched);
	last->next = (*token)->next;
	if ((*token)->next)
		(*token)->next->prev = last;
	matched->prev = (*token)->prev;
	if ((*token)->prev)
		(*token)->prev->next = matched;
	*token = last;
}
