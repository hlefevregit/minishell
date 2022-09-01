/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:21:25 by hlefevre          #+#    #+#             */
/*   Updated: 2022/09/01 15:37:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(char const *haystack, char const *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_realloc(char *s, int size);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);

/* Bonus part */

typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstlast(t_list *var);
t_list	**ft_lstreplace(t_list **v, char *name, char *val);
t_list	*ft_lstnew(char *name, char *value);

void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **v);
void	ft_lstdel(t_list **var, char *name);

char	*ft_lstexist(t_list *v, char *n)

int		ft_lstsize(t_list *lst);

#endif