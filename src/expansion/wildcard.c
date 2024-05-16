/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:28:22 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/16 16:06:09 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_wildcards(t_token **token, t_token **head)
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
			token_lst_add_back(&matched, token_lst_new(ft_strdup(entry->d_name),
					WORD));
		entry = readdir(dir);
	}
	closedir(dir);
	if (!matched)
		return ;
	if ((*token)->prev == NULL)
		*head = matched;
	sort_token_lst(&matched);
	update_token_list(token, matched);
}

bool	is_match(char *text, char *pattern)
{
	int		text_length;
	int		pattern_length;
	int		row;
	int		col;
	bool	**lookup;

	lookup = init_lookup_table(text, &text_length, pattern, &pattern_length);
	row = true;
	while (row <= text_length)
	{
		col = true;
		while (col <= pattern_length)
		{
			if (pattern[col - 1] == '*')
				lookup[row][col] = lookup[row][col - 1] | lookup[row - 1][col];
			else if (text[row - 1] == pattern[col - 1])
				lookup[row][col] = lookup[row - 1][col - 1];
			col++;
		}
		row++;
	}
	return (match_result_and_free(lookup, text_length, pattern_length));
}

bool	**init_lookup_table(char *text, int *text_length, char *pattern,
		int *pattern_length)
{
	bool	**lookup;
	int		row;
	int		col;

	*text_length = ft_strlen(text);
	*pattern_length = ft_strlen(pattern);
	lookup = (bool **)ft_calloc((*text_length + 1), sizeof(bool *));
	row = false;
	while (row <= *text_length)
	{
		lookup[row] = (bool *)ft_calloc((*pattern_length + 1), sizeof(bool));
		row++;
	}
	lookup[0][0] = true;
	col = 1;
	while (col <= *pattern_length)
	{
		if (pattern[col - 1] == '*')
			lookup[0][col] = lookup[0][col - 1];
		col++;
	}
	return (lookup);
}

bool	match_result_and_free(bool **lookup, int text_length,
		int pattern_length)
{
	bool	result;
	int		row;

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
