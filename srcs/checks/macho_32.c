/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessyefuster <jessyefuster@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 20:54:36 by jessye            #+#    #+#             */
/*   Updated: 2018/12/11 16:31:38 by jessyefuster     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nm_otool.h"

static enum e_check_result	check_segment_command_32(t_file *file,
	struct mach_header *mh, struct load_command *lc, struct segment_command *sg)
{
	size_t				i;
	char				*p;
	struct section		*s;

	// printf("SEGNAME : %s\n", sg->segname);
	if (sg->cmdsize != sizeof(t_seg) + sg->nsects * sizeof(t_sect))
		return (filecheck_error(file->name, "LC_SEGMENT incorrect cmdsize"));
	s = (struct section *)((void *)sg + sizeof(struct segment_command));
	p = (char *)s;
	i = 0;
	while (i < sg->nsects)
	{
		// printf("sect %zu\n", i);
		if (F_IS_BIG(file->type))
			swap_section(s);
		if (p + sizeof(struct section) > (char *)lc + mh->sizeofcmds)
			return (filecheck_error(file->name, "section offset out of load commands"));
		// if (s->offset > file->size || s->offset + s->size > file->size)
		// {
		// 	printf("s offset %d, s->offset + s->size %u,file size %zu\n", s->offset, s->offset + s->size, file->size);
		// 	return (filecheck_error(file->name, "section offset out of file"));
		// }
		s++;
		i++;
	}
	return (CHECK_GOOD);
}

static enum e_check_result	check_symtab_32(t_file *file,
	struct mach_header *mh, struct symtab_command **st, struct load_command *l)
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

static enum e_check_result	check_segment_32(t_file *file,
	struct mach_header *mh, struct segment_command *sg, struct load_command *l)
{
	struct load_command		*lc;

	lc = (struct load_command *)(mh + 1);
	if ((void *)l + sizeof(t_seg) > (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "LC_SEGMENT end out of cmds"));
	if (F_IS_BIG(file->type))
		swap_segment(sg);
	if ((void *)l + sizeof(t_seg) + sg->nsects * sizeof(t_sect) >
	(void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "LC_SEGMENT sections out of cmds"));
	if (check_segment_command_32(file, mh, lc, sg) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

static enum e_check_result	check_command_32(t_file *file,
	struct mach_header *mh, struct load_command *l)
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

enum e_check_result			check_load_commands_32(t_file *file,
	struct mach_header *mh, struct load_command *lc)
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
		if (check_command_32(file, mh, l) == CHECK_BAD)
			return (CHECK_BAD);
		if (l->cmd == LC_SYMTAB &&
		check_symtab_32(file, mh, &st, l) == CHECK_BAD)
			return (CHECK_BAD);
		else if (l->cmd == LC_SEGMENT &&
		check_segment_32(file, mh, (t_seg *)l, l) == CHECK_BAD)
			return (CHECK_BAD);
		l = (void *)l + l->cmdsize;
		i++;
	}
	if ((void *)l != (void *)lc + mh->sizeofcmds)
		return (filecheck_error(file->name, "inconsistent size of cmds"));
	return (CHECK_GOOD);
}
