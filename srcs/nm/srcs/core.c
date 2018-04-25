/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 14:37:49 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

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
	load_cmds = (struct load_command *)(((struct mach_header_64 *)file->ptr)
				+ 1);
	if (F_IS_32(file->type))
		load_cmds = (struct load_command *)(((struct mach_header *)file->ptr)
					+ 1);
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

void		handle_fat(t_file *file)
{
	size_t				i;
	char				*name;
	struct fat_header	*fat_header;
	struct fat_arch		*fat_arch;

	fat_header = (struct fat_header *)file->ptr;
	if ((fat_arch = find_arch(fat_header, CPU_TYPE_X86_64)))
		ft_nm(file->ptr + fat_arch->offset, file->name, fat_arch->size, FALSE);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < fat_header->nfat_arch)
		{
			name = ft_strjoin(file->name, arch_name(fat_arch->cputype));
			ft_nm(file->ptr + fat_arch->offset, name, fat_arch->size, TRUE);
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

static void	call_nm(t_file *file, struct ar_hdr *header, size_t offset,
			t_ar_member m)
{
	char	*filename;
	size_t	size;

	if (is_extended(header))
	{
		filename = format_archive_name(file->name, m.name,
					MIN((size_t)(m.name_size), ft_strlen(m.name)));
		size = ft_atoi(header->ar_size) - m.name_size;
		ft_nm(file->ptr + offset + m.name_size, filename, size, TRUE);
	}
	else
	{
		filename = format_archive_name(file->name, m.name, m.name_size);
		size = ft_atoi(header->ar_size);
		ft_nm(file->ptr + offset, filename, size, TRUE);
	}
}

void		handle_archive(t_file *file)
{
	struct ar_hdr	*header;
	t_ar_member		member;
	size_t			offset;

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
			call_nm(file, header, offset, member);
		offset += ft_atoi(header->ar_size);
	}
}
