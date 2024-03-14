/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/14 18:24:24 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/src/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

enum				e_token_type
{
	OR = 100,
	APPEND = 101,
	HERE_DOC = 102,
	CLOSE_BRACKET = 103,
	OPEN_BRACKET = 104,
	AND = 105,
	PIPE = 200,
	REDIR_OUT = 201,
	WORD = 202,
	REDIR_IN = 203,
};

// automaton
void				lexer(char *str);

// token lst
t_token				*ft_lstnew_token(char *value, int type);
void				ft_lstadd_back_token(t_token **lst, t_token *new);

#endif