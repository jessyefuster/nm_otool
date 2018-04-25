/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:47:34 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 14:48:54 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

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
