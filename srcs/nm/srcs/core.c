/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/12/30 16:58:31 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"
#define IS_ONE(value) (value == 1)

/*
**	Search for SYMTAB load command in Mach-o file
**	note : this function handles both 32bit and 64bit arch
**	note : this function handles endianess
*/

enum e_status			handle_macho(t_file *file, t_symbols **symbols)
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
			return (store_symbols(file, (struct symtab_command *)load_cmds,
			symbols));
		}
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
		i++;
	}
	return (S_SUCCESS);
}

/*
**	Iterate over arch headers in FAT file and nm each binary
*/

static enum e_status	handle_fat_core(t_file *file,
	struct fat_header *fat_header)
{
	size_t				i;
	char				*name;
	struct fat_arch		*fat_arch;
	char				status;

	status = S_SUCCESS;
	fat_arch = (struct fat_arch *)(fat_header + 1);
	i = 0;
	while (i < fat_header->nfat_arch)
	{
		name = ft_strjoin(file->name, arch_name(fat_arch->cputype));
		if (name == NULL || ft_nm(file->ptr + fat_arch->offset,
		fat_header->nfat_arch > 1 ? name : file->name, fat_arch->size,
		(IS_ONE(fat_header->nfat_arch) ? P_NAME : P_REGULAR)) == S_FAILURE)
		{
			status = S_FAILURE;
		}
		fat_arch++;
		i++;
	}
	return (status);
}

enum e_status			handle_fat(t_file *file)
{
	struct fat_header	*fat_header;
	struct fat_arch		*fat_arch;

	fat_header = (struct fat_header *)file->ptr;
	if ((fat_arch = find_arch(fat_header, CPU_TYPE_X86_64)))
		return (ft_nm(file->ptr + fat_arch->offset, file->name, fat_arch->size,
		P_NONE));
	else
		return (handle_fat_core(file, fat_header));
}

/*
**	Archive handling
*/

static enum e_status	call_nm(t_file *file, struct ar_hdr *header,
size_t offset, t_ar_member m)
{
	char	*filename;
	size_t	size;

	if (is_extended(header))
	{
		filename = format_archive_name(file->name, m.name,
					MIN((size_t)(m.name_size), ft_strlen(m.name)));
		if (filename == NULL)
			return (program_error("Malloc error", __FILE__, __LINE__));
		size = ft_atoi(header->ar_size) - m.name_size;
		return (ft_nm(file->ptr + offset + m.name_size, filename, size,
			P_REGULAR));
	}
	else
	{
		filename = format_archive_name(file->name, m.name, m.name_size);
		if (filename == NULL)
			return (program_error("Malloc error", __FILE__, __LINE__));
		size = ft_atoi(header->ar_size);
		return (ft_nm(file->ptr + offset, filename, size, P_REGULAR));
	}
}

enum e_status			handle_archive(t_file *file)
{
	struct ar_hdr	*header;
	t_ar_member		member;
	size_t			offset;

	offset = SARMAG;
	if (file->size == SARMAG)
		return (S_SUCCESS);
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
		{
			if (call_nm(file, header, offset, member) == S_FAILURE)
				return (S_FAILURE);
		}
		offset += ft_atoi(header->ar_size);
	}
	return (S_SUCCESS);
}
