/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:20 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/10 16:27:43 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

size_t	size_ar_name(struct ar_hdr *header)
{
	long i;

	i = sizeof(header->ar_name) - 1;
	while (i >= 0 && header->ar_name[i] == ' ')
		i--;
	return ((size_t)(i + 1));
}

bool				is_extended(struct ar_hdr *header)
{
	if (ft_strncmp(header->ar_name, AR_EFMT1, sizeof(AR_EFMT1) - 1) == 0)
		return (TRUE);
	return (FALSE);
}

static enum check_result	check_archive_header(struct ar_hdr *header)
{
	size_t	i;
	char	*p;

	i = sizeof(AR_EFMT1) - 1;
	p = (char *)header;
	if (is_extended(header))
	{
		while (i < sizeof(header->ar_name))
		{
			if (p[i] != ' ' && !ft_isdigit(p[i]))
				return (CHECK_BAD);
			i++;
		}
	}
	i = 0;
	p = (char *)header->ar_size;
	while (i < sizeof(header->ar_size))
	{
		if (p[i] != ' ' && !ft_isdigit(p[i]))
			return (CHECK_BAD);
		i++;
	}
	if (ft_strncmp(header->ar_fmag, ARFMAG, sizeof(ARFMAG) - 1) != 0)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

// check on badnamesize archive
enum check_result			check_archive(t_file *file)
{
	uint32_t		*o_magic;
	size_t			offset;
	struct ar_hdr	*ah;

	offset = SARMAG;
	if (file->size == SARMAG)
		return (CHECK_GOOD);
	while (file->size > offset + 1)
	{
		ah = (struct ar_hdr *)(file->ptr + offset);
		if (offset + sizeof(struct ar_hdr) > file->size)
			return (filecheck_error(file->name, "no size for archive header"));
		if (check_archive_header(ah) == CHECK_BAD)
			return (filecheck_error(file->name, "malformed archive header"));
		offset += sizeof(struct ar_hdr);
		if (ft_atoi(ah->ar_size) == 0 || file->size < offset + ft_atoi(ah->ar_size))
			return (filecheck_error(file->name, "invalid archive member size"));
		if (is_extended(ah))
		{
			if (file->size < offset + ft_atoi(ah->ar_name + sizeof(AR_EFMT1) - 1))
				return (filecheck_error(file->name, "no size for archive member name"));
			o_magic = (uint32_t *)(file->ptr + offset + ft_atoi(ah->ar_name + sizeof(AR_EFMT1) - 1));
			if (offset + ft_atoi(ah->ar_name + sizeof(AR_EFMT1) - 1) + sizeof(uint32_t) > file->size || *o_magic == FAT_CIGAM)
				return (filecheck_error(file->name, "cannot contain FAT object"));
		}
		else
		{
			o_magic = (uint32_t *)(file->ptr + offset);
			if (offset + sizeof(uint32_t) > file->size || *o_magic == FAT_CIGAM)
				return (filecheck_error(file->name, "archive cannot contain FAT object"));
		}
		offset += ft_atoi(ah->ar_size);
	}
	return (CHECK_GOOD);
}
