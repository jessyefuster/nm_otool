NAME = ft_otool

FLAGS = -Wall -Wextra -Werror

LIBFT = ../../libft/libft.a

SRCS =	srcs/main.c \
		../archive.c \
		../fat.c \
		../tools.c \
		../checks/archive.c \
		../checks/fat.c \
		../checks/file.c \
		../checks/macho.c \
		../checks/macho_32.c \
		../checks/macho_64.c \
		../checks/tools.c \
		../checks/swap.c \

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