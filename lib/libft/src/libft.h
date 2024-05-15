/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:32:55 by leduard2          #+#    #+#             */
/*   Updated: 2024/05/15 16:42:54 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define NULL_BYTE 1
# define ERROR_CODE -1
# define FD_LIMIT 1024
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define MAX_INT 2147483647
# define MIN_INT -2147483648

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_dlst
{
	void			*content;
	struct s_dlst	*prev;
	struct s_dlst	*next;
}					t_dlst;

int					ft_isalpha(int point);
int					ft_isdigit(int point);
int					ft_isalnum(int point);
int					ft_isascii(int point);
int					ft_isprint(int point);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int point, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int point);
int					ft_tolower(int point);
char				*ft_strchr(const char *s, int point);
char				*ft_strrchr(const char *s, int point);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int point, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char point);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
int					ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(long n, int fd);
int					ft_putptr_fd(unsigned long nbr, int fd);
int					ft_putnbr_base_fd(long nbr, char *base, int fd);

char				*get_next_line(int fd);
int					ft_wordcount(char *str, char delimiter);
void				ft_freepp(char **arr);
unsigned int		ft_atoi_base(char *str, int str_base);
float				ft_absolute(float a);
float				ft_maxval(float a, float b);
void				ft_print_words(char **str);
long				ft_atol(char *str);
int					ft_isspace(char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_arrstr_len(char **str);
int					ft_fprintf(int fd, const char *format, ...);

// SPLIT_QUOTE
void				ft_add_word(char *str, char delimiter, char *dst);
int					ft_countwords_quote(char *str, char delimiter);
int					ft_get_len(char *str, char delimiter);
char				*ft_move_next_word(char *str, char delimiter);
char				**ft_quote_split(char *str, char delimiter);

// list utils
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstadd_back_arr(t_list **lst, void **content);

//double linked list utils
void				ft_dlst_add_back(t_dlst *list, t_dlst *new);
void				ft_dlst_add_front(t_dlst *list, t_dlst *new);
t_dlst				*ft_dlst_last(t_dlst *list);
t_dlst				*ft_dlst_new(void *content);
int					ft_dlst_size(t_dlst *list);

// memory collector
t_list				**ft_get_memory_lst(void);
void				ft_collect_mem(void *content);
void				ft_collect_mem_arr(void **content);
void				ft_free_memory(void);
void				*ft_dalloc(size_t nmemb, size_t size);

# ifndef FT_PRINTF_H
#  define FT_PRINTF_H

typedef struct s_format
{
	va_list			ap;
	int				wdt;
	int				prc;
	int				zero;
	int				pnt;
	int				dash;
	int				tl;
	int				sign;
	int				is_zero;
	int				perc;
	int				sp;
	int				hash;
	int				lowc;
	int				upc;
}					t_format;

// utils
t_format			*inicialize_flags(t_format *flags);
int					ft_printf(const char *format, ...);

// ft_eval_format
int					is_normal_flag(char c);
int					ft_eval_format(t_format *flags, const char *format, int i);
int					ft_print_format(char c, t_format *flags);

// normal flags
int					ft_print_char(t_format *flag);
int					ft_print_str(t_format *flags);
int					ft_print_digit(t_format *flags);
int					ft_print_ex(t_format *flags);
int					ft_print_ex_up(t_format *flags);
int					ft_print_pointer(t_format *flags);
int					ft_print_unsigned(t_format *flags);
# endif

#endif