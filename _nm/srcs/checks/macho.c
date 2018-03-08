/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessye <jessye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:43 by jfuster           #+#    #+#             */
/*   Updated: 2018/03/08 23:58:33 by jessye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_nm.h"

enum check_result	check_load_commands_64(struct mach_header_64 *mh, struct load_command *lc, char *filename, t_filetype_t ft)
{
	size_t					i;
	struct load_command		*l;

	l = lc;
	i = 0;
	while (i < S_32(mh->ncmds, ft))
	{
		if ((void *)l > (void *)lc + S_32(mh->sizeofcmds, ft))
			return (filecheck_error(filename, "command out of cmds"));
		if ((void *)l + sizeof(struct load_command *) > (void *)lc + S_32(mh->sizeofcmds, ft))
			return (filecheck_error(filename, "command end out of cmds"));
		if (S_32(l->cmdsize, ft) == 0)
			return (filecheck_error(filename, "bad command size"));
		if ((void *)l + S_32(l->cmdsize, ft) > (void *)lc + S_32(mh->sizeofcmds, ft))
			return (filecheck_error(filename, "real command end out of cmds"));
		l = (void *)l + S_32(l->cmdsize, ft);
		i++;
	}
	return (CHECK_GOOD);
}

enum check_result	check_macho_64(char *file, size_t size, char *filename, t_filetype_t ft)
{
	struct mach_header_64	*mh;
	struct load_command		*lc;

	mh = (struct mach_header_64 *)file;
	lc = (struct load_command *)(mh + 1);
	if (size < sizeof(struct mach_header_64))
		return (filecheck_error(filename, "no size for mach header"));
	if (size < sizeof(struct mach_header_64) + S_32(mh->sizeofcmds, ft))
		return (filecheck_error(filename, "bad size of cmds"));
	if (check_load_commands_64(mh, lc, filename, ft) == CHECK_BAD)
		return (CHECK_BAD);
	return (CHECK_GOOD);
}

enum check_result	check_macho(char *file, size_t size, char *filename, t_filetype_t ft)
{

	if (F_IS_32(ft))
		return (filecheck_error(filename, "32 arch not handled"));
	else
		return (check_macho_64(file, size, filename, ft));
}
