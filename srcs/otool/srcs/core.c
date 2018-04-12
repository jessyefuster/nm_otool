/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessyefuster <jessyefuster@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:35:09 by jessyefuster      #+#    #+#             */
/*   Updated: 2018/04/11 20:41:05 by jessyefuster     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_otool.h"

/*
**	Search for __text section in Mach-o file
**	note : this function handles both 32bit and 64bit arch
*/

void		handle_macho(t_file *file)
{
	size_t					i;
	size_t					ncmds;
	struct load_command		*lc;
	void					*text_section;

	printf("Contents of (__TEXT,__text) section\n");
	ncmds = ((struct mach_header *)file->ptr)->ncmds;
	lc = (struct load_command *)(((struct mach_header_64 *)file->ptr) + 1);
	if (F_IS_32(file->type))
		lc = (struct load_command *)(((struct mach_header *)file->ptr) + 1);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64 || lc->cmd == LC_SEGMENT)
		{
			text_section = get_text_section(file, (void *)lc);
			if (text_section)
			{
				print_text_section(file, text_section);
				break ;
			}
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

/*
**	Iterate over arch headers in FAT file and otool each binary
*/

void		handle_fat(t_file *file)
{
	size_t				i;
	char				*name;
	struct fat_header	*fat_header;
	struct fat_arch		*fat_arch;

	fat_header = (struct fat_header *)file->ptr;
	if ((fat_arch = find_arch(fat_header, CPU_TYPE_X86_64)))
		ft_otool(file->ptr + fat_arch->offset, file->name, fat_arch->size, FALSE);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < fat_header->nfat_arch)
		{
			name = ft_strjoin(file->name, arch_name(fat_arch->cputype));
			ft_otool(file->ptr + fat_arch->offset, name, fat_arch->size, TRUE);
			free(name);
			fat_arch++;
			i++;
		}
	}
}

/*
**	https://code.woboq.org/llvm/include/ar.h.html
**	https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg
**	WIP
*/

void		handle_archive(t_file *file)
{
	char			*member_name;
	size_t			member_name_size;
	size_t			offset;
	struct ar_hdr	*header;

	offset = SARMAG;
	if (file->size == SARMAG)
		return ;
	while (file->size > offset)
	{
		header = (struct ar_hdr *)(file->ptr + offset);
		offset += sizeof(struct ar_hdr);
		member_name = header->ar_name;
		member_name_size = size_ar_name(header);
		if (is_extended(header))
		{
			member_name = file->ptr + offset;
			member_name_size = ft_atoi(header->ar_name + sizeof(AR_EFMT1) - 1);
		}
		if (ft_strncmp(member_name, SYMDEF, member_name_size) && ft_strncmp(member_name, SYMDEF_SORTED, member_name_size))
		{
			if (is_extended(header))
				ft_otool(file->ptr + offset + member_name_size, format_archive_name(file->name, member_name, MIN((size_t)member_name_size, ft_strlen(member_name))), ft_atoi(header->ar_size) - member_name_size, TRUE);
			else
				ft_otool(file->ptr + offset, format_archive_name(file->name, member_name, member_name_size), ft_atoi(header->ar_size), TRUE);
		}
		offset += ft_atoi(header->ar_size);
	}
}
