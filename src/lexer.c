/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:13 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/13 19:11:44 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(char *str, t_token **list)
{
	while (*str)
	{
		str = get_next_token(str, list);
	}
}

char *get_next_token(char *str, t_token **list)
{
	int type;
	
	type = get_token_type(str);
	if (is_two_char_token(type))
		get_two_char_token(str, type, list);
	else if (is_one_char_token(type))
		get_one_char_token(str, type, list);
	else if (type == WORD)
		get_word_token(str, list);
	else if (type == SPACES)
		str++;
	return (*str);
}

int	get_token_type(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
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
int is_two_char_token(int type)
{
	return (type == AND || type == OR || type == REDIR_APPEND || type == REDIR_HEREDOC);
}

int	is_one_char_token(int type)
{
	return (type == PIPE || type == REDIR_IN || type == REDIR_OUT);
}

void	get_two_char_token(char *str, int type, t_token **list)
{
	t_token	*new;
	char	*value;
	
	value = ft_strndup(str, 2);
	new = create_token(value, type);
	add_token(list, new);
	str += 2;
}

void	get_one_char_token(char *str, int type, t_token **list)
{
	t_token	*new;
	char	*value;
	
	value = ft_strndup(str, 1);
	new = create_token(value, type);
	add_token(list, new);
	str++;
}

void	get_word_token(char *str, t_token **list)
{
	t_token	*new;
	char	*value;
	int		len;
	int		i;
	
	len = 0;
	while (get_token_type(str) == WORD) //fazer função externa para contar com casos de quotes
		len++;
	value = malloc(len + 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			value[i] = str[i];
			i++;
			while (str[i] != '\'')
			{
				value[i] = str[i];
				i++;
			}
		}
		if (str[i] == '\"')
		{
			value[i] = str[i];
			i++;
			while (str[i] != '\"')
			{
				value[i] = str[i];
				i++;
			}
		}
		if (get_token_type(str + i) != WORD)
			break;
		value[i] = str[i];
		i++;
	}
	new = create_token(value, WORD);
	add_token(list, new);
	str += len;
}