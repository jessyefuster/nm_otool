NAME = ft_nm

FLAGS = -Wall -Wextra -Werror

LIBFT = -L../libft/ -lft

SRCS =	srcs/archive.c \
		srcs/core.c \
		srcs/fat.c \
		srcs/macho.c \
		srcs/main.c \
		srcs/tools.c \

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