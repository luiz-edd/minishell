/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:28:22 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/08 20:58:43 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int	**init_lookup_table(char *text, int *text_length, char *pattern,
		int *pattern_length)
{
	int	**lookup;
	int	row;
	int	col;

	*text_length = strlen(text);
	*pattern_length = strlen(pattern);
	lookup = (int **)calloc((*text_length + 1), sizeof(int *));
	row = 0;
	while (row <= *text_length)
	{
		lookup[row] = (int *)calloc((*pattern_length + 1), sizeof(int));
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

int	main(void)
{
	char	*text;
	char	*pattern;

	text = "123baaabab";
	pattern = "*****ba*****ab";
	if (is_match(text, pattern))
		printf("Encontrou\n");
	else
		printf("Não encontrou\n");
	return (0);
}
