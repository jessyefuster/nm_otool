/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:01:14 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/16 16:08:40 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void		display_symbols_64(char *file, struct mach_header_64 *header, struct symtab_command *symtab_cmd)
{
	int					i;
	int					string_index;
	struct nlist_64		*sym_table;
	char				*string_table;
	char				**sections;

	sym_table = (struct nlist_64 *)(file + symtab_cmd->symoff);
	string_table = file + symtab_cmd->stroff;
	sections = get_sections_64(header, (struct load_command *)(header + 1));
	i = 0;
	while (i < symtab_cmd->nsyms)
	{
		string_index = sym_table->n_un.n_strx;
		if (!(sym_table->n_type & N_STAB))
		{
			if (sym_table->n_value != 0)
				printf("%016llx %c %s\n", sym_table->n_value, symbol_64(file, sections, sym_table, string_table), string_table + string_index);
			else
				printf("%18c %s\n", symbol_64(file, sections, sym_table, string_table), string_table + string_index);
		}
		sym_table = sym_table + 1;
		i++;
	}
}

void		ft_handle_macho_64(char *file)
{
	int						i;
	struct mach_header_64	*header;
	struct load_command		*load_cmds;
	struct symtab_command	*symtab_cmd;

	header = (struct mach_header_64 *)file;
	load_cmds = (struct load_command *)(header + 1);
	i = 0;
	while (i < header->ncmds)
	{
		if (load_cmds->cmd == LC_SYMTAB)
		{
			display_symbols_64(file, header, (struct symtab_command *)load_cmds);
			break ;
		}
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
		i++;
	}
}
