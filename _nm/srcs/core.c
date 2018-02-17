/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/02/17 18:57:43 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	Search for SYMTAB load command in Mach-o file
**	note : this function handles both 32bit and 64bit arch
*/
void		handle_macho(char *file, uint32_t file_type, t_symbols **symbols)
{
	size_t					i;
	size_t					ncmds;
	struct load_command		*load_cmds;

	ncmds = ((struct mach_header *)file)->ncmds;
	load_cmds = (struct load_command *)(((struct mach_header_64 *)file) + 1);
	if (F_ARCH(file_type) == F_32)
		load_cmds = (struct load_command *)(((struct mach_header *)file) + 1);

	i = 0;
	while (i < ncmds)
	{
		if (load_cmds->cmd == LC_SYMTAB)
		{
			store_symbols(file, file_type, (struct symtab_command *)load_cmds, symbols);
			break ;
		}
		load_cmds = (void *)load_cmds + load_cmds->cmdsize;
		i++;
	}	
}

/*
**	Iterate over arch headers in FAT file and nm each binary
*/
void		handle_fat(char *file, char *filename)
{
	size_t				i;
	char				*name;
	struct fat_header	*fat_header;
	struct fat_arch		*fat_arch;

	fat_header = (struct fat_header *)file;
	name = ft_strjoin(filename, " (for architecture x86_64)");
	if ((fat_arch = find_arch(fat_header, CPU_TYPE_X86_64)))
		ft_nm(file + swap_endian(fat_arch->offset), name);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < swap_endian(fat_header->nfat_arch))
		{
			name = ft_strjoin(filename, " (for architecture ...)");
			ft_nm(file + swap_endian(fat_arch->offset), name);
			free(name);
			fat_arch++;
			i++;
		}
		return ;
	}
	free(name);
}
// https://code.woboq.org/llvm/include/ar.h.html
// https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg
void		handle_archive(char *file, uint32_t file_type)
{
	printf("%p %u\n", file, file_type);
}
