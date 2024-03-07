# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 12:13:03 by pehenri2          #+#    #+#              #
#    Updated: 2024/03/07 15:59:07 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
CC					=	cc
CFLAGS				=	-Wextra -Wall -Werror -Wunreachable-code -g3
LIBFLAGS			=	-lreadline -lhistory
HEADERS				= 	-I ./include -I $(LIBFT_PATH)
LIBFT				= 	$(addprefix $(LIBFT_PATH), libft.a)
LIBFT_PATH			= 	./lib/libft/
SRCS_PATH			= 	./src/
FILES				= 	$(addprefix $(SRCS_PATH), main.c)
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
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file=valgrind-out.txt \
		 ./$(EXE) $(ARG)

.PHONY: all, clean, fclean, re, norm, val