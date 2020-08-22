/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:33:19 by pdemocri          #+#    #+#             */
/*   Updated: 2020/08/15 21:18:33 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define FT_SIZE_MAX (size_t)~0
# include <string.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
*********************** PART 1 ***********************
*/
void				*ft_memset(void *destination, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *arr, int c, size_t n);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t n);
char				*ft_strchr(const char *str, int ch);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strnstr(const char *str1, const char *str2, size_t n);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int ch);
int					ft_isdigit(int ch);
int					ft_isalnum(int ch);
int					ft_isascii(int ch);
int					ft_isprint(int ch);
int					ft_toupper(int ch);
int					ft_tolower(int ch);
void				*ft_calloc(size_t n, size_t size);
char				*ft_strdup(const char *str);
/*
*********************** PART 2 ***********************
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char const *s, int fd);
int					ft_putendl_fd(char const *s, int fd);
int					ft_putnbr_fd(int n, int fd);

/*
********************* BONUS PART *********************
*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),\
					void (*del)(void *));
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strncat(char *dst, const char *src, size_t n);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcpy(char *dst, const char *src);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_putchar(char c);
int					ft_putstr(char const *s);
void				ft_putendl(char const *s);
int					ft_putnbr(long long n);
int					ft_putunbr(unsigned long long n);
int					ft_islower(int ch);
int					ft_isupper(int ch);
int					ft_isblank(int ch);
int					ft_iscntrl(int ch);
int					ft_isgraph(int ch);
int					ft_isspace(int ch);
int					ft_isxdigit(int ch);
int					ft_strcasecmp(const char *str1, const char *str2);
int					ft_strncasecmp(const char *str1, const char *str2,\
					size_t n);
char				*ft_strcasestr(const char *str1, const char *str2);
char				*ft_strupcase(char *str);
char				*ft_strlowcase(char *str);
double				ft_pow(double basis, double exponent);
char				*ft_lltoa(long long n);
int					ft_abs(int i);
long long			ft_llabs(long long ll);
double				ft_fabs(double d);
double				ft_atof(char *str);

#endif
