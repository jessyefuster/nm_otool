/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <jfuster@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 20:55:03 by jessye            #+#    #+#             */
/*   Updated: 2018/04/25 16:30:46 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

static enum e_check_result	check_segment_command_64(t_file *file,
	struct segment_command_64 *sg)
{
	size_t				i;
	struct section_64	*s;

	if (sg->cmdsize != sizeof(t_seg_64) + sg->nsects * sizeof(t_sect_64))
		return (filecheck_error(file->name, "LC_SEGMENT64 incorrect cmdsize"));
	s = (struct section_64 *)((void *)sg + sizeof(struct segment_command_64));
	i = 0;
	while (i < sg->nsects)
	{
		if (F_IS_BIG(file->type))
			swap_section_64(s);
		if (s->offset > file->size || s->offset + s->size > file->size)
			return (filecheck_error(file->name, "section offset out of file"));
		s++;
		i++;
	}
	return (CHECK_GOOD);
}

static enum e_check_result	check_symtab_64(t_file *file,
struct mach_header_64 *mh, struct symtab_command **st, struct load_command *l)
{
	struct load_command		*lc;

	lc = (struct load_command *)(mh + 1);
	if (*st != NULL)
		return (filecheck_error(file->name, "more than one LC_SYMTAB"));
	*st = (struct symtab_command *)l;
	if ((void *)l + sizeof(struct symtab_command) > (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "LC_SYMTAB end out of cmds"));
	if (F_IS_BIG(file->type))
		swap_symtab(*st);
	if (check_symtab_command(file, *st) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

static enum e_check_result	check_segment_64(t_file *file,
	struct mach_header_64 *mh, t_seg_64 *sg, struct load_command *l)
{
	struct load_command		*lc;

	lc = (struct load_command *)(mh + 1);
	if ((void *)l + sizeof(t_seg_64) > (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "LC_SEGMENT end out of cmds"));
	if (F_IS_BIG(file->type))
		swap_segment_64(sg);
	if ((void *)l + sizeof(t_seg_64) + sg->nsects * sizeof(t_sect_64) >
	(void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "LC_SEGMENT sections out of cmds"));
	if (check_segment_command_64(file, sg) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

static enum e_check_result	check_command_64(t_file *file,
	struct mach_header_64 *mh, struct load_command *l)
{
	struct load_command		*lc;

	lc = (struct load_command *)(mh + 1);
	if ((void *)l > (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "command out of cmds"));
	if ((void *)l + sizeof(struct load_command) > (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "command end out of cmds"));
	if (F_IS_BIG(file->type))
		swap_load_command(l);
	if (l->cmdsize == 0)
		return (filecheck_error(file->name, "bad command size"));
	if ((void *)l + l->cmdsize > (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "real command end out of cmds"));
	return (CHECK_GOOD);
}

enum e_check_result			check_load_commands_64(t_file *file,
	struct mach_header_64 *mh, struct load_command *lc)
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
		check_command_64(file, mh, l);
		if (l->cmd == LC_SYMTAB &&
		check_symtab_64(file, mh, &st, l) == CHECK_BAD)
			return (CHECK_BAD);
		else if (l->cmd == LC_SEGMENT_64 &&
		check_segment_64(file, mh, (t_seg_64 *)l, l) == CHECK_BAD)
			return (CHECK_BAD);
		l = (void *)l + l->cmdsize;
		i++;
	}
	if ((void *)l != (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "inconsistent size of cmds"));
	return (CHECK_GOOD);
}
