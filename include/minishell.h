/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/03/25 18:54:37 by pehenri2         ###   ########.fr       */
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
# include <wait.h>

# define SUCCESS 0
# define FAILURE 1
# define WRITE 1
# define READ 0

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_tree_node
{
	int					type;
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
int			lexer(char *str, t_token **list);
int			get_token_length(char *str, int type);
int			get_word_length(char *str);
int			get_token_type(char *str);

//lexer_utils.c
int			check_open_syntax(char *str);
void		move_to_next_quote(char *str, int *index, int *single_quote,
				int *double_quote);
//parser.c
int			parser(t_token *list, t_tree_node **root);
int			check_syntax(t_token *current);
int			check_control_operator_rule(t_token *token);
int			check_redirect_rule(t_token *token);
int			check_parenthesis_rule(t_token *token);

//exec_tree.c
t_tree_node	*build_execution_tree(t_token *token_list);
void		split_tokens_into_tree(t_tree_node *tree_node, t_token *token_list);
int			split_list(t_tree_node *tree_node, t_token *token_list,
				t_token *token_to_cut);
t_token		*cut_token_list(t_token *token_list, t_token *token_to_cut);
void		parse_command(t_tree_node *tree_node);

//exec_tree_utils.c
t_token		*search_and_or(t_token *token_list);
t_token		*search_pipe(t_token *token_list);
t_token		*get_cmd_path(t_token *cmd);
t_token		*search_in_cur_dir(t_token *cmd);
t_token		*search_in_path(t_token *cmd);
int			is_builtin(t_token *cmd);

//executor.c
int			executor(t_tree_node *root);
int			execute_and(t_tree_node *left, t_tree_node *right);
int			execute_or(t_tree_node *left, t_tree_node *right);
int			execute_pipe(t_tree_node *left, t_tree_node *right);
int			execute_command(t_tree_node *cmd_node);

//executor_utils.c
char		**get_cmd_and_args(t_tree_node *cmd_node);
void		solve_redirections(t_tree_node *cmd_node);

//token_list.c
t_token		*token_lst_new(char *value, int type);
void		token_lst_add_back(t_token *token_list, t_token *new);
void		token_lst_add_front(t_token *token_list, t_token *new);
int			token_lst_size(t_token *token_list);
t_token		*token_lst_last(t_token *token_list);

//error.c
int			syntax_error(char *token);
int			handle_error(char *message);

//debug.c
void		print_list(t_token *list);
void		print_tree(t_tree_node *root);
void		print_tree_util(t_tree_node *root, int space);

#endif