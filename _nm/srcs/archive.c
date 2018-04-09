/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:01:25 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/09 16:18:41 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char			*archive_name(char *name)
{
	size_t	name_len;
	char	*new_name;

	name_len = ft_strlen(name);
	if ((new_name = (char *)malloc(sizeof(char) * (name_len + 2 + 1))) == NULL)
		return (NULL);
	new_name[name_len + 2] = 0;
	new_name[0] = '(';
	ft_strcpy(&new_name[1], name);
	new_name[name_len + 1] = ')';
	return (new_name);
}

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
	ft_memset(new_name, 'x', sizeof(char) * name_len + 2);
	new_name[name_len + 2] = 0;
	ft_strcpy(new_name, archive_name);
	new_name[archive_name_len] = '(';
	ft_strncpy(new_name + archive_name_len + 1, member_name, member_name_len);
	new_name[name_len + 1] = ')';
	return (new_name);
}

static bool		in_array(size_t *tab, size_t len, size_t value)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (tab[i] == value)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static size_t	*store_offsets(struct ranlib *ranlib, size_t n_rans)
{
	size_t	i;
	size_t	tab_i;
	size_t	*offsets;

	if ((offsets = (size_t *)malloc(sizeof(size_t) * (n_rans + 1))) == NULL)
		return (NULL);
	ft_bzero(offsets, (n_rans + 1) * sizeof(size_t));
	tab_i = 0;
	i = 0;
	while (i < n_rans)
	{
		if (!in_array(offsets, n_rans, ranlib->ran_off))
		{
			offsets[tab_i] = ranlib->ran_off;
			tab_i++;
		}
		i++;
		ranlib++;
	}
	sort_tab(offsets, tab_i);
	return (offsets);
}

// BESOIN DE PROTECTION
size_t	*archive_offsets(struct ar_hdr *header)
{
	size_t			n_rans;
	struct ranlib	*ran;
	size_t			*offsets;

	n_rans = *((uint32_t *)((char *)(header + 1) + ft_atoi((char *)header + 3))) / sizeof(struct ranlib);
	ran = (struct ranlib *)((char *)(header + 1) + ft_atoi((char *)header + 3) + sizeof(uint32_t));

	// if (!valid_addr((void *)ran) || n_rans == 0)
		// return (NULL);
	offsets = store_offsets(ran, n_rans);

	return (offsets);
}
