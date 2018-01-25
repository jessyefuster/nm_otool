/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:30:05 by jfuster           #+#    #+#             */
/*   Updated: 2018/01/25 16:18:39 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <mach-o/loader.h>
#include <mach-o/nlist.h>



int		ft_error(char *message)
{
	printf("%s\n", message);
	return (1);
}

void	nm(char *file)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64 *)file;
	if (header->magic == MH_MAGIC_64)
		printf("bravo ! %x\n", header->magic);
	else
		printf("non\n");
}

int		main(int argc, char **argv)
{
	int				fd;
	struct stat		file_info;
	char			*file;

	if (argc != 2)
		return (ft_error("Error\n"));

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error("Open error\n"));

	if (fstat(fd, &file_info) < 0)
		return (ft_error("Fstat error\n"));

	if ((file = mmap(0, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error("Mmap error\n"));

	nm(file);

	return (0);
}