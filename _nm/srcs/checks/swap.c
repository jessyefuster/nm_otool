/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:50:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/15 20:59:31 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

void		swap_fat_header(struct fat_header *header)
{
	header->nfat_arch = swap_uint32(header->nfat_arch);
}

void		swap_fat_arch(struct fat_arch *arch)
{
	arch->cputype = (cpu_type_t)swap_uint32(arch->cputype);
	arch->offset = swap_uint32(arch->offset);
	arch->size = swap_uint32(arch->size);
}

void		swap_mach_header(struct mach_header *header)
{
	header->filetype = swap_uint32(header->filetype);
	header->ncmds = swap_uint32(header->ncmds);
	header->sizeofcmds = swap_uint32(header->sizeofcmds);
}

void		swap_mach_header_64(struct mach_header_64 *header)
{
	header->filetype = swap_uint32(header->filetype);
	header->ncmds = swap_uint32(header->ncmds);
	header->sizeofcmds = swap_uint32(header->sizeofcmds);
}

void		swap_load_command(struct load_command *command)
{
	command->cmd = swap_uint32(command->cmd);
	command->cmdsize = swap_uint32(command->cmdsize);
}

void		swap_symtab(struct symtab_command *symtab)
{
	symtab->symoff = swap_uint32(symtab->symoff);
	symtab->nsyms = swap_uint32(symtab->nsyms);
	symtab->stroff = swap_uint32(symtab->stroff);
	symtab->strsize = swap_uint32(symtab->strsize);
}

void		swap_segment(struct segment_command *segment)
{
	segment->nsects = swap_uint32(segment->nsects);
}

void		swap_segment_64(struct segment_command_64 *segment)
{
	segment->nsects = swap_uint32(segment->nsects);
}

void		swap_nlist(struct nlist *symbol)
{
	symbol->n_un.n_strx = swap_uint32(symbol->n_un.n_strx);
	symbol->n_value = swap_uint32(symbol->n_value);
}

void		swap_nlist_64(struct nlist_64 *symbol)
{
	symbol->n_un.n_strx = swap_uint32(symbol->n_un.n_strx);
	symbol->n_value = swap_uint64(symbol->n_value);
}
