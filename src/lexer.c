/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:13 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/20 15:16:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *str, t_token **list)
{
	int		type;
	int		length;
	t_token	*token;

	if (!str || check_open_syntax(str))
		return (FAILURE);
	while (*str)
	{
		length = 0;
		type = get_token_type(str);
		if (type == SPACES)
			length = 1;
		else
		{
			length = get_token_length(str, type);
			token = create_token(ft_substr(str, 0, length), type);
			append_token(token, list);
		}
		str = str + length;
	}
	return (SUCCESS);
}

int	get_token_type(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "(", 1) == 0)
		return (OPEN_PAREN);
	else if (ft_strncmp(str, ")", 1) == 0)
		return (CLOSE_PAREN);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR_OUT);
	else if (ft_isspace(*str))
		return (SPACES);
	else if (ft_strncmp(str, "\0", 1) == 0)
		return (END);
	else
		return (WORD);
}

int	get_token_length(char *str, int type)
{
	if (type == OPEN_PAREN || type == CLOSE_PAREN || type == PIPE
		|| type == REDIR_IN || type == REDIR_OUT)
		return (1);
	else if (type == AND || type == OR || type == REDIR_APPEND
		|| type == REDIR_HEREDOC)
		return (2);
	else if (type == WORD)
		return (get_word_length(str));
	return (0);
}

int	get_word_length(char *str)
{
	int		len;

	len = 0;
	while (get_token_type(str + len) == WORD)
	{
		if (str[len] == '\'')
		{
			len++;
			while (str[len] != '\'')
				len++;
		}
		if (str[len] == '\"')
		{
			len++;
			while (str[len] != '\"')
				len++;
		}
		len++;
	}
	return (len);
}
