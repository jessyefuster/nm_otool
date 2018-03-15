/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:13:56 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/15 21:24:07 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

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
		if (file->size < fa->offset + fa->size)
			return (filecheck_error(file->name, "no size for arch"));
		fa++;
		i++;
	}
	return (CHECK_GOOD);
}
