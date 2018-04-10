CURRENT_DIR = $(PWD)

LIBFT_DIR = libft/

NM_DIR = srcs/nm/
OTOOL_DIR = srcs/otool/

NM = nm
OTOOL = otool

all: $(NM)

nm:
	make -C libft/
	make -C $(NM_DIR)
	cp $(NM_DIR)ft_nm ./

otool:
	make -C $(LIBFT_DIR)
	make -C $(OTOOL_DIR)
	cp $(OTOOL_DIR)ft_otool ./

clean:
	make -C libft/ clean
	make -C $(NM_DIR) clean

fclean: clean
	make -C libft/ fclean
	make -C $(NM_DIR) fclean
	rm -rf ./ft_nm

re: fclean all
