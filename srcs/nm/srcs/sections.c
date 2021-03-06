/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 01:30:05 by jessye            #+#    #+#             */
/*   Updated: 2018/04/30 16:19:14 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm.h"

char		section_letter(char *segname)
{
	if (segname == NULL)
		return ('S');
	if (ft_strcmp(segname, "__text") == 0)
		return ('T');
	else if (ft_strcmp(segname, "__data") == 0)
		return ('D');
	else if (ft_strcmp(segname, "__bss") == 0)
		return ('B');
	else
		return ('S');
}

static void	store_sections(void *segment, char **sections,
			t_filetype_t file_type, size_t *i_sect)
{
	size_t			i;
	size_t			nsects;
	void			*section;

	nsects = ((struct segment_command_64 *)segment)->nsects;
	section = ((struct segment_command_64 *)segment) + 1;
	if (F_IS_32(file_type))
	{
		nsects = ((struct segment_command *)segment)->nsects;
		section = ((struct segment_command *)segment) + 1;
	}
	i = 0;
	while (i < nsects)
	{
		if (F_IS_32(file_type))
			sections[(*i_sect)] = ((struct section *)section)->sectname;
		else
			sections[(*i_sect)] = ((struct section_64 *)section)->sectname;
		section += SECTION_SIZE(F_IS_32(file_type));
		(*i_sect)++;
		i++;
	}
}

/*
**	Store section names in a tab in order of appearance
**	note : this function handles both 32bit and 64bit arch
**	note : this function handles endianess
*/

char		**get_sections(struct mach_header *header, t_filetype_t file_type)
{
	size_t					i;
	size_t					i_sect;
	char					**sections;
	struct load_command		*load_cmd;

	if ((sections = (char **)malloc(sizeof(char *) * 256)) == NULL)
		return (NULL);
	load_cmd = (void *)(((struct mach_header_64 *)header) + 1);
	if (F_IS_32(file_type))
		load_cmd = (void *)(header + 1);
	i = 0;
	i_sect = 1;
	while (i < header->ncmds)
	{
		if (load_cmd->cmd == LC_SEGMENT_64 || load_cmd->cmd == LC_SEGMENT)
			store_sections((void *)load_cmd, sections, file_type, &i_sect);
		load_cmd = (void *)load_cmd + load_cmd->cmdsize;
		i++;
	}
	return (sections);
}
