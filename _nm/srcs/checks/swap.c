/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:50:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/15 16:22:05 by jfuster          ###   ########.fr       */
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
	(void)header;
	// arch->cputype = (cpu_type_t)swap_uint32(arch->cputype);
	// arch->offset = swap_uint32(arch->offset);
	// arch->size = swap_uint32(arch->size);
}
