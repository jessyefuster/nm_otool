/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:30:05 by jfuster           #+#    #+#             */
/*   Updated: 2018/01/31 15:31:30 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

int lol;

int		ft_error(char *message)
{
	printf("%s\n", message);
	return (1);
}

void	types_help(void)
{
	printf("%s  -  %15s\n", "N_STAB", ft_utob(N_STAB, 2, "01"));
	printf("%s  -  %15s\n", "N_PEXT", ft_utob(N_PEXT, 2, "01"));
	printf("%s  -  %15s\n", "N_TYPE", ft_utob(N_TYPE, 2, "01"));
	printf("%s  -  %15s\n\n", "N_EXT ", ft_utob(N_EXT, 2, "01"));
	printf("   N_TYPE :\n\n");
	printf("%s  -  %15s\n", "N_UNDF", ft_utob(N_UNDF, 2, "01"));
	printf("%s  -  %15s\n", "N_ABS ", ft_utob(N_ABS, 2, "01"));
	printf("%s  -  %15s\n", "N_SECT", ft_utob(N_SECT, 2, "01"));
	printf("%s  -  %15s\n", "N_PBUD", ft_utob(N_PBUD, 2, "01"));
	printf("%s  -  %15s\n\n", "N_INDR", ft_utob(N_INDR, 2, "01"));
}


// n_list.h  line 109 - 136
char	*symbol_type(int type, int sect, int value)
{
	if (type == N_EXT)
	{
		if (value)
			return ("C");
		return ("U");
	}
	if (type == N_STAB)
		return ("-");
	if (type & N_SECT)
	{
		printf("%d - ", sect);
		if (type & 1)
			return ("ext_sect");
		return ("loc_sect");
	}
	// if (type )
	// if (type & N_UNDF)
	// 	return ('U');
	// if (type & N_ABS)
	// 	return ('A');
	// printf("%s\n", ft_utob(type, 2, "01"));
	// return ("X");
	return (ft_utob(type, 2, "01"));
}

void	display_symbols(char *file, struct symtab_command *symtab_cmd)
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

void	handle64(char *file)
{
	int						i;
	struct mach_header_64	*header;
	struct load_command		*load_cmds;
	struct symtab_command	*symtab_cmd;

	header = (struct mach_header_64 *)file;
	load_cmds = (struct load_command *)(header + 1);

	printf("%d\n", header->ncmds);
	i = 0;
	while (i < header->ncmds)
	{
		printf("NEW COMMAND\n");
		if (load_cmds->cmd == LC_SYMTAB)
		{
			printf("SEGMENT FOUND :  symtab_command");
			display_symbols(file, (struct symtab_command *)load_cmds);
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

void	nm(char *file)
{
	int						magic;

	magic = *(int *)file;
	if (magic == MH_MAGIC_64)
	{
		printf("64 bits - %x\n", magic);
		handle64(file);
	}
	else if (magic == MH_MAGIC)
		printf("32 bits - %x\n", magic);
	else
		printf("not a binary\n");


}

int		main(int argc, char **argv)
{
	int				fd;
	char			*file;
	struct stat		file_info;

	// printf("%s\n", ft_utob(45, 2, "01"));
	types_help();

	if (argc != 2)
		return (ft_error("Error\n"));

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error("Open error\n"));

	if (fstat(fd, &file_info) < 0)
		return (ft_error("Fstat error\n"));

	if ((file = mmap(0, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error("Mmap error\n"));

	nm(file);

	return (0);
}