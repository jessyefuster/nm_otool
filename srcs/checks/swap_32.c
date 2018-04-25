/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:50:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 14:48:40 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

void		swap_mach_header(struct mach_header *header)
{
	header->filetype = swap_uint32(header->filetype);
	header->ncmds = swap_uint32(header->ncmds);
	header->sizeofcmds = swap_uint32(header->sizeofcmds);
}

void		swap_segment(struct segment_command *segment)
{
	segment->nsects = swap_uint32(segment->nsects);
}

void		swap_section(struct section *section)
{
	section->size = swap_uint32(section->size);
	section->offset = swap_uint32(section->offset);
	section->addr = swap_uint32(section->addr);
}

void		swap_nlist(struct nlist *symbol)
{
	symbol->n_un.n_strx = swap_uint32(symbol->n_un.n_strx);
	symbol->n_value = swap_uint32(symbol->n_value);
}
