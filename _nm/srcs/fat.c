/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:39:48 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/22 18:54:11 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

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
