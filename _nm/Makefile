NAME = ft_nm

FLAGS = -Wall -Wextra -Werror

LIBFT = -L../libft/ -lft

SRCS = srcs/main.c

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