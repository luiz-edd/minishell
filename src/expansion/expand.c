/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:25:53 by pehenri2          #+#    #+#             */
/*   Updated: 2024/04/16 17:54:46 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *start, char *dollar, char *after_var)
{
	char	*expanded_var;
	char	*before_var;
	char	*str;

	expanded_var = getenv(ft_substr(dollar, 1, after_var - dollar - 1));
	before_var = ft_substr(start, 0, dollar - start);
	str = ft_strjoin(before_var, expanded_var);
	str = ft_strjoin(str, after_var);
	return (str);
}

// Criar condição de imprimir último exit status
char	*handle_dollar(char *start, char **str)
{
	char	*dollar;
	char	*after_var;

	dollar = *str++;
	while (**str && **str != '\'' && **str != '\"' && **str != '$')
		(*str)++;
	after_var = *str;
	return (expand(start, dollar, after_var));
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
				str++;
		}
		else if (*str == '\"')
		{
			while (*(++str) && *str != '\"')
			{
				if (*str == '$')
					return (handle_dollar(start, &str));
				str++;
			}
		}
		else if (*str == '$')
			return (handle_dollar(start, &str));
		str++;
	}
	return (start);
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
