/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/16 16:42:09 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void		ft_handle_macho(char *file, uint32_t file_type, t_symbols *symbols)
{
	//to do : add in symbols list rather than print
	if (file_type & F_32)
		ft_handle_macho_32(file);
	else if (file_type & F_64)
		ft_handle_macho_64(file);
}

void		ft_handle_fat(char *file, uint32_t file_type, char *filename)
{
	size_t				i;
	char				*name;
	struct fat_header	*fat_header;
	struct fat_arch		*fat_arch;

	fat_header = (struct fat_header *)file;
	name = ft_strjoin(filename, " (for architecture x86_64)");
	if ((fat_arch = find_arch(fat_header, CPU_TYPE_X86_64)))
		ft_nm(file + swap_endian(fat_arch->offset), name);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < swap_endian(fat_header->nfat_arch))
		{
			name = ft_strjoin(filename, " (for architecture ...)");
			ft_nm(file + swap_endian(fat_arch->offset), name);
			free(name);
			fat_arch++;
			i++;
		}
		return ;
	}
	free(name);
}

void		ft_handle_archive(char *file, uint32_t file_type)
{

}
