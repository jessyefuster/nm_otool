/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:04 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/05 15:33:56 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

/*
**	Search for SYMTAB load command in Mach-o file
**	note : this function handles both 32bit and 64bit arch
**	note : this function handles endianess
*/

void		handle_macho(char *file, uint32_t file_type, t_symbols **symbols)
{
	size_t					i;
	size_t					ncmds;
	struct load_command		*load_cmds;

	ncmds = S_32(((struct mach_header *)file)->ncmds, file_type);
	load_cmds = (struct load_command *)(((struct mach_header_64 *)file) + 1);
	if (F_ARCH(file_type) == F_32)
		load_cmds = (struct load_command *)(((struct mach_header *)file) + 1);
	i = 0;
	while (i < ncmds)
	{
		if (S_32(load_cmds->cmd, file_type) == LC_SYMTAB)
		{
			store_symbols(file, file_type, (struct symtab_command *)load_cmds,
				symbols);
			break ;
		}
		load_cmds = (void *)load_cmds + S_32(load_cmds->cmdsize, file_type);
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
	if ((fat_arch = find_arch(fat_header, CPU_TYPE_X86_64)))
		ft_nm(file + swap_uint32(fat_arch->offset), filename, FALSE);
	else
	{
		fat_arch = (struct fat_arch *)(fat_header + 1);
		i = 0;
		while (i < swap_uint32(fat_header->nfat_arch))
		{
			name = ft_strjoin(filename, arch_name(swap_uint32(fat_arch->cputype)));
			ft_nm(file + swap_uint32(fat_arch->offset), name, TRUE);
			free(name);
			fat_arch++;
			i++;
		}
	}
}

/*
**	https://code.woboq.org/llvm/include/ar.h.html
**	https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg
*/

void		handle_archive(char *file, uint32_t file_type)
{
	// printf("%u\n", file_type);
	(void)file_type;

	size_t	*offsets;

	offsets = archive_offsets((struct ar_hdr *)file);
	// struct ar_hdr	*header;
	// size_t			symdef_len;
	// char			*symdef;
	// struct ranlib	*ran;
	// size_t			n_ran;

	// header = (struct ar_hdr *)file;
	// symdef_len = ft_atoi(file + (sizeof(AR_EFMT1) - 1));
	// symdef = (char *)(header + 1);
	// ran = (struct ranlib *)(symdef + symdef_len + sizeof(uint32_t));

	// n_ran = *((uint32_t *)(symdef + symdef_len)) / sizeof(struct ranlib);

	// for (size_t i = 0; i < n_ran; ++i)
	// {
	// 	printf("%u\n", ran->ran_off);
	// 	ran++;
	// }

	// printf("len %zu\n", symdef_len);
	// printf("n_ran %zu\n", n_ran);
}
