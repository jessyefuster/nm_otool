/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:43 by jfuster           #+#    #+#             */
/*   Updated: 2018/04/25 16:14:33 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

enum e_check_result				check_symtab_command(t_file *file,
								struct symtab_command *st)
{
	if (st->cmdsize != sizeof(struct symtab_command))
		return (filecheck_error(file->name, "LC_SYMTAB incorrect cmdsize"));
	if (st->symoff > file->size)
		return (filecheck_error(file->name, "LC_SYMTAB symoff out of file"));
	if (st->symoff + st->nsyms * sizeof(struct nlist_64) > file->size)
		return (filecheck_error(file->name, "no size for symbol table"));
	if (st->stroff > file->size)
		return (filecheck_error(file->name, "LC_SYMTAB stroff out of file"));
	if (st->stroff + st->strsize > file->size)
		return (filecheck_error(file->name, "no size for string table"));
	return (CHECK_GOOD);
}

static enum e_check_result		check_macho_32(t_file *file)
{
	struct mach_header		*mh;
	struct load_command		*lc;

	mh = (struct mach_header *)(file->ptr);
	lc = (struct load_command *)(mh + 1);
	if (F_IS_BIG(file->type))
		swap_mach_header(mh);
	if (file->size < sizeof(struct mach_header))
		return (filecheck_error(file->name, "no size for mach header"));
	if (file->size < sizeof(struct mach_header) + mh->sizeofcmds)
		return (filecheck_error(file->name, "bad size of cmds"));
	if (check_load_commands_32(file, mh, lc) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

static enum e_check_result		check_macho_64(t_file *file)
{
	struct mach_header_64	*mh;
	struct load_command		*lc;

	mh = (struct mach_header_64 *)(file->ptr);
	lc = (struct load_command *)(mh + 1);
	if (F_IS_BIG(file->type))
		swap_mach_header_64(mh);
	if (file->size < sizeof(struct mach_header_64))
		return (filecheck_error(file->name, "no size for mach header"));
	if (file->size < sizeof(struct mach_header_64) + mh->sizeofcmds)
		return (filecheck_error(file->name, "bad size of cmds"));
	if (check_load_commands_64(file, mh, lc) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

enum e_check_result				check_macho(t_file *file)
{
	if (F_IS_32(file->type))
		return (check_macho_32(file));
	else
		return (check_macho_64(file));
}
