/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:20 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/22 16:35:37 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

// get size after #1/
static size_t size_ar_name(struct ar_hdr *header)
{
	(void)header;
	return (0);
}

static enum check_result	check_archive_header(struct ar_hdr *header)
{
	(void)header;
	return (CHECK_GOOD);
}

enum check_result			check_archive(t_file *file)
{
	// uint32_t		*magic;
	size_t			offset;
	// size_t			name_size;
	// size_t			member_size;
	struct ar_hdr	*ah;

	
	offset = SARMAG;
	if (file->size == SARMAG)
		return (CHECK_GOOD);
	while (file->size > offset)
	{
		ah = (struct ar_hdr *)(file->ptr + offset);
		printf("\nheader |%s|\n", file->ptr + offset );

		if (offset + sizeof(struct ar_hdr) > file->size)
			return (filecheck_error(file->name, "no size for archive header"));
		if (check_archive_header(ah) == CHECK_BAD)
			return (filecheck_error(file->name, "malformed archive header"));
		offset += sizeof(struct ar_hdr);
		if (ft_atoi(ah->ar_size) == 0 || file->size < offset + ft_atoi(ah->ar_size))
			return (filecheck_error(file->name, "invalid archive member size"));

		if (ft_strncmp(ah->ar_name, AR_EFMT1 , sizeof(AR_EFMT1) - 1) == 0)
		{
			if (file->size < offset + size_ar_name(ah))
				return (filecheck_error(file->name, "no size for archive member name"));
		}
		else
		{
			//
		}

		// if (ft_strncmp(ah->ar_name, AR_EFMT1 , sizeof(AR_EFMT1) - 1) == 0)
		// {
		// 	name_size = ft_atoi(ah->ar_name + sizeof(AR_EFMT1) - 1);
		// 	printf("member name %s\n", file->ptr + offset);
		// 	printf("member name size %zu\n", name_size);
		// 	if (offset + name_size > file->size)
		// 		return (filecheck_error(file->name, "invalid archive member size"));
		// 	printf("magic %x\n", *((uint32_t *)(file->ptr + offset + name_size)));
		// }
		// else
		// {
		// 	printf("member name %16s\n", ah->ar_name);
		// 	printf("magic %x\n", *((uint32_t *)(file->ptr + offset)));
		// }
		offset += ft_atoi(ah->ar_size);
	}

	return (CHECK_GOOD);
}
