/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:52:19 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/19 17:01:59 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

bool		file_error(char *filename)
{
	fprintf(stderr, "ft_nm: %s: error occured\n", filename);
	return (TRUE);
}

bool		valid_addr(void *ptr)
{
	if ((uint64_t)ptr > g_maxaddr)
		return (FALSE);
	return (TRUE);
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

char		type_letter(char **sections, t_symbols *symbol)
{
	char	type_letter;

	type_letter = '?';
	if (symbol->type & N_STAB)
		return ('-');
	else if ((symbol->type & N_TYPE) == N_UNDF)
	{
		type_letter = 'U';
		if (symbol->value)
			type_letter = 'C';
		// if ((symbol->type & N_EXT))
		// 	return (ft_toupper(type_letter));
	}
	else if ((symbol->type & N_TYPE) == N_ABS)
		type_letter = 'A';
	else if ((symbol->type & N_TYPE) == N_INDR)
		type_letter = 'I';
	else if (symbol->type & N_SECT)
		type_letter = section_letter(sections[symbol->sect]);
	if (!(symbol->type & N_EXT))
		type_letter = ft_tolower(type_letter);
	return (type_letter);
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

uint32_t			get_file_type(char *file)
{
	uint32_t	file_type;
	uint32_t	magic;

	file_type = 0;
	magic = *(int *)file;
	printf("magic  %x\n", magic);
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
	else
		return (0);
	if (file_type & F_MACHO)
		file_type |= get_macho_type(((struct mach_header *)file)->filetype);
	return (file_type);
}
