/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/08 14:26:42 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

uint64_t	g_maxaddr = 0;

bool	ft_nm(char *file, char *filename, size_t file_size, bool print_filename)
{
	t_filetype_t	file_type;
	t_symbols		*symbols;

	symbols = NULL;
	file_type = get_file_type(file, file_size);
	if (file_type & F_MACHO)
	{
		printf("DO MACHO (print name: %s)\n", print_filename ? "true" : "false");
		// if (print_filename)
		// 	printf("\n%s:\n", filename);
		// handle_macho(file, file_type, &symbols);
		// print_symbols(file, symbols, file_type);
	}
	else if (file_type & F_FAT)
		printf("DO FAT\n");
		// handle_fat(file, filename);
	else if (file_type & F_ARCHIVE)
		printf("DO ARCHIVE\n");
		// handle_archive(file, filename);
	else
		return (file_error(filename));
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
	if ((file = mmap(0, (*file_info).st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (NULL);
	g_maxaddr = (uint64_t)(file + (*file_info).st_size);
	close(fd);
	return (file);
}

void	nm_if_valid(char *filename, bool print_filename)
{
	char		*file;
	struct stat	file_info;

	if ((file = valid_file(filename, &file_info)))
	{
		if (!ft_nm(file, filename, file_info.st_size, print_filename))
			munmap(file, file_info.st_size);
	}
	else
		file_error(filename);
}

int		main(int argc, char **argv)
{
	int		i;

	if (argc > 2)
	{
		i = 1;
		while (i < argc)
		{
			nm_if_valid(argv[i], TRUE);
			i++;
		}
	}
	else if (argc == 2)
		nm_if_valid(argv[1], FALSE);
	else
		nm_if_valid("a.out", FALSE);
	return (0);
}
