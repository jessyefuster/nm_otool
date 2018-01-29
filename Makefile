NAME = ft_nm

FLAGS = -Wall -Wextra -Werror

LIBFT = -L./libft/ -lft

SRCS = srcs/nm.c

SRCO = $(SRCS:.c=.o)

%.o:%.c
	gcc -c $< -o $@

all: $(NAME)

$(NAME): $(SRCO)
	make -C libft/
	gcc -o $(NAME) $(LIBFT) $(SRCO)

# $(SRCO):
# 	gcc -c $(SRCS) $<

clean:
	make -C libft/ clean
	rm -f $(SRCO)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all