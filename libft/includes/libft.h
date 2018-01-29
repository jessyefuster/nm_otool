/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:55:12 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/24 15:57:00 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

int		get_next_line(int const fd, char **line);

int		ft_numlen(long value, int base);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_ltoa(long n);
char	*ft_utob(unsigned long long value, int base, char *base_str);
void	ft_memdel(void **ap);
void	ft_strdel(char **as);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char *s, char (*f)(char));
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));

/*
**      STRING MALLOC
*/

void	*ft_memalloc(size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnew(size_t size);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s);
char	**ft_strsplit(char const *s, char c);

/*
**      STRING MANIPULATION
*/

char	*ft_strcpy(char *dst, char const *src);
char	*ft_strncpy(char *dst, char const *src, size_t n);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *s1, const char *s2);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(char const *s);
int		ft_strlen_unicode(wchar_t *str);
char	*ft_strdup(char const *s1);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_strclr(char *s);
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);

/*
**      PRINTING FUNCTIONS
*/

void	ft_usage(char *str);
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar_unicode(wchar_t c);
void	ft_putstr(char const *s);
void	ft_putnstr(char const *s, int len);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putstr_unicode(wchar_t *str);
void	ft_putendl(char const *s);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_abs(int n);
void	ft_putnbr_lint_abs(long n);

/*
**      ASCII FUNCTIONS
*/

int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalpha(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_str_toupper(char *str);

#endif
