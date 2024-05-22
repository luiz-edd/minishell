/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:25:05 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/22 20:29:23 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_empty_value(t_token **current, t_tree_node **cmd_node)
{
	if ((*current)->prev)
		(*current)->prev->next = (*current)->next;
	if ((*current)->next)
		(*current)->next->prev = (*current)->prev;
	if (*((*cmd_node)->cmd->value) == '\0')
	{
		(*cmd_node)->cmd = (*cmd_node)->cmd->next;
		if ((*cmd_node)->cmd)
			(*cmd_node)->cmd->prev = NULL;
	}
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	tmp = ft_dalloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == str[i])
			quote = '\0';
		else if ((str[i] == '\"' || str[i] == '\'') && quote == '\0')
			quote = str[i];
		else
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	retokenize(t_token **token)
{
	t_token	*next;
	char	**tokens;
	int		i;

	next = (*token)->next;
	tokens = ft_split((*token)->value, ' ');
	if (*tokens)
	{
		(*token)->value = *tokens;
		i = 1;
		while (tokens[i])
		{
			(*token)->next = token_lst_new(tokens[i], WORD);
			(*token) = (*token)->next;
			i++;
		}
		(*token)->next = next;
	}
	else
		(*token)->value = "\0";
}
