/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 20:54:36 by jessye            #+#    #+#             */
/*   Updated: 2018/03/15 21:10:46 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

static enum check_result	check_segment_command_32(t_file *file, struct segment_command *sg, t_filetype_t ft)
{
	(void)ft;
	size_t				i;
	struct section		*s;

	if (sg->cmdsize != sizeof(struct segment_command) + sg->nsects * sizeof(struct section))
		return (filecheck_error(file->filename, "LC_SEGMENT incorrect cmdsize"));
	s = (struct section *)((void *)sg + sizeof(struct segment_command));
	i = 0;
	while (i < sg->nsects)
	{
		i++;
	}

	return (CHECK_GOOD);
}

static enum check_result	check_load_commands_32(t_file *file, struct mach_header *mh, struct load_command *lc, t_filetype_t ft)
{
	size_t						i;
	struct load_command			*l;
	struct symtab_command		*st;
	struct segment_command		*sg;

	st = NULL;
	sg = NULL;
	l = lc;
	i = 0;
	while (i < mh->ncmds)
	{
		if ((void *)l > (void *)lc + mh->sizeofcmds)
			return (filecheck_error(file->filename, "command out of cmds"));
		if ((void *)l + sizeof(struct load_command) > (void *)lc + mh->sizeofcmds)
			return (filecheck_error(file->filename, "command end out of cmds"));
		if (F_IS_BIG(ft))
			swap_load_command(l);
		if (l->cmdsize == 0)
			return (filecheck_error(file->filename, "bad command size"));
		if ((void *)l + l->cmdsize > (void *)lc + mh->sizeofcmds)
			return (filecheck_error(file->filename, "real command end out of cmds"));

		if (l->cmd == LC_SYMTAB)
		{
			if (st != NULL)
				return (filecheck_error(file->filename, "more than one LC_SYMTAB"));
			st = (struct symtab_command *)l;
			if ((void *)l + sizeof(struct symtab_command) > (void *)lc + mh->sizeofcmds)
				return (filecheck_error(file->filename, "LC_SYMTAB end out of cmds"));
			if (F_IS_BIG(ft))
				swap_symtab(st);
			if (check_symtab_command(file, st, ft) == CHECK_BAD)
				return (CHECK_BAD);
		}
		else if (l->cmd == LC_SEGMENT)
		{
			sg = (struct segment_command *)l;
			if ((void *)l + sizeof(struct segment_command) > (void *)lc + mh->sizeofcmds)
				return (filecheck_error(file->filename, "LC_SEGMENT end out of cmds"));
			if (F_IS_BIG(ft))
				swap_segment(sg);
			if ((void *)l + sizeof(struct segment_command) + sg->nsects * sizeof(struct section) > (void *)lc + mh->sizeofcmds)
				return (filecheck_error(file->filename, "LC_SEGMENT sections out of cmds"));
			if (check_segment_command_32(file, sg, ft) == CHECK_BAD)
				return (CHECK_BAD);
		}

		l = (void *)l + l->cmdsize;
		i++;
	}
	if ((void *)l != (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->filename, "inconsistent size of cmds"));
	return (CHECK_GOOD);
}

enum check_result	check_macho_32(t_file *file, t_filetype_t ft)
{
	struct mach_header		*mh;
	struct load_command		*lc;

	mh = (struct mach_header *)(file->ptr);
	lc = (struct load_command *)(mh + 1);
	if (F_IS_BIG(ft))
		swap_mach_header(mh);
	if (file->size < sizeof(struct mach_header))
		return (filecheck_error(file->filename, "no size for mach header"));
	if (file->size < sizeof(struct mach_header) + mh->sizeofcmds)
		return (filecheck_error(file->filename, "bad size of cmds"));
	if (check_load_commands_32(file, mh, lc, ft) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}