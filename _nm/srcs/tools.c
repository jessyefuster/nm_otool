/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:52:19 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/15 15:35:48 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int			ft_error(char *message)
{
	ft_putstr(message);
	return (1);
}

uint32_t	swap_endian(uint32_t num)
{
	uint32_t b0;
	uint32_t b1;
	uint32_t b2;
	uint32_t b3;

	b0 = (num & 0x000000ff) << 24u;
	b1 = (num & 0x0000ff00) << 8u;
	b2 = (num & 0x00ff0000) >> 8u;
	b3 = (num & 0xff000000) >> 24u;

	return (b0 | b1 | b2 | b3);
}

char		section_letter(char *segname)
{
	if (ft_strcmp(segname, "__text") == 0)
		return ('T');
	else if (ft_strcmp(segname, "__data") == 0)
		return ('D');
	else if (ft_strcmp(segname, "__bss") == 0)
		return ('B');
	return ('S');
}

static	uint32_t	get_macho_type(uint32_t file_type)
{
	if (file_type == MH_OBJECT)
		return (F_OBJECT);
	else if (file_type == MH_EXECUTE)
		return (F_EXECUTE);
	else if (file_type == MH_FVMLIB)
		return (F_FVMLIB);
	else if (file_type == MH_CORE)
		return (F_CORE);
	else if (file_type == MH_PRELOAD)
		return (F_PRELOAD);
	else if (file_type == MH_DYLIB || file_type == MH_DYLIB_STUB)
		return (F_DYLIB);
	else if (file_type == MH_DYLINKER)
		return (F_DYLINKER);
	else if (file_type == MH_BUNDLE)
		return (F_BUNDLE);
	return (0);
}

// https://code.woboq.org/llvm/include/ar.h.html
// https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg
uint32_t			get_file_type(char *file)
{
	uint32_t	file_type;
	uint32_t	magic;

	file_type = 0;
	magic = *(int *)file;
	// printf("magic:  %x\n", magic);
	if (magic == MH_MAGIC)
		file_type |= F_32 | F_MACHO;
	else if (magic == MH_MAGIC_64)
		file_type |= F_64 | F_MACHO;
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		file_type |= F_FAT;
	else
		return (0);

	if (file_type & F_MACHO)
		file_type |= get_macho_type(((struct mach_header *)file)->filetype);
	
	// printf("filetype: %s\n", ft_utob(file_type, 2, "01"));
	// printf("arch: %04s\n", ft_utob((file_type & 0xF00) >> 8, 2, "01"));



	return (file_type);
}
