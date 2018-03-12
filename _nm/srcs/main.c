/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/12 17:18:23 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

uint64_t	g_maxaddr = 0;

enum status		ft_nm(char *file, char *filename, size_t file_size, bool print_filename)
{
	t_filetype_t	file_type;
	t_symbols		*symbols;

	symbols = NULL;
	file_type = get_file_type(file, filename, file_size);
	if (file_type & F_MACHO)
	{
		printf("ft_nm: %-50s: DO MACHO (print name: %s)\n", filename, print_filename ? "true" : "false");
		// if (print_filename)
		// 	printf("\n%s:\n", filename);
		// handle_macho(file, file_type, &symbols);
		// print_symbols(file, symbols, file_type);
	}
	else if (file_type & F_FAT)
		printf("ft_nm: %-50s: DO FAT\n",filename);
		// handle_fat(file, filename);
	else if (file_type & F_ARCHIVE)
		printf("ft_nm: %-50s: DO ARCHIVE\n",filename);
		// handle_archive(file, filename);
	else
		return (S_FAILURE);
		// return (file_error(filename));
	return (S_SUCCESS);
}

char	*map_file(char *filename, struct stat *file_info)
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

enum status		nm_if_valid_file(char *filename, bool print_filename)
{
	char			*file;
	struct stat		file_info;
	enum status		status;

	file = map_file(filename, &file_info);
	if (file)
	{
		status = ft_nm(file, filename, file_info.st_size, print_filename);
		munmap(file, file_info.st_size);
		return (status);
	}
	else
	{
		file_error(filename);
		return (S_FAILURE);
	}
}

int		main(int argc, char **argv)
{
	int		i;
	int		errors;

	errors = 0;
	if (argc > 2)
	{
		i = 1;
		while (i < argc)
		{
			errors += !nm_if_valid_file(argv[i], TRUE);
			i++;
		}
	}
	else if (argc == 2)
		errors = !nm_if_valid_file(argv[1], FALSE);
	else
		errors = !nm_if_valid_file("a.out", FALSE);

	if (errors)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
