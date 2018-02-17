/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/17 19:35:43 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

uint64_t	G_MAXADDR = 0;

bool	ft_nm(char *file, char *filename)
{
	uint32_t	file_type;
	t_symbols	*symbols;

	symbols = NULL;
	file_type = get_file_type(file);
	if (file_type & F_MACHO)
	{
		printf("\n%s:\n", filename);
		handle_macho(file, file_type, &symbols);
		print_symbols(file, symbols, file_type);
	}
	else if (file_type & F_FAT)
		handle_fat(file, filename);
	else if (file_type & F_ARCHIVE)
		ft_putendl("File type:   ARCHIVE FILE");
	else
		return (TRUE);
	return (FALSE);
}

char	*valid_file(char *filename, struct stat *file_info)
{
	int			fd;
	char		*file;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);

	if (fstat(fd, file_info) < 0 || (*file_info).st_mode & S_IFDIR)
		return (NULL);

	if ((file = mmap(0, (*file_info).st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NULL);

	G_MAXADDR = (uint64_t)(file + (*file_info).st_size);
	close(fd);

	return (file);
}

void	nm_if_valid(char *filename)
{
	char		*file;
	struct stat	file_info;

	if ((file = valid_file(filename, &file_info)) && !ft_nm(file, filename))
		munmap(file, file_info.st_size);
	else
		fprintf(stderr, "ft_nm: %s: error occured\n", filename);
}

int		main(int argc, char **argv)
{
	int		i;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			nm_if_valid(argv[i]);
			i++;
		}
	}
	else
		nm_if_valid("a.out");

	return (0);
}
