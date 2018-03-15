/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/15 21:27:56 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	Search for SYMTAB load command in Mach-o file
**	note : this function handles both 32bit and 64bit arch
**	note : this function handles endianess
*/

void		handle_macho(t_file *file, t_symbols **symbols)
{
	size_t					i;
	size_t					ncmds;
	struct load_command		*load_cmds;

	ncmds = ((struct mach_header *)file->ptr)->ncmds;
	load_cmds = (struct load_command *)(((struct mach_header_64 *)file->ptr) + 1);
	if (F_IS_32(file->type))
		load_cmds = (struct load_command *)(((struct mach_header *)file->ptr) + 1);
	i = 0;
	while (i < ncmds)
	{
		if (load_cmds->cmd == LC_SYMTAB)
		{
			store_symbols(file, (struct symtab_command *)load_cmds, symbols);
			break ;
		}
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
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
		ft_nm(file + fat_arch->offset, filename, fat_arch->size, FALSE);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < fat_header->nfat_arch)
		{
			name = ft_strjoin(filename, arch_name(fat_arch->cputype));
			ft_nm(file + fat_arch->offset, name, fat_arch->size, TRUE);
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

	// offsets = archive_offsets((struct ar_hdr *)(file + SARMAG));
	if ((offsets = archive_offsets((struct ar_hdr *)(file + SARMAG))) == NULL)
	{
		file_error(filename);
		return ;
	}

	i = 0;
	while (offsets[i])
	{
		header = (struct ar_hdr *)(file + offsets[i]);
		macho = (char *)(header + 1) + ft_atoi((char *)header + 3);
		name = archive_name((char *)(header + 1));
		if (name)
			name = ft_strjoin(filename, name);
		ft_nm(macho, name, ft_atoi(header->ar_size), TRUE);
		i++;
	}
}
