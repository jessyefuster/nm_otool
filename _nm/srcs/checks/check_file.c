/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 23:56:49 by jessye            #+#    #+#             */
/*   Updated: 2018/03/07 02:21:44 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

// bool		is_archive(char *ptr, size_t size)
// {
// 	if (size >= SARMAG && ft_strncmp(ptr, ARMAG, SARMAG) == 0)
// 		return (TRUE);
// 	return (FALSE);
// }

// static	t_filetype_t	get_macho_type(t_filetype_t file_type)
// {
// 	if (file_type == MH_OBJECT)
// 		return (F_OBJECT);
// 	else if (file_type == MH_EXECUTE)
// 		return (F_EXECUTE);
// 	else if (file_type == MH_FVMLIB)
// 		return (F_FVMLIB);
// 	else if (file_type == MH_CORE)
// 		return (F_CORE);
// 	else if (file_type == MH_PRELOAD)
// 		return (F_PRELOAD);
// 	else if (file_type == MH_DYLIB || file_type == MH_DYLIB_STUB)
// 		return (F_DYLIB);
// 	else if (file_type == MH_DYLINKER)
// 		return (F_DYLINKER);
// 	else if (file_type == MH_BUNDLE)
// 		return (F_BUNDLE);
// 	return (0);
// }

/*
**	Try to first-guess file type based on its magic number
*/

static t_filetype_t		guess_file_type(char *file, size_t size)
{
	uint32_t		magic;
	t_filetype_t	file_type;

	magic = 0;
	file_type = 0;
	if (size >= SARMAG && ft_strncmp(file, ARMAG, SARMAG) == 0)
		file_type |= F_ARCHIVE;
	else
	{
		if (size >= sizeof(magic))
			magic = *((uint32_t *)file);
		if (magic == MH_MAGIC)
			file_type |= F_32 | F_MACHO | F_LITTLE;
		else if (magic == MH_CIGAM)
			file_type |= F_32 | F_MACHO | F_BIG;
		else if (magic == MH_MAGIC_64)
			file_type |= F_64 | F_MACHO | F_LITTLE;
		else if (magic == MH_CIGAM_64)
			file_type |= F_64 | F_MACHO | F_BIG;
		else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
			file_type |= F_FAT;
	}
	return (file_type);
}

/*
**	Parse file to get its type
**	note : this function makes security and consistency checks of the file
**	WIP
*/

t_filetype_t			get_file_type(char *file, size_t size)
{
	t_filetype_t	file_type;

	file_type = guess_file_type(file, size);

	// if (file_type & F_MACHO)
	// 	file_type |= get_macho_type(((struct mach_header *)file)->filetype);
	return (file_type);
}
