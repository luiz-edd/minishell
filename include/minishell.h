/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/20 16:11:31 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;


typedef struct s_tree_node
{
	t_token				*cmd;
	t_token				*redir;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

enum e_token_type
{
	AND = 1,
	OR,
	PIPE,
	OPEN_PAREN,
	CLOSE_PAREN,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	SPACES,
	END,
	WORD,
};

// lexer.c
int		lexer(char *str, t_token **list);
int		get_token_length(char *str, int type);
int		get_word_length(char *str);
int		get_token_type(char *str);

//lexer_utils.c
void	append_token(t_token *token, t_token **list);
t_token	*create_token(char *value, int type);
int		check_open_syntax(char *str);
void	move_to_next_quote(char *str, int *index, int *single_quote,
			int *double_quote);
//parser.c
int		parser(t_token *list);
int		check_syntax(t_token *current);
int		check_control_operator_rule(t_token *token);
int		check_redirect_rule(t_token *token);
int		check_parenthesis_rule(t_token *token);

//error.c
int		syntax_error(char *token);
int		handle_error(char *message);

// main.c

//debug.c
void	print_list(t_token *list);

#endif