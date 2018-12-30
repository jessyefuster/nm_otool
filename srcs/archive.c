/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:01:25 by jfuster           #+#    #+#             */
/*   Updated: 2018/12/30 16:47:13 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_nm_otool.h"

void			set_member(t_ar_member *m, char *name, size_t name_size)
{
	m->name = name;
	m->name_size = name_size;
}

char			*format_archive_name(char *archive_name, char *member_name,
						size_t member_name_len)
{
	size_t	archive_name_len;
	size_t	name_len;
	char	*new_name;

	archive_name_len = ft_strlen(archive_name);
	name_len = archive_name_len + member_name_len;
	if ((new_name = (char *)malloc(sizeof(char) * (name_len + 2 + 1))) == NULL)
		return (NULL);
	new_name[name_len + 2] = 0;
	ft_strcpy(new_name, archive_name);
	new_name[archive_name_len] = '(';
	ft_strncpy(new_name + archive_name_len + 1, member_name, member_name_len);
	new_name[name_len + 1] = ')';
	return (new_name);
}
