# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 12:13:03 by pehenri2          #+#    #+#              #
#    Updated: 2024/04/12 11:58:25 by leduard2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
CC					=	cc
CFLAGS				=	-Wextra -Wall -Werror -Wunreachable-code -g3 
LIBFLAGS			=	-lreadline -lhistory 
HEADERS				= 	-I ./include -I $(LIBFT_PATH)/src
LIBFT				= 	$(addprefix $(LIBFT_PATH), libft.a)
LIBFT_PATH			= 	./lib/libft/
SRCS_PATH			= 	./src/
FILES				= 	$(addprefix $(SRCS_PATH), main.c lexer.c lexer_utils.c parser.c parser_utils.c bin_tree.c bin_tree_utils.c executor.c executor_utils.c builtins.c token_list.c error.c debug.c builtin/echo.c builtin/execute_builtin.c builtin/pwd.c builtin/cd.c)
OBJS				= 	$(FILES:%.c=%.o)

.DEFAULT_GOAL = $(NAME)

all: $(NAME) 

$(NAME): $(OBJS) libft
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME)

libft:
	@make -C $(LIBFT_PATH) --silent

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"

clean:
	@rm -rf $(OBJS)
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
		 --track-fds=yes \
		 ./$(NAME)
		#  --show-leak-kinds=all \
        #  --track-origins=yes \
        #  --log-file=valgrind-out.txt \

.PHONY: all, clean, fclean, re, norm, val

