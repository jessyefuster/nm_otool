NAME = ft_nm

FLAGS = -Wall -Wextra -Werror

LIBFT = -L../libft/ -lft

SRCS = srcs/main.c \
		srcs/tools.c \
		srcs/macho_32_handler.c \
		srcs/macho_64_handler.c \
		srcs/core_handler.c \
		srcs/fat_handler.c \
		srcs/print_symbols.c

SRCO = $(SRCS:.c=.o)

%.o:%.c
	gcc -c $< -o $@

all: $(NAME)

$(NAME): $(SRCO)
	gcc -o $(NAME) $(LIBFT) $(SRCO)

clean:
	rm -f $(SRCO)

fclean: clean
	rm -f $(NAME)

re: fclean all