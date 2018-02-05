/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:52:19 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/05 17:13:27 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int			ft_error(char *message)
{
	ft_putstr(message);
	return (1);
}


static	uint32_t	get_macho_type(uint32_t file_type)
{
	if (header->filetype == MH_OBJECT)
		return (F_OBJECT);
	else if (header->filetype == MH_EXECUTE)
		return (F_EXECUTE);
	else if (header->filetype == MH_FVMLIB)
		return (F_FVMLIB);
	else if (header->filetype == MH_CORE)
		return (F_CORE);
	else if (header->filetype == MH_PRELOAD)
		return (F_PRELOAD);
	else if (header->filetype == MH_DYLIB || header->filetype == MH_DYLIB_STUB)
		return (F_DYLIB);
	else if (header->filetype == MH_DYLINKER)
		return (F_DYLINKER);
	else if (header->filetype == MH_BUNDLE)
		return (F_BUNDLE);
	return (0);
}

// https://code.woboq.org/llvm/include/ar.h.html
// https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg
uint32_t			get_file_type(char *file)
{
	uint32_t				file_type;

	file_type = 0;
	magic = *(int *)file;
	if (magic == MH_MAGIC)
		file_type |= F_32 | F_MACHO;
	else if (magic == MH_MAGIC_64)
		file_type |= F_64 | F_MACHO;
	else if (magic == FAT_MAGIC)
		file_type |= F_FAT;
	else
		return (0);

	if (file_type & F_MACHO)
		file_type |= get_macho_type(file_type);
	
	printf("arch: %d\n", (file_type & F_32) ? 32 : 64);

	return (file_type);
}
