# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 15:01:24 by fedmarti          #+#    #+#              #
#    Updated: 2023/10/10 21:57:14 by fedmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES := ft_atoi.c \
	ft_bzero.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_substr.c \
	ft_calloc.c \
	ft_strnstr.c \
	ft_abs.c \
	ft_abs_d.c \
	ft_sign.c \
	ft_free_matrix.c \
	ft_matrix_init.c \
	ft_lstsize.c \
	ft_swap.c \
	ft_max.c \
	ft_min.c \
	ft_clamp.c \
	ft_is_in_list.c \
	ft_lst_iteri_2.c \
	ft_lstclear_2.c \
	ft_lst_swap_next.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lst_insert.c \
	ft_read_file.c \
	ft_lst_to_matrix.c \
	ft_lst_to_array.c \
	ft_lstpop_one.c \
	ft_lstnext_and_delete.c \
	ft_array_free.c \
	ft_matrix_size.c \
	ft_strhas.c \
	ft_multistrjoin.c \
	ft_copy_up_to.c \
	get_next_line.c \
	get_next_line_utils.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS += -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJECTS)
	@ ar rc $@ $^
#	@ echo $^
	@ echo "$(NAME) compiled ✅"

bonus: $(NAME)

%.o:%.c
	@ gcc $(CFLAGS) -c -I. $< -o $@

clean:
	@ rm -f *.o

fclean: clean
	@ rm -f $(NAME)

re: fclean all
