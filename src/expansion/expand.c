/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:25:53 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/24 19:54:34 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_tree_node *cmd_node)
{
	t_token	*current;

	current = cmd_node->cmd;
	while (current)
	{
		current->value = expand_vars(current->value);
		if (*(current->value) == '\0')
			handle_empty_value(&current, &cmd_node);
		if (ft_strchr_quote_aware(current->value, '*'))
			expand_wildcards(&current, &cmd_node);
		if (ft_strchr_quote_aware(current->value, ' '))
			retokenize(&current);
		current->value = remove_quotes(current->value);
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
		else if (*str == '$' && str[1] && (ft_isalnum(str[1])
				|| ft_strchr("_?\'\"", str[1])))
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
	if (!handle_special_cases(dollar, str, &after_var, &expanded_var))
	{
		while (**str && (ft_isalnum(**str) || **str == '_'))
			(*str)++;
		after_var = *str;
		expanded_var = getenv(ft_substr(dollar, 1, after_var - dollar - 1));
	}
	before_var = ft_substr(start, 0, dollar - start);
	result = ft_strjoin(before_var, expanded_var);
	result = ft_strjoin(result, after_var);
	*str = result + ft_strlen(before_var) + ft_strlen(expanded_var) - 1;
	return (result);
}

char	*handle_special_cases(char *dollar, char **str, char **after_var,
		char **expanded_var)
{
	if (*(dollar + 1) == '?')
	{
		*expanded_var = ft_itoa(*get_exit_status());
		*after_var = ++(*str);
	}
	else if (*(dollar + 1) == '\'' || *(dollar + 1) == '\"')
	{
		*after_var = *str;
		*expanded_var = ft_strdup("");
	}
	else
		return (NULL);
	return (*expanded_var);
}
