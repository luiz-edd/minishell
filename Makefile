# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 12:13:03 by pehenri2          #+#    #+#              #
#    Updated: 2024/05/15 20:05:40 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
CC					=	cc
CFLAGS				=	-Wextra -Wall -Werror -Wunreachable-code -g3
LIBFLAGS			=	-lreadline -lhistory 
HEADERS				= 	-I ./include -I $(LIBFT_PATH)/src
LIBFT				= 	$(addprefix $(LIBFT_PATH), libft.a)
LIBFT_PATH			= 	./lib/libft/
VPATH 				= 	./src:./src/builtin:./src/executor:./src/expansion:./src/lexer:./src/parser:./src/redirect:./src/signals:./src/utils
FILES				= 	main.c \
						builtins.c \
						cd.c \
						echo.c \
						env.c \
						exit.c \
						pwd.c \
						execute_command.c \
						execute_pipe.c \
						execute_redirect.c \
						executor.c \
						expand.c \
						wildcard.c \
						lexer.c \
						open_syntax.c \
						bin_tree.c \
						bin_tree_helper.c \
						parser.c \
						heredoc.c \
						signals.c \
						debug.c \
						error.c \
						helper.c \
						token_list.c \
						environ.c \
						export.c \
						export_print.c \
						export_utils.c \
						unset.c
OBJS				= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR				= 	obj

.DEFAULT_GOAL = $(NAME)

all: $(NAME) 

$(NAME): $(OBJS) libft
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME) $(LIBFLAGS)

libft:
	@make -C $(LIBFT_PATH) --silent

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_PATH) clean --silent
	@echo "Deleted object files"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean --silent
	@echo "Deleted executable files and static libraries"

re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader

val: all
	valgrind --leak-check=full \
		--trace-children=yes \
		--show-leak-kinds=all \
		--suppressions=readline.supp \
		./$(NAME)
#		--track-fds=yes \
#       --track-origins=yes \
#       --log-file=valgrind-out.txt \

.PHONY: all, clean, fclean, re, norm, val
