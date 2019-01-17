# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jessyefuster <jessyefuster@student.42.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 12:47:10 by jfuster           #+#    #+#              #
#    Updated: 2019/01/17 13:45:13 by jessyefuster     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCS = ft_memset.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_memalloc.c \
		ft_bzero.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putnstr.c \
		ft_putendl.c \
		ft_putchar_fd.c \
		ft_putchar_unicode.c \
		ft_putstr_fd.c \
		ft_putstr_unicode.c \
		ft_putendl_fd.c\
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strlen_unicode.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isalpha.c \
		ft_isprint.c \
		ft_islower.c \
		ft_isupper.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_str_toupper.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_ltoa.c \
		ft_utob.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putnbr_abs.c \
		ft_putnbr_lint_abs.c \
		ft_strclr.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strjoin.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_numlen.c \
		ft_usage.c \
		get_next_line.c \
		fprint/ft_fprint.c \
		fprint/print.c \
		fprint/checks.c \
		fprint/tools.c


OBJ = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -o $@ -c $< $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
