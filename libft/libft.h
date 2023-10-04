/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:08:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/04 22:38:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

//generic list node
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

typedef struct s_array
{
	void	*arr;
	size_t	member_size;
	size_t	n_members;
}	t_array;

void	ft_swap_i(int *a, int *b);
void	ft_swap_d(double *a, double *b);
int		ft_sign(int n);
double	ft_sign_d(double n);
int		ft_max(int a, int b);
double	ft_max_d(double a, double b);
int		ft_min(int a, int b);
double	ft_min_d(double a, double b);
int		ft_clamp(int num, int min, int max);
double	ft_clamp_d(double num, double min, double max);
int		ft_abs(int a);
int		abs_max(int a, int b);
int		abs_min(int a, int b);
double	ft_abs_d(double a);
double	abs_max_d(double a, double b);
double	abs_min_d(double a, double b);
double	abs_max_signed_d(double a, double b);
double	abs_min_signed_d(double a, double b);
int		abs_max_signed(int a, int b);
int		abs_min_signed(int a, int b);
int		ft_abs_clamp(int num, int min, int max);
double	ft_abs_clamp_d(double num, double min, double max);
void	ft_do_nothing(void *p);
void	ft_do_nothing_2(void *p, void *p2);
void	*ft_free_matrix(void ***pointer, size_t n_members);
// allocates using ft_calloc a pointer array of size (y + 1* sizeof(void *))
// and then allocates (x * member_size) y times
// returns the null terminated matrix
void	**ft_matrix_init(size_t x_size, size_t y_size, size_t member_size);
t_list	*ft_lst_swap_next(t_list *node);
bool	ft_is_in_list(t_list *list, void *content, size_t content_size);
t_list	*ft_lstpop_one(void *content, t_list **list);
void	ft_lst_iteri_2(t_list *list, void (*foo)(void *, void *), void *arg);
void	ft_lstclear_2(t_list **lst, void (*del)(void *, void *), void *arg);
void	**ft_lst_to_matrix(t_list *lst);
char	**ft_read_file(char *path);
size_t	ft_matrix_size(void **mat);
void	ft_array_free(t_array *arr, void (*del)(void *));
void	ft_lst_insert_n(t_list **list, t_list *new, unsigned short n);
void	ft_lst_insert_when(t_list **list, \
t_list *new_node, bool (*comparison)(void *, void *));
t_array	ft_lst_to_array(t_list **list, size_t member_size, void (*del)(void *));
t_list	*ft_lstnext_and_delete(t_list *node, void (*del)(void *));

//iterates through the string, returns true if any of its characters
//matches one of the characters from charset
int		ft_strhas(char *str, char *charset);

//takes a null terminated array of strings
//allocates and returns a string that is all the strings concatenated together 
char	*ft_multistrjoin(char **strings);

//reads file returning one line each call
//returns null when there's nothing more to read
char	*get_next_line(int fd);

/*end of additional stuff*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
