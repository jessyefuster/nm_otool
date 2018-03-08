NAME = ft_nm

FLAGS = -Wall -Wextra -Werror

LIBFT = ../libft/libft.a

SRCS =	srcs/archive.c \
		srcs/core.c \
		srcs/fat.c \
		srcs/list.c \
		srcs/macho.c \
		srcs/main.c \
		srcs/sections.c \
		srcs/sort.c \
		srcs/tools.c \
		srcs/checks/check_archive.c \
		srcs/checks/check_fat.c \
		srcs/checks/check_file.c \
		srcs/checks/check_macho.c \

SRCO = $(SRCS:.c=.o)

%.o:%.c
	gcc -c $< -o $@ $(FLAGS)

all: $(NAME)

$(NAME): $(SRCO)
	gcc -o $(NAME) $(LIBFT) $(SRCO)

clean:
	rm -f $(SRCO)

fclean: clean
	rm -f $(NAME)

re: fclean all