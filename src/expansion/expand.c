/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:25:53 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/13 17:54:54 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_command(t_tree_node *cmd_node)
{
	t_token	*current;

	current = cmd_node->cmd;
	while (current)
	{
		current->value = expand_vars(current->value);
		if (ft_strchr_quote_aware(current->value, '*'))
			expand_wildcards(&current, &cmd_node->cmd);
		current->value = remove_quotes(current->value);
		if (ft_strchr(current->value, ' '))
			retokenize(&current);
		if (*(current->value) == '\0')
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
		}
		current = current->next;
	}
}

char	*expand_vars(char *str)
{
	char	*start;

	start = str;
	while (*str)
	{
		if (*str == '\'')
		{
			while (*(++str) && *str != '\'')
				;
		}
		else if (*str == '\"')
		{
			while (*(++str) && *str != '\"')
			{
				if (*str == '$' && str[1] && (ft_isalnum(str[1])
						|| ft_strchr("_?", str[1])))
					start = handle_dollar(start, &str);
			}
		}
		else if (*str == '$' && str[1] && (ft_isalnum(str[1]) || ft_strchr("_?",
					str[1])))
			start = handle_dollar(start, &str);
		str++;
	}
	return (start);
}

char	*handle_dollar(char *start, char **str)
{
	char	*dollar;
	char	*before_var;
	char	*after_var;
	char	*expanded_var;
	char	*result;

	dollar = (*str)++;
	if (*(dollar + 1) == '?')
		return (ft_itoa(*get_exit_status()));
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	after_var = *str;
	expanded_var = getenv(ft_substr(dollar, 1, after_var - dollar - 1));
	before_var = ft_substr(start, 0, dollar - start);
	result = ft_strjoin(before_var, expanded_var);
	result = ft_strjoin(result, after_var);
	*str = result + ft_strlen(before_var) + ft_strlen(after_var) - 1;
	return (result);
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
