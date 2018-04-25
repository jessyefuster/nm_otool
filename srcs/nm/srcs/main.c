/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 14:21:39 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

void			init_file_info(t_file *file_info, char *file, char *filename,
				size_t file_size)
{
	file_info->ptr = file;
	file_info->size = file_size;
	file_info->name = filename;
	file_info->type = 0;
}

enum e_status	ft_nm(char *ptr, char *filename, size_t file_size,
				bool print_filename)
{
	t_file		*file;
	t_symbols	*symbols;

	symbols = NULL;
	if (((file = (t_file *)malloc(sizeof(t_file))) == NULL))
		exit_error("malloc error");
	init_file_info(file, ptr, filename, file_size);
	file->type = get_file_type(file);
	if (file->type & F_MACHO)
	{
		if (print_filename)
			printf("\n%s:\n", file->name);
		handle_macho(file, &symbols);
		print_symbols(file, symbols);
	}
	else if (file->type & F_FAT)
		handle_fat(file);
	else if (file->type & F_ARCHIVE)
		handle_archive(file);
	else
		return (S_FAILURE);
	return (S_SUCCESS);
}

char			*map_file(char *filename, struct stat *file_info)
{
	int			fd;
	char		*file;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if (fstat(fd, file_info) < 0 || (*file_info).st_mode & S_IFDIR)
		return (NULL);
	if ((file = mmap(0, (*file_info).st_size,
	PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NULL);
	close(fd);
	return (file);
}

enum e_status	nm_if_valid_file(char *filename, bool print_filename)
{
	char			*ptr;
	struct stat		file_info;
	enum e_status	status;

	ptr = map_file(filename, &file_info);
	if (ptr)
	{
		status = ft_nm(ptr, filename, file_info.st_size, print_filename);
		munmap(ptr, file_info.st_size);
		return (status);
	}
	else
	{
		filecheck_error(filename, "file map error");
		return (S_FAILURE);
	}
}

int				main(int argc, char **argv)
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
