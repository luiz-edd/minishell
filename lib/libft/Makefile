NAME = libft.a
HEADERS = src/
CC = cc -Wall -Wextra -Werror -g3

PATH_TO_SRC = src/
PATH_TO_OBJ = obj/

PRINTF = ft_eval_format.c \
	ft_print_char.c \
	ft_print_digit.c \
	ft_print_ex_up.c \
	ft_print_ex.c \
	ft_print_pointer.c \
	ft_print_str.c \
	ft_print_unsigned.c \
	ft_printf.c \
	ft_print_utils.c \

GNL = get_next_line.c

SPLIT_QUOTE = ft_quote_add_word.c \
	ft_quote_count_words.c \
	ft_quote_get_len.c \
	ft_quote_move_next_word.c \
	ft_quote_split.c \


SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_atoi.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_wordcount.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_atoi_base.c \
	ft_maxval.c \
	ft_lstsize.c \
	ft_freepp.c \
	ft_absolute.c \
	ft_print_words.c \
	ft_atol.c \
	ft_lstadd_back_arr.c \
	ft_collect_mem.c \
	ft_isspace.c	\
	ft_strcmp.c	\
	ft_arrstr_len.c \
	ft_strndup.c \
	ft_strdup_calloc.c \
	ft_strchr_quote_aware.c \
	$(PRINTF) \
	$(GNL) \
	$(SPLIT_QUOTE) \
	ft_putptr_fd.c \
	ft_putnbr_base_fd.c \
	ft_fprintf.c

	# ft_dlstadd_back.c \
	# ft_dlstadd_front.c \
	# ft_dlst_last.c \
	# ft_dlst_new.c \
	# ft_dlst_size.c \

OBJ = $(SRC:.c=.o)

SRC_PATH = $(addprefix $(PATH_TO_SRC), $(SRC))
OBJ_PATH = $(addprefix $(PATH_TO_OBJ), $(OBJ))

all: $(NAME)

$(NAME): $(OBJ_PATH)

$(PATH_TO_OBJ)%.o: $(PATH_TO_SRC)%.c $(HEADERS)
	@mkdir -p obj 
	$(CC) $< -o $@ -c && printf "Compiling: $(notdir $<\n)"
	@ar rcs $(NAME) $@ 
	
clean: 
	@rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

val: 
	make && $(CC) main.c libft.a && valgrind --leak-check=full --track-origins=yes ./a.out

.PHONY: all re clean fclean
