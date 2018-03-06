/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 23:56:49 by jessye            #+#    #+#             */
/*   Updated: 2018/03/07 00:31:38 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static	t_filetype_t	get_macho_type(t_filetype_t file_type)
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

t_filetype_t			get_file_type(char *file)
{
	t_filetype_t	file_type;
	uint32_t		magic;

	file_type = 0;
	magic = *(int *)file;
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
	else if (is_archive(file))
		file_type |= F_ARCHIVE;
	else
		return (0);
	if (file_type & F_MACHO)
		file_type |= get_macho_type(((struct mach_header *)file)->filetype);
	return (file_type);
}
