/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:20 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/21 16:46:38 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static enum check_result	check_archive_header(struct ar_hdr *header)
{
	(void)header;
	return (CHECK_GOOD);
}

enum check_result			check_archive(t_file *file)
{
	size_t			offset;
	struct ar_hdr	*member_header;
	
	offset = SARMAG;
	if (file->size == SARMAG)
		return (CHECK_GOOD);
	while (file->size > offset)
	{
		member_header = (struct ar_hdr *)(file->ptr + offset);
		if (offset + sizeof(struct ar_hdr) > file->size)
			return (filecheck_error(file->name, "no size for archive header"));
		if (check_archive_header(member_header) == CHECK_BAD)
			return (filecheck_error(file->name, "malformed archive header"));
		if (offset + ft_atoi(member_header->ar_size) > offset)
			return (filecheck_error(file->name, "inavlid archive member size"));
		offset += sizeof(struct ar_hdr);
		if (ft_strncmp(member_header->ar_name, AR_EFMT1 , sizeof(AR_EFMT1) - 1) == 0)
		{
			printf("%x\n", *((uint32_t *)( file->ptr + offset + ft_atoi((char *)(member_header->ar_name) + sizeof(AR_EFMT1))) )      );
		}
		else
		{
			printf("%x\n", *((uint32_t *)(file->ptr + offset)));
		}
		offset += ft_atoi(member_header->ar_size);


	}

	// printf("%c\n", *(file->ptr + SARMAG));
	filecheck_error(file->name, "bad archive");
	return (CHECK_BAD);
}
