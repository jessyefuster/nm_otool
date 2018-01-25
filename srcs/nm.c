/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:30:05 by jfuster           #+#    #+#             */
/*   Updated: 2018/01/25 16:18:39 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
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

// n_list.h  line 109 - 136
char	symbol_type(int type)
{
	if (type == N_UNDF)
		return ('C');
	if (type == N_ABS)
		return ('A');
	return ('X');
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
			printf("%016llx %c %s\n", sym_table->n_value, symbol_type(sym_table->n_type), string_table + string_index);
		else
			printf("%18c %s\n", symbol_type(sym_table->n_type), string_table + string_index);
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

	i = 0;
	while (i < header->ncmds)
	{
		if (load_cmds->cmd == LC_SYMTAB)
		{
			printf("LC_SYMTAB load command\n");
			display_symbols(file, (struct symtab_command *)load_cmds);
			// symtab_cmd = (struct symtab_command *)load_cmds;
			// printf("number of symbols : %d\n", symtab_cmd->nsyms);
			break ;
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