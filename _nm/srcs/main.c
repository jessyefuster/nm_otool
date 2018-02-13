/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/13 16:54:27 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void	ft_nm(char *file)
{
	uint32_t	file_type;

	file_type = get_file_type(file);
	if (file_type & F_MACHO)
	{
		ft_putendl("File type:   MACHO FILE");
		ft_handle_macho(file, file_type);
	}
	else if (file_type & F_FAT)
	{
		ft_putendl("File type:   FAT FILE");
		ft_handle_fat(file, file_type);
	}
	else if (file_type & F_ARCHIVE)
	{
		ft_putendl("File type:   ARCHIVE FILE");
	}
	else
		ft_putendl("File type:   NONE");
}

// int		main(int argc, char **argv)
// {
// 	int				fd;
// 	char			*file;
// 	struct stat		file_info;

// 	if (argc != 2)
// 		return (ft_error("Error\n"));

// 	if ((fd = open(argv[1], O_RDONLY)) < 0)
// 		return (ft_error("Open error\n"));

// 	if (fstat(fd, &file_info) < 0 || file_info.st_mode & S_IFDIR)
// 		return (ft_error("Fstat error\n"));

// 	if ((file = mmap(0, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
// 		return (ft_error("Mmap error\n"));


// 	ft_nm(file);

// 	return (0);
// }
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

	close(fd);

	return (file);
}

void	nm_if_valid(char *filename)
{
	char		*file;
	struct stat	file_info;

	if ((file = valid_file(filename, &file_info)))
	{
		printf("valid file : %s\n", filename);
		ft_nm(file);
		munmap(file, file_info.st_size);
	}
	else
		printf("invalid file : %s\n", filename);
}

int		main(int argc, char **argv)
{
	size_t		i;
	char		*file;

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
