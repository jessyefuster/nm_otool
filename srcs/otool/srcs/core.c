/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:35:09 by jessyefuster      #+#    #+#             */
/*   Updated: 2018/04/16 16:33:59 by jfuster          ###   ########.fr       */
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
		ft_otool(file->ptr + fat_arch->offset, file->name, fat_arch->size);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < fat_header->nfat_arch)
		{
			name = ft_strjoin(file->name, arch_name_short(fat_arch->cputype));
			ft_otool(file->ptr + fat_arch->offset, name, fat_arch->size);
			free(name);
			fat_arch++;
			i++;
		}
	}
}

/*
**	Archive handling
*/

static void	set_member(t_ar_member *m, char *name, size_t name_size)
{
	m->name = name;
	m->name_size = name_size;
}

static void	call_otool(t_file *file, struct ar_hdr *header, size_t offset,
			t_ar_member m)
{
	char	*filename;
	size_t	size;

	if (is_extended(header))
	{
		filename = format_archive_name(file->name, m.name,
					MIN((size_t)(m.name_size), ft_strlen(m.name)));
		size = ft_atoi(header->ar_size) - m.name_size;
		ft_otool(file->ptr + offset + m.name_size, filename, size);
	}
	else
	{
		filename = format_archive_name(file->name, m.name, m.name_size);
		size = ft_atoi(header->ar_size);
		ft_otool(file->ptr + offset, filename, size);
	}
}

void		handle_archive(t_file *file)
{
	struct ar_hdr	*header;
	t_ar_member		member;
	size_t			offset;

	printf("Archive : %s\n", file->name);
	offset = SARMAG;
	if (file->size == SARMAG)
		return ;
	while (file->size > offset)
	{
		header = (struct ar_hdr *)(file->ptr + offset);
		offset += sizeof(struct ar_hdr);
		set_member(&member, header->ar_name, size_ar_name(header));
		if (is_extended(header))
			set_member(&member, file->ptr + offset,
				ft_atoi(header->ar_name + sizeof(AR_EFMT1) - 1));
		if (ft_strncmp(member.name, SYMDEF, member.name_size) &&
				ft_strncmp(member.name, SYMDEF_SORTED, member.name_size))
			call_otool(file, header, offset, member);
		offset += ft_atoi(header->ar_size);
	}
}
