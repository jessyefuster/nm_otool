/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:56:25 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/07 16:06:57 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

char		**get_sections_64(char *file)
{
	size_t					i;
	size_t					j;
	size_t					i_sect;
	struct mach_header_64	*header;
	struct load_command		*load_cmds;
	struct segment_command_64	*segment_cmd;
	struct section_64			*section;
	char					**sections;

	header = (struct mach_header_64 *)file;
	load_cmds = (struct load_command *)(header + 1);
	sections = (char **)malloc(sizeof(char *) * 256);

	i = 0;
	i_sect = 1;
	while (i < header->ncmds)
	{
		if (load_cmds->cmd == LC_SEGMENT_64)
		{
			// printf("SEGMENT FOUND :  n_sects -> %d,  segment_name -> %s\n", ((struct segment_command_64 *)load_cmds)->nsects, ((struct segment_command_64 *)load_cmds)->segname);
			j = 0;
			segment_cmd = (struct segment_command_64 *)load_cmds;
			printf("SEGMENT : %p\n", segment_cmd);
			section = (struct section_64 *)(segment_cmd + 1);
			printf("SEGMENT : %p\n", segment_cmd);
			while (j < segment_cmd->nsects)
			{
				// printf("section number %zu found : %s   in    %s\n", i_sect, section->sectname, section->segname);
				sections[i_sect] = ft_strdup(section->segname);
				// printf("%zu  %s\n", i_sect, sections[i_sect]);

				i_sect++;
				section = section + 1;
				j++;
			}
		}
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
		i++;
	}

	return (sections);
}

char		symbol_64(char *file, char **sections, struct nlist_64 *symbol, char *string_table)
{
	char	type_letter;

	if (symbol->n_type == N_EXT)
	{
		if (symbol->n_value)
			return ('C');
		return ('U');
	}
	if (symbol->n_type & N_SECT)
	{
		// printf("sect %d\n", symbol->n_sect);
		type_letter = section_letter(sections[symbol->n_sect]);
		if (!(symbol->n_type & 1))
			type_letter = ft_tolower(type_letter);
		return (type_letter);
	}
	// if (type == N_EXT)
	// {
	// 	if (value)
	// 		return ("C");
	// 	return ("U");
	// }
	// if (type == N_STAB)
	// 	return ("-");
	// if (type & N_SECT)
	// {
	// 	printf("%d - ", sect);
	// 	if (type & 1)
	// 		return ("ext_sect");
	// 	return ("loc_sect");
	// }
	// if (type & N_UNDF)
	// 	return ("U");
	// if (type & N_ABS)
	// 	return ("A");
	return ('X');
}
