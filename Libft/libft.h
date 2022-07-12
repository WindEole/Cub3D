/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:06:07 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/08 11:05:46 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BUFFER_SIZE 8

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *s);
int					ft_atoi_base(char *str, char *base);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_convert_base(char *nbr, char *base_from, \
		char *base_to);
void				ft_div_mod(int a, int b, int *div, int *mod);
void				ft_is_negative(int n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void*));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
		void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t n);
void				ft_print_alphabet(void);
void				ft_print_comb(void);
void				ft_print_comb2(void);
void				ft_print_numbers(void);
void				ft_print_reverse_alphabet(void);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_base(int nbr, char *base);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int nb);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr_non_printable(char *str);
void				ft_putstr(char *str);
char				**ft_split(char const *s, char c);
int					ft_str_is_alpha(char *str);
int					ft_str_is_lowercase(char *str);
int					ft_str_is_numeric(char *str);
int					ft_str_is_printable(char *str);
int					ft_str_is_uppercase(char *str);
char				*ft_strcat(char *dest, char *src);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_strlen(char *str);
char				*ft_strlowcase(char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *dest, char *src, unsigned int nb);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				ft_strncpy(char *dest, char *src, unsigned int n);
char				*ft_strnstr(const char *haystack, const char *needle, \
		size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(char *str, char *to_find);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strupcase(char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_swap(int *a, int *b);
int					ft_tolower(int c);
int					ft_toupper(int c);

// get_next_line

int					get_next_line(int fd, char **line);
char				*ft_strjoin_gnl(char *s1, char *s2);
int					ft_strn(char *s);

#endif
