/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/13 15:53:31 by leduard2         ###   ########.fr       */
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
	REDIR_OUT = 101,
	REDIR_IN = 102,
	CLOSE_BRACKET = 103,
	OPEN_BRACKET = 104,
	AND = 105,
	PIPE = 200,
	APPEND = 201,
	WORD = 202,
	HERE_DOC = 203,
	
	
	
	
	


	// AND = 100,
	// OR,
	// PIPE,
	// DOLLAR,
	// REDIR_IN,
	// REDIR_OUT = 200,
	// REDIR_APPEND,
	// REDIR_HEREDOC,
	// SPACES, //" ", \t, \n, \v, \f, \r
	// WORD,   // alphanum, minus, quotes
	// NOK,
};

//automaton
void				lexer(char *str);

//token lst
t_token				*ft_lstnew_token(char *value, int type);
void				ft_lstadd_back_token(t_token **lst, t_token *new);

#endif