/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:30:08 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/10 16:35:46 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_otool.h"

enum status		ft_otool()
{
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
	close(fd);
	return (file);
}

enum status		otool_if_valid_file(char *filename, bool print_filename)
{
	char			*ptr;
	struct stat		file_info;
	enum status		status;

(void)print_filename;
	ptr = map_file(filename, &file_info);
	if (ptr)
	{
		status = ft_otool();
		munmap(ptr, file_info.st_size);
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
			errors += !otool_if_valid_file(argv[i], TRUE);
			i++;
		}
	}
	else if (argc == 2)
		errors = !otool_if_valid_file(argv[1], FALSE);
	else
		errors = !otool_if_valid_file("a.out", FALSE);

	if (errors)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}