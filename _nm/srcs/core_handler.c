/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/12 17:09:58 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void		ft_handle_macho(char *file, uint32_t file_type)
{
	if (file_type & F_32)
		ft_handle_macho_32(file);
	else if (file_type & F_64)
		ft_handle_macho_64(file);
}

void		ft_handle_fat(char *file, uint32_t file_type)
{
	size_t				i;
	struct fat_header	*fat_header;
	struct fat_arch		*fat_arch;

	fat_header = (struct fat_header *)file;
	fat_arch = (struct fat_arch *)(fat_header + 1);
	i = 0;
	while (i < swap_endian(fat_header->nfat_arch))
	{
		printf("cpu type : %d\n", swap_endian(fat_arch->cputype));
		if (swap_endian(fat_arch->cputype) == CPU_TYPE_X86_64)
			printf("ARCH FOUND (%zu)\n", i);
		fat_arch++;
		i++;
	}
}

void		ft_handle_archive(char *file, uint32_t file_type)
{

}
