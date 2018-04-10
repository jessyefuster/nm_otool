/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:01:25 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/10 16:24:08 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_nm_otool.h"

char			*format_archive_name(char *archive_name, char *member_name, size_t member_name_len)
{
	size_t	archive_name_len;
	size_t	name_len;
	char	*new_name;

	(void)member_name;

	archive_name_len = ft_strlen(archive_name);
	name_len = archive_name_len + member_name_len;
	if ((new_name = (char *)malloc(sizeof(char) * (name_len + 2 + 1))) == NULL)
		exit_error("malloc error");
	new_name[name_len + 2] = 0;
	ft_strcpy(new_name, archive_name);
	new_name[archive_name_len] = '(';
	ft_strncpy(new_name + archive_name_len + 1, member_name, member_name_len);
	new_name[name_len + 1] = ')';
	return (new_name);
}
