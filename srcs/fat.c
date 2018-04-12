/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/12 15:50:45 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_nm_otool.h"

char				*arch_name(cpu_type_t type)
{
	if (type == CPU_TYPE_I386)
		return (" (for architecture i386)");
	else if (type == CPU_TYPE_X86_64)
		return (" (for architecture x86_64)");
	else if (type == CPU_TYPE_VAX)
		return (" (for architecture vax)");
	else if (type == CPU_TYPE_MC680x0)
		return (" (for architecture mc680x0)");
	else if (type == CPU_TYPE_MC98000)
		return (" (for architecture mc98000)");
	else if (type == CPU_TYPE_HPPA)
		return (" (for architecture hppa)");
	else if ((type == CPU_TYPE_ARM) || (type == CPU_TYPE_ARM64))
		return (" (for architecture arm)");
	else if (type == CPU_TYPE_MC88000)
		return (" (for architecture mc88000)");
	else if (type == CPU_TYPE_SPARC)
		return (" (for architecture sparc)");
	else if (type == CPU_TYPE_I860)
		return (" (for architecture i860)");
	else if ((type == CPU_TYPE_POWERPC) || (type == CPU_TYPE_POWERPC64))
		return (" (for architecture ppc)");
	else
		return (" (for architecture \?\?\?)");
}

char				*arch_name_short(cpu_type_t type)
{
	if (type == CPU_TYPE_I386)
		return (" (architecture i386)");
	else if (type == CPU_TYPE_X86_64)
		return (" (architecture x86_64)");
	else if (type == CPU_TYPE_VAX)
		return (" (architecture vax)");
	else if (type == CPU_TYPE_MC680x0)
		return (" (architecture mc680x0)");
	else if (type == CPU_TYPE_MC98000)
		return (" (architecture mc98000)");
	else if (type == CPU_TYPE_HPPA)
		return (" (architecture hppa)");
	else if ((type == CPU_TYPE_ARM) || (type == CPU_TYPE_ARM64))
		return (" (architecture arm)");
	else if (type == CPU_TYPE_MC88000)
		return (" (architecture mc88000)");
	else if (type == CPU_TYPE_SPARC)
		return (" (architecture sparc)");
	else if (type == CPU_TYPE_I860)
		return (" (architecture i860)");
	else if ((type == CPU_TYPE_POWERPC) || (type == CPU_TYPE_POWERPC64))
		return (" (architecture ppc)");
	else
		return (" (architecture \?\?\?)");
}

struct fat_arch		*find_arch(struct fat_header *fat_header, cpu_type_t arch)
{
	size_t				i;
	struct fat_arch		*fat_arch;

	fat_arch = (struct fat_arch *)(fat_header + 1);
	i = 0;
	while (i < fat_header->nfat_arch)
	{
		if (fat_arch->cputype == arch)
			return (fat_arch);
		fat_arch++;
		i++;
	}
	return (NULL);
}
