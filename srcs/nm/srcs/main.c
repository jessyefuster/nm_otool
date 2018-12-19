/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/12/19 16:38:07 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

enum e_status	init_file_info(t_file **file_info, char *file, char *filename,
				size_t file_size)
{
	if (((*file_info = (t_file *)malloc(sizeof(t_file))) == NULL))
		return (program_error("Malloc error", __FILE__, __LINE__));
	(*file_info)->ptr = file;
	(*file_info)->size = file_size;
	(*file_info)->name = filename;
	(*file_info)->ft = NM;
	(*file_info)->type = get_file_type(*file_info);
	return (S_SUCCESS);
}

enum e_status	ft_nm(char *ptr, char *filename, size_t file_size,
				enum e_print print)
{
	t_file		*file;
	t_symbols	*symbols;

	symbols = NULL;
	// printf("CHECK\n");
	if (init_file_info(&file, ptr, filename, file_size) == S_FAILURE)
		return (S_FAILURE);
	if (file->type & F_MACHO)
	{
		// printf("MACHO\n");
		if (handle_macho(file, &symbols) == S_FAILURE)
			return (S_FAILURE);
		if (print)
		{
			if (print & P_NEWLINE)
				printf("\n");
			if (print & P_NAME)
				printf("%s:\n", file->name);
		}
		if (print_symbols(file, symbols) == S_FAILURE)
			return (S_FAILURE);
	}
	else if (file->type & F_FAT)
	{
		// printf("FAT\n");
		return (handle_fat(file));
	}
	else if (file->type & F_ARCHIVE)
	{
		// printf("ARCHIVE\n");
		return (handle_archive(file));
	}
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

enum e_status	nm_if_valid_file(char *filename, enum e_print print)
{
	char			*ptr;
	struct stat		file_info;
	enum e_status	status;

	ptr = map_file(filename, &file_info);
	if (ptr)
	{
		status = ft_nm(ptr, filename, file_info.st_size, print);
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
			errors += !nm_if_valid_file(argv[i], P_REGULAR);
			i++;
		}
	}
	else if (argc == 2)
		errors = !nm_if_valid_file(argv[1], P_NONE);
	else
		errors = !nm_if_valid_file("a.out", P_NONE);
	if (errors)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
