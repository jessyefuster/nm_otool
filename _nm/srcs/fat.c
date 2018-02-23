/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/23 15:23:34 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char				*arch_name(cpu_type_t type)
{
	if (type == CPU_TYPE_I386)
		return (ft_strdup(" (for architecture i386)"));
	else if (type == CPU_TYPE_X86_64)
		return (ft_strdup(" (for architecture x86_64)"));
	else if (type == CPU_TYPE_VAX)
		return (ft_strdup(" (for architecture vax)"));
	else if (type == CPU_TYPE_MC680x0)
		return (ft_strdup(" (for architecture mc680x0)"));
	else if (type == CPU_TYPE_MC98000)
		return (ft_strdup(" (for architecture mc98000)"));
	else if (type == CPU_TYPE_HPPA)
		return (ft_strdup(" (for architecture hppa)"));
	else if ((type == CPU_TYPE_ARM) || (type == CPU_TYPE_ARM64))
		return (ft_strdup(" (for architecture arm)"));
	else if (type == CPU_TYPE_MC88000)
		return (ft_strdup(" (for architecture mc88000)"));
	else if (type == CPU_TYPE_SPARC)
		return (ft_strdup(" (for architecture sparc)"));
	else if (type == CPU_TYPE_I860)
		return (ft_strdup(" (for architecture i860)"));
	else if ((type == CPU_TYPE_POWERPC) || (type == CPU_TYPE_POWERPC64))
		return (ft_strdup(" (for architecture ppc)"));
	else
		return (ft_strdup(" (for architecture \?\?\?)"));
}

struct fat_arch		*find_arch(struct fat_header *fat_header, cpu_type_t arch)
{
	size_t				i;
	struct fat_arch		*fat_arch;

	fat_arch = (struct fat_arch *)(fat_header + 1);
	i = 0;
	while (i < swap_uint32(fat_header->nfat_arch))
	{
		if ((cpu_type_t)swap_uint32(fat_arch->cputype) == arch)
			return (fat_arch);
		fat_arch++;
		i++;
	}
	return (NULL);
}
