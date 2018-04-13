NAME = ft_nm

FLAGS = -Wall -Wextra -Werror

LIBFT = ../../libft/libft.a

SRCS =	../archive.c \
		srcs/core.c \
		../fat.c \
		srcs/list.c \
		srcs/macho.c \
		srcs/main.c \
		srcs/sections.c \
		srcs/symbols.c \
		../tools.c \
		../checks/archive.c \
		../checks/fat.c \
		../checks/file.c \
		../checks/macho.c \
		../checks/macho_32.c \
		../checks/macho_64.c \
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
