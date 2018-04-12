/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessyefuster <jessyefuster@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 20:55:03 by jessye            #+#    #+#             */
/*   Updated: 2018/04/11 20:25:26 by jessyefuster     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

static enum check_result	check_segment_command_64(t_file *file, struct segment_command_64 *sg, t_filetype_t ft)
{
	size_t				i;
	struct section_64	*s;

	if (sg->cmdsize != sizeof(struct segment_command_64) + sg->nsects * sizeof(struct section_64))
		return (filecheck_error(file->name, "LC_SEGMENT_64 incorrect cmdsize"));
	s = (struct section_64 *)((void *)sg + sizeof(struct segment_command_64));
	i = 0;
	while (i < sg->nsects)
	{
		if (F_IS_BIG(ft))
			swap_section_64(s);
		if (s->offset > file->size || s->offset + s->size > file->size)
			return (filecheck_error(file->name, "section offset out of file"));
		s++;
		i++;
	}

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
	while (i < mh->ncmds)
	{
		if ((void *)l > (void *)lc + mh->sizeofcmds)
			return (filecheck_error(file->name, "command out of cmds"));
		if ((void *)l + sizeof(struct load_command) > (void *)lc + mh->sizeofcmds)
			return (filecheck_error(file->name, "command end out of cmds"));
		if (F_IS_BIG(ft))
			swap_load_command(l);
		if (l->cmdsize == 0)
			return (filecheck_error(file->name, "bad command size"));
		if ((void *)l + l->cmdsize > (void *)lc + mh->sizeofcmds)
			return (filecheck_error(file->name, "real command end out of cmds"));

		if (l->cmd == LC_SYMTAB)
		{
			if (st != NULL)
				return (filecheck_error(file->name, "more than one LC_SYMTAB"));
			st = (struct symtab_command *)l;
			if ((void *)l + sizeof(struct symtab_command) > (void *)lc + mh->sizeofcmds)
				return (filecheck_error(file->name, "LC_SYMTAB end out of cmds"));
			if (F_IS_BIG(ft))
				swap_symtab(st);
			if (check_symtab_command(file, st, ft) == CHECK_BAD)
				return (CHECK_BAD);
		}
		else if (l->cmd == LC_SEGMENT_64)
		{
			sg = (struct segment_command_64 *)l;
			if ((void *)l + sizeof(struct segment_command_64) > (void *)lc + mh->sizeofcmds)
				return (filecheck_error(file->name, "LC_SEGMENT_64 end out of cmds"));
			if (F_IS_BIG(ft))
				swap_segment_64(sg);
			if ((void *)l + sizeof(struct segment_command_64) + sg->nsects * sizeof(struct section_64) > (void *)lc + mh->sizeofcmds)
				return (filecheck_error(file->name, "LC_SEGMENT_64 sections out of cmds"));
			if (check_segment_command_64(file, sg, ft) == CHECK_BAD)
				return (CHECK_BAD);
		}

		l = (void *)l + l->cmdsize;
		i++;
	}
	if ((void *)l != (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "inconsistent size of cmds"));
	return (CHECK_GOOD);
}

enum check_result	check_macho_64(t_file *file, t_filetype_t ft)
{
	struct mach_header_64	*mh;
	struct load_command		*lc;

	mh = (struct mach_header_64 *)(file->ptr);
	lc = (struct load_command *)(mh + 1);
	if (F_IS_BIG(ft))
		swap_mach_header_64(mh);
	if (file->size < sizeof(struct mach_header_64))
		return (filecheck_error(file->name, "no size for mach header"));
	if (file->size < sizeof(struct mach_header_64) + mh->sizeofcmds)
		return (filecheck_error(file->name, "bad size of cmds"));
	if (check_load_commands_64(file, mh, lc, ft) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}