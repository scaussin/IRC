/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 16:42:08 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/02 18:48:44 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 4096
# define SIZE_TAB_FNCT 10
# define FD_MAX 64

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include "struct.h"

/*
** libft
*/
void	*ft_memset(void *str, int value, size_t len);
void	ft_bzero(void *str, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *src, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *src, int c);
char	*ft_strrchr(const char *src, int c);
char	*ft_strstr(const char *src, const char *test);
char	*ft_strnstr(const char *src, const char *test, size_t n);
int		ft_strcmp(const char *src, const char *test);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s);
char	**ft_strsplit(char const *s, char c);
char	*ft_itoa(int n);
void	ft_putchar(char c);
int		ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*
** libft bonus
*/
t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** get_next_line
*/
int		get_next_line(int const fd, char **line);

/*
** ft_printf
*/
int		ft_printf(const char *str, ...);
void	ft_init_fun_tab(t_fct tab[SIZE_TAB_FNCT]);
void	ft_putnbr_x(unsigned int n);
void	ft_putnbr_xx(unsigned int n);
void	ft_putnbr_p(unsigned long n);
void	ft_putnbr_unsigned(unsigned int n);
void	ft_putnbr_o(unsigned int n);
int		ft_printf_d(int nbr);
int		ft_printf_s(char *str);
int		ft_printf_c(char c);
int		ft_printf_u(unsigned int nbr);
int		ft_printf_o(unsigned int nbr);
int		ft_printf_x(unsigned int nbr);
int		ft_printf_xx(unsigned int nbr);
int		ft_printf_p(unsigned long nbr);
int		ft_printf_u_va(va_list ap);
int		ft_printf_o_va(va_list ap);
int		ft_printf_s_va(va_list ap);
int		ft_printf_c_va(va_list ap);
int		ft_printf_p_va(va_list ap);

/*
** Bonus libre
*/
char	**ft_strdup2d(char **dest, char **src);
char	**ft_strsplit_nbr(char const *s);
void	ft_swap_int(int *elem1, int *elem2);
int		ft_getnbr(const char *str);
int		ft_strlen_2d(char **tab);

#endif
