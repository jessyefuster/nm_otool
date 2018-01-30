CURRENT_DIR = $(PWD)

LIBFT_DIR = libft/

NM_DIR = _nm/
OTOOL_DIR = _otool/

NM = nm
OTOOL = otool

all: $(NM) $(OTOOL)

nm:
	make -C libft/
	make -C $(NM_DIR)
	cp $(NM_DIR)ft_nm ./

otool:
	make -C $(LIBFT_DIR)
	make -C $(OTOOL_DIR)
	cp $(OTOOL_DIR)ft_nm ./

clean:
	make -C libft/ clean
	make -C $(NM_DIR) clean

fclean: clean
	make -C libft/ fclean
	make -C $(NM_DIR) fclean
	rm -rf ./ft_nm

re: fclean all
