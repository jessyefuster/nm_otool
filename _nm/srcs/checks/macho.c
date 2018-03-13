/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:43 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/13 16:01:10 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static enum check_result	check_segment_command_64(t_file *file, struct segment_command_64 *sg, t_filetype_t ft)
{
	size_t				i;
	struct section_64	*s;

	if (S_32(sg->cmdsize, ft) != sizeof(struct segment_command_64) + sg->nsects * sizeof(struct section_64))
		return (filecheck_error(file->filename, "LC_SEGMENT_64 incorrect cmdsize"));
	s = (struct section_64 *)((void *)sg + sizeof(struct segment_command_64));
	i = 0;
	while (i < sg->nsects)
	{
		i++;
	}

	return (CHECK_GOOD);
}

static enum check_result	check_symtab_command_64(t_file *file, struct symtab_command *st, t_filetype_t ft)
{
	if (S_32(st->cmdsize, ft) != sizeof(struct symtab_command))
		return (filecheck_error(file->filename, "LC_SYMTAB incorrect cmdsize"));
	if (S_32(st->symoff, ft) > file->size)
		return (filecheck_error(file->filename, "LC_SYMTAB symoff out of file"));
	if (S_32(st->symoff, ft) + S_32(st->nsyms, ft) * sizeof(struct nlist_64) > file->size)
		return (filecheck_error(file->filename, "no size for symbol table"));
	if (S_32(st->stroff, ft) > file->size)
		return (filecheck_error(file->filename, "LC_SYMTAB stroff out of file"));
	if (S_32(st->stroff, ft) + S_32(st->strsize, ft) > file->size)
		return (filecheck_error(file->filename, "no size for string table"));
	return (CHECK_GOOD);
}

static enum check_result	check_load_commands_64(t_file *file, struct mach_header_64 *mh, struct load_command *lc, t_filetype_t ft)
{
	size_t						i;
	struct load_command			*l;
	struct symtab_command		*st;
	struct segment_command_64	*sg;

	st = NULL;
	sg = NULL;
	l = lc;
	i = 0;
	while (i < S_32(mh->ncmds, ft))
	{
		if ((void *)l > (void *)lc + S_32(mh->sizeofcmds, ft))
			return (filecheck_error(file->filename, "command out of cmds"));
		if ((void *)l + sizeof(struct load_command) > (void *)lc + S_32(mh->sizeofcmds, ft))
			return (filecheck_error(file->filename, "command end out of cmds"));
		if (S_32(l->cmdsize, ft) == 0)
			return (filecheck_error(file->filename, "bad command size"));
		if ((void *)l + S_32(l->cmdsize, ft) > (void *)lc + S_32(mh->sizeofcmds, ft))
			return (filecheck_error(file->filename, "real command end out of cmds"));

		if (S_32(l->cmd, ft) == LC_SYMTAB)
		{
			if (st != NULL)
				return (filecheck_error(file->filename, "more than one LC_SYMTAB"));
			st = (struct symtab_command *)l;
			if ((void *)l + sizeof(struct symtab_command) > (void *)lc + S_32(mh->sizeofcmds, ft))
				return (filecheck_error(file->filename, "LC_SYMTAB end out of cmds"));
			if (check_symtab_command_64(file, st, ft) == CHECK_BAD)
				return (CHECK_BAD);
		}
		else if (S_32(l->cmd, ft) == LC_SEGMENT_64)
		{
			sg = (struct segment_command_64 *)l;
			if ((void *)l + sizeof(struct segment_command_64) > (void *)lc + S_32(mh->sizeofcmds, ft))
				return (filecheck_error(file->filename, "LC_SEGMENT_64 end out of cmds"));
			if ((void *)l + sizeof(struct segment_command_64) + sg->nsects * sizeof(struct section_64) > (void *)lc + S_32(mh->sizeofcmds, ft))
				return (filecheck_error(file->filename, "LC_SEGMENT_64 sections out of cmds"));
			if (check_segment_command_64(file, sg, ft) == CHECK_BAD)
				return (CHECK_BAD);
		}

		l = (void *)l + S_32(l->cmdsize, ft);
		i++;
	}
	if ((void *)l != (void *)lc + S_32(mh->sizeofcmds, ft))
		return (filecheck_error(file->filename, "inconsistent size of cmds"));
	return (CHECK_GOOD);
}

static enum check_result	check_macho_64(t_file *file, t_filetype_t ft)
{
	struct mach_header_64	*mh;
	struct load_command		*lc;

	mh = (struct mach_header_64 *)(file->ptr);
	lc = (struct load_command *)(mh + 1);
	if (file->size < sizeof(struct mach_header_64))
		return (filecheck_error(file->filename, "no size for mach header"));
	if (file->size < sizeof(struct mach_header_64) + S_32(mh->sizeofcmds, ft))
		return (filecheck_error(file->filename, "bad size of cmds"));
	if (check_load_commands_64(file, mh, lc, ft) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

enum check_result	check_macho(t_file *file, t_filetype_t ft)
{

	if (F_IS_32(ft))
		return (filecheck_error(file->filename, "32 arch not handled"));
	else
		return (check_macho_64(file, ft));
}
