/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:13 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/07 17:14:26 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "$", 1) == 0)
		return (DOLLAR);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	else if (ft_isspace(*str))
		return (SPACES);
	else if (ft_isalnum(*str) || *str == '-' || *str == '\'' || *str == '\"')
		return (WORD);
	else
		return (NOK);
}