/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/06 02:16:49 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	Search for SYMTAB load command in Mach-o file
**	note : this function handles both 32bit and 64bit arch
**	note : this function handles endianess
*/

void		handle_macho(char *file, uint32_t file_type, t_symbols **symbols)
{
	size_t					i;
	size_t					ncmds;
	struct load_command		*load_cmds;

	ncmds = S_32(((struct mach_header *)file)->ncmds, file_type);
	load_cmds = (struct load_command *)(((struct mach_header_64 *)file) + 1);
	if (F_ARCH(file_type) == F_32)
		load_cmds = (struct load_command *)(((struct mach_header *)file) + 1);
	i = 0;
	while (i < ncmds)
	{
		if (S_32(load_cmds->cmd, file_type) == LC_SYMTAB)
		{
			store_symbols(file, file_type, (struct symtab_command *)load_cmds,
				symbols);
			break ;
		}
		load_cmds = (void *)load_cmds + S_32(load_cmds->cmdsize, file_type);
		i++;
	}
}

/*
**	Iterate over arch headers in FAT file and nm each binary
*/

void		handle_fat(char *file, char *filename)
{
	size_t				i;
	char				*name;
	struct fat_header	*fat_header;
	struct fat_arch		*fat_arch;

	fat_header = (struct fat_header *)file;
	if ((fat_arch = find_arch(fat_header, CPU_TYPE_X86_64)))
		ft_nm(file + swap_uint32(fat_arch->offset), filename, FALSE);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < swap_uint32(fat_header->nfat_arch))
		{
			name = ft_strjoin(filename, arch_name(swap_uint32(fat_arch->cputype)));
			ft_nm(file + swap_uint32(fat_arch->offset), name, TRUE);
			free(name);
			fat_arch++;
			i++;
		}
	}
}

/*
**	https://code.woboq.org/llvm/include/ar.h.html
**	https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg
*/

void		handle_archive(char *file, char *filename)
{
	size_t			i;
	struct ar_hdr	*header;
	char			*macho;
	char			*name;
	size_t			*offsets;

	offsets = archive_offsets((struct ar_hdr *)(file + SARMAG));
	if (offsets == NULL)
	{
		file_error("");
		return ;
	}

	i = 0;
	while (offsets[i])
	{
		header = (struct ar_hdr *)(file + offsets[i]);
		macho = (char *)(header + 1) + ft_atoi((char *)header + 3);
		name = ft_strjoin(filename, archive_name((char *)(header + 1)));
		ft_nm(macho, name, TRUE);
		i++;
	}
}
