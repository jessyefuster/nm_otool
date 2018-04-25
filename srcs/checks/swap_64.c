/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:45:59 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 14:46:58 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

void		swap_mach_header_64(struct mach_header_64 *header)
{
	header->filetype = swap_uint32(header->filetype);
	header->ncmds = swap_uint32(header->ncmds);
	header->sizeofcmds = swap_uint32(header->sizeofcmds);
}

void		swap_segment_64(struct segment_command_64 *segment)
{
	segment->nsects = swap_uint32(segment->nsects);
}

void		swap_section_64(struct section_64 *section)
{
	section->size = swap_uint64(section->size);
	section->offset = swap_uint32(section->offset);
	section->addr = swap_uint64(section->addr);
}

void		swap_nlist_64(struct nlist_64 *symbol)
{
	symbol->n_un.n_strx = swap_uint32(symbol->n_un.n_strx);
	symbol->n_value = swap_uint64(symbol->n_value);
}
