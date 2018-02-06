/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:01:14 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/06 16:02:58 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void		display_symbols_64(char *file, struct symtab_command *symtab_cmd)
{
	int					i;
	int					string_index;
	struct nlist_64		*sym_table;
	char				*string_table;

	sym_table = (struct nlist_64 *)(file + symtab_cmd->symoff);
	string_table = file + symtab_cmd->stroff;

	i = 0;
	while (i < symtab_cmd->nsyms)
	{
		string_index = sym_table->n_un.n_strx;
		if (sym_table->n_value != 0)
			printf("%016llx  %s  %s\n", sym_table->n_value, symbol_type(sym_table->n_type, sym_table->n_sect, sym_table->n_value), string_table + string_index);
		else
			printf("                   %s  %s\n", symbol_type(sym_table->n_type, sym_table->n_sect, sym_table->n_value),string_table + string_index);
		sym_table = sym_table + 1;
		i++;
	}
}

void		ft_handle_macho_32(char *file)
{
	printf("HANDLE MACHO 32\n");
}

void		ft_handle_macho_64(char *file)
{
	printf("HANDLE MACHO 64\n");
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
			printf("SEGMENT FOUND :  symtab_command\n");
			display_symbols_64(file, (struct symtab_command *)load_cmds);
			// symtab_cmd = (struct symtab_command *)load_cmds;
			// printf("number of symbols : %d\n", symtab_cmd->nsyms);
			// break ;
		}
		if (load_cmds->cmd == LC_SEGMENT_64)
		{
			printf("SEGMENT FOUND :  n_sects -> %d,  segment_name -> %s\n", ((struct segment_command_64 *)load_cmds)->nsects, ((struct segment_command_64 *)load_cmds)->segname);
		}
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
		i++;
	}
}
