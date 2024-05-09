/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/09 17:18:33 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERROR 2
# define DELETE 0
# define WRITE 1
# define READ 0

typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_tree_node
{
	t_token				*cmd;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

enum					e_token_type
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

/*******************************************
############## BUILTIN FOLDER ##############
*******************************************/

/*************** builtins.c ***************/

int			is_builtin(t_token *cmd);
int			execute_builtin(t_token *cmd);

/****************** cd.c ******************/

int			execute_cd(t_token *cmd);
int			change_to_home(void);
int			change_dir(char *path);
int			check_access(char *path);

/***************** env.c ******************/

int			execute_env(t_token *cmd);

/***************** exit.c *****************/

int			execute_exit(t_token *cmd);
int			validate_argument(char *arg);
int			check_limits(long number);

/***************** echo.c *****************/

int			execute_echo(t_token *cmd);
int			check_n_flag(char *str);
void		print_args(char **args, int has_n_flag);

/***************** pwd.c ******************/

int			execute_pwd(void);

/*******************************************
############# EXECUTOR FOLDER ##############
*******************************************/

/************ execute_command.c ***********/

int			execute_command(t_tree_node *cmd_node);
void		run_command_in_child_process(t_tree_node *cmd_node);
char		*get_cmd_path(t_token *cmd);
char		*search_in_path(t_token *cmd);
char		**get_cmd_and_args(t_token *cmd);

/************* execute_pipe.c *************/

int			execute_pipe(t_tree_node *left, t_tree_node *right);
int			execute_child(int fd, int *pipe, t_tree_node *node);

/*********** execute_redirect.c ***********/

int			execute_redirect(t_tree_node *left, t_tree_node *right,
				int redir_type);
int			open_redir_file(t_tree_node *right, int redir_type, int *fd);
int			dup2_redir_file(int redir_type, int *fd);

/*************** executor.c ***************/

int			executor(t_tree_node *root);
int			execute_and(t_tree_node *left, t_tree_node *right);
int			execute_or(t_tree_node *left, t_tree_node *right);
int			execute_block(t_tree_node *root);

/*******************************************
############# EXPANSION FOLDER #############
*******************************************/

/**************** expand.c ****************/

void		expand_command(t_tree_node *cmd_node);
char		*expand_vars(char *str);
char		*handle_dollar(char *start, char **str);
char		*remove_quotes(char *str);
void		retokenize(t_token **token);

/************* wildcard.c ****************/
void		expand_wildcards(t_token **token);
int			is_match(char *text, char *pattern);
int			**init_lookup_table(char *text, int *text_length, char *pattern,
				int *pattern_length);
int			match_result_and_free(int **lookup, int text_length,
				int pattern_length);

/*******************************************
############### LEXER FOLDER ###############
*******************************************/

/**************** lexer.c *****************/

int			lexer(char *str, t_token **list);
int			get_token_type(char *str);
int			get_token_length(char *str, int type);
int			get_word_length(char *str);

/************* open_syntax.c **************/

int			check_open_syntax(char *str);
void		move_to_next_quote(char *str, int *index, int *single_quote,
				int *double_quote);

/*******************************************
############## PARSER FOLDER ###############
*******************************************/

/*************** bin_tree.c ***************/

t_tree_node	*build_execution_tree(t_token *token_list);
void		split_tokens_into_tree(t_tree_node *tree_node, t_token *token_list);
void		split_list(t_tree_node *tree_node, t_token *token_list,
				t_token *token_to_cut);
t_token		*cut_token_list(t_token *token_list, t_token *token_to_cut);
void		split_redirect(t_tree_node *tree_node, t_token *token_list,
				t_token *token_to_cut);

/*********** bin_tree_helper.c ************/

t_token		*search_and_or(t_token *token_list);
t_token		*search_pipe(t_token *token_list);
t_token		*search_redirect(t_token *token_list);
t_tree_node	*get_redir_filename(t_token *redir);

/**************** parser.c ****************/

int			parser(t_token *list, t_tree_node **root);
int			check_syntax(t_token *current);
int			check_control_operator_rule(t_token *token);
int			check_redirect_rule(t_token *token);
int			check_parenthesis_rule(t_token *token);

/*******************************************
############# REDIRECT FOLDER ##############
*******************************************/

/*************** heredoc.c ****************/

int			create_heredoc_file(t_token *token);
int			write_input_to_heredoc(int fd, char *end_condition,
				int is_expandable);
int			delete_heredoc_files(void);
int			*get_heredoc_counter(void);

/*******************************************
############## SIGNALS FOLDER ##############
*******************************************/

/*************** signals.c ****************/
int			setup_signal_handler(void (*func)(int signum));
int			setup_fork_signal_handlers(int pid);
void		main_signal_handler(int signum);
void		heredoc_signal_handler(int signum);

/*******************************************
############### UTILS FOLDER ###############
*******************************************/

/**************** error.c *****************/

int			syntax_error(char *token);
int			handle_error(char *message);
int			throw_error(char *cmd_path);
void		close_pipe(int *pipe_fd);

/**************** helper.c ****************/

int			*get_exit_status(void);
int			set_exit_status(int status);
void		wait_child_status(pid_t pid, int *status);
void		reset_for_next_iteration(char *line);

/************** token_list.c **************/

t_token		*token_lst_new(char *value, int type);
void		token_lst_add_back(t_token **token_list, t_token *new);
void		token_lst_add_front(t_token **token_list, t_token *new);
int			token_lst_get_size(t_token *token_list);
t_token		*token_lst_get_last(t_token *token_list);

/*******************************************
!!!!!!!!!!!!!!! DELETE THIS !!!!!!!!!!!!!!!!
*******************************************/
void		print_list(t_token *list);
void		print_tree(t_tree_node *root);
void		print_tree_util(t_tree_node *root, int space);

#endif
