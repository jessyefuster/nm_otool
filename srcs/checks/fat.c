/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:13:56 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/10 16:27:47 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

enum check_result	check_fat(t_file *file)
{
	struct fat_header	*fh;
	struct fat_arch		*fa;
	size_t				i;

	fh = (struct fat_header *)(file->ptr);
	fa = (struct fat_arch *)(fh + 1);
	swap_fat_header(fh);
	if (file->size < sizeof(struct fat_header))
		return (filecheck_error(file->name, "no size for fat header"));
	if (file->size < sizeof(struct fat_header) + fh->nfat_arch * sizeof(struct fat_arch))
		return (filecheck_error(file->name, "no size for fat archs"));
	if (fh->nfat_arch == 0)
		return (filecheck_error(file->name, "incorrect nfat_arch in fat header"));
	i = 0;
	while (i < fh->nfat_arch)
	{
		swap_fat_arch(fa);
		if (fa->offset == 0)
			return (filecheck_error(file->name, "arch offset is 0"));
		if (file->size < fa->offset + fa->size)
			return (filecheck_error(file->name, "no size for arch"));
		fa++;
		i++;
	}
	return (CHECK_GOOD);
}
