/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:56:25 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/16 16:08:43 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	SECTIONS 64
*/
static void	store_sections_64(struct segment_command_64 *segment, char **sections, size_t *i_sect)
{
	size_t				i;
	struct section_64	*section;

	i = 0;
	section = (struct section_64 *)(segment + 1);
	while (i < segment->nsects)
	{
		sections[(*i_sect)] = ft_strdup(section->sectname);
		(*i_sect)++;
		section++;
		i++;
	}
}

char		**get_sections_64(struct mach_header_64 *header, struct load_command *load_cmds)
{
	size_t					i;
	size_t					i_sect;
	char					**sections;
	struct section_64		*section;

	i_sect = 1;
	sections = (char **)malloc(sizeof(char *) * 256);
	i = 0;
	while (i < header->ncmds)
	{
		if (load_cmds->cmd == LC_SEGMENT_64)
			store_sections_64((struct segment_command_64 *)load_cmds, sections, &i_sect);
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
		i++;
	}
	return (sections);
}

/*
**	SECTIONS 32
*/
static void	store_sections_32(struct segment_command *segment, char **sections, size_t *i_sect)
{
	size_t				i;
	struct section		*section;

	i = 0;
	section = (struct section *)(segment + 1);
	while (i < segment->nsects)
	{
		sections[(*i_sect)] = ft_strdup(section->sectname);
		(*i_sect)++;
		section++;
		i++;
	}
}

char		**get_sections_32(struct mach_header *header, struct load_command *load_cmds)
{
	size_t					i;
	size_t					i_sect;
	char					**sections;
	struct section			*section;

	i_sect = 1;
	sections = (char **)malloc(sizeof(char *) * 256);
	i = 0;
	while (i < header->ncmds)
	{
		if (load_cmds->cmd == LC_SEGMENT)
			store_sections_32((struct segment_command *)load_cmds, sections, &i_sect);
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
		i++;
	}
	return (sections);
}

char		symbol_32(char *file, char **sections, struct nlist *symbol, char *string_table)
{
	static char		type_letter = ' ';

	// printf("flags %s\n", ft_utob(symbol->n_type, 2, "01"));

	if (symbol->n_type & N_STAB)
		return ('-');
	// else if (symbol->n_type & N_PEXT)
	// 	return ('u');
	else if ((symbol->n_type & N_TYPE) == N_ABS)
		type_letter = 'A';
	else if ((symbol->n_type & N_TYPE) == N_INDR)
		type_letter = 'I';
	else if (symbol->n_type == N_EXT)
	{
		if (symbol->n_value)
			return ('C');
		return ('U');
	}
	else if (symbol->n_type & N_SECT)
		type_letter = section_letter(sections[symbol->n_sect]);
	if (!(symbol->n_type & N_EXT))
		type_letter = ft_tolower(type_letter);
	return (type_letter);
}

char		symbol_64(char *file, char **sections, struct nlist_64 *symbol, char *string_table)
{
	static char		type_letter = ' ';

	// printf("flags %s\n", ft_utob(symbol->n_type, 2, "01"));

	if (symbol->n_type & N_STAB)
		return ('-');
	// else if (symbol->n_type & N_PEXT)
	// 	return ('u');
	else if ((symbol->n_type & N_TYPE) == N_ABS)
		type_letter = 'A';
	else if ((symbol->n_type & N_TYPE) == N_INDR)
		type_letter = 'I';
	else if (symbol->n_type == N_EXT)
	{
		if (symbol->n_value)
			return ('C');
		return ('U');
	}
	else if (symbol->n_type & N_SECT)
		type_letter = section_letter(sections[symbol->n_sect]);
	if (!(symbol->n_type & N_EXT))
		type_letter = ft_tolower(type_letter);
	return (type_letter);
}
